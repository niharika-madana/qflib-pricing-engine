#include <qflib/pricers/bsmcquantopricer.hpp>
#include <qflib/methods/montecarlo/antitheticpathgenerator.hpp>
#include <cmath>

using namespace std;

BEGIN_NAMESPACE(qf)

BsMcQuantoPricer::BsMcQuantoPricer(SPtrProduct prod,
                                   SPtrYieldCurve discountYieldCurve,
                                   SPtrYieldCurve growthYieldCurve,
                                   double divYield,
                                   SPtrVolatilityTermStructure assetVol,
                                   double fxVol,
                                   double correl,
                                   double spot,
                                   McParams mcparams)
: prod_(prod), discyc_(discountYieldCurve), growthyc_(growthYieldCurve),
  divyld_(divYield), fxvol_(fxVol), correl_(correl),
  vol_(assetVol), spot_(spot), mcparams_(mcparams)
{
  QF_ASSERT(correl >= -1.0 && correl <= 1.0, "BsMcQuantoPricer: correl must be in [-1, 1]");
  QF_ASSERT(fxVol >= 0.0, "BsMcQuantoPricer: fxVol must be non-negative");

  Vector timesteps = prod->fixTimes();

  if (mcparams.pathGenType == McParams::PathGenType::EULER) {
    if (mcparams.urngType == McParams::UrngType::MINSTDRAND)
      pathgen_ = SPtrPathGenerator(new EulerPathGenerator<NormalRngMinStdRand>(
          timesteps.begin(), timesteps.end(), 1));
    else if (mcparams.urngType == McParams::UrngType::MT19937)
      pathgen_ = SPtrPathGenerator(new EulerPathGenerator<NormalRngMt19937>(
          timesteps.begin(), timesteps.end(), 1));
    else if (mcparams.urngType == McParams::UrngType::RANLUX3)
      pathgen_ = SPtrPathGenerator(new EulerPathGenerator<NormalRngRanLux3>(
          timesteps.begin(), timesteps.end(), 1));
    else if (mcparams.urngType == McParams::UrngType::RANLUX4)
      pathgen_ = SPtrPathGenerator(new EulerPathGenerator<NormalRngRanLux4>(
          timesteps.begin(), timesteps.end(), 1));
    else
      QF_ASSERT(0, "unknown urng type!");
  }
  else
    QF_ASSERT(0, "unknown path generator type!");

  if (mcparams.controlVarType == McParams::ControlVarType::ANTITHETIC)
    pathgen_ = SPtrPathGenerator(new AntitheticPathGenerator(pathgen_));

  Vector const& paytimes = prod->payTimes();
  discfactors_.resize(paytimes.size());
  for (size_t i = 0; i < paytimes.size(); ++i)
    discfactors_[i] = discyc_->discount(paytimes[i]);

  Vector const& fixtimes = prod->fixTimes();
  double t1 = 0.0;
  drifts_.resize(fixtimes.size());
  stdevs_.resize(fixtimes.size());
  for (size_t i = 0; i < fixtimes.size(); ++i) {
    double t2 = fixtimes[i];
    double assetFwdVol = vol_->fwdVol(t1, t2);
    double var = assetFwdVol * assetFwdVol * (t2 - t1);
    stdevs_[i] = sqrt(var);
    double growthFwdRate = growthyc_->fwdRate(t1, t2);
    double quantoAdj = correl_ * assetFwdVol * fxvol_;
    drifts_[i] = (growthFwdRate - divyld_ + quantoAdj) * (t2 - t1) - 0.5 * var;
    t1 = t2;
  }

  payamts_.resize(prod->payTimes().size());
}


double BsMcQuantoPricer::processOnePath(Matrix& pricePath)
{
  pathgen_->next(pricePath);
  double spot = spot_;
  for (size_t i = 0; i < pricePath.n_rows; ++i) {
    double normaldeviate = pricePath(i, 0);
    pricePath(i, 0) = spot * exp(drifts_[i] + stdevs_[i] * normaldeviate);
    spot = pricePath(i, 0);
  }
  prod_->eval(pricePath);
  payamts_ = prod_->payAmounts();

  double pv = 0.0;
  for (size_t i = 0; i < payamts_.size(); ++i)
    pv += discfactors_[i] * payamts_[i];

  return pv;
}

END_NAMESPACE(qf)

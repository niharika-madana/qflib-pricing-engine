#pragma once

#include <qflib/products/product.hpp>
#include <qflib/market/yieldcurve.hpp>
#include <qflib/market/volatilitytermstructure.hpp>
#include <qflib/methods/montecarlo/mcparams.hpp>
#include <qflib/methods/montecarlo/pathgenerator.hpp>
#include <qflib/methods/montecarlo/eulerpathgenerator.hpp>
#include <qflib/math/stats/statisticscalculator.hpp>

BEGIN_NAMESPACE(qf)

class BsMcQuantoPricer
{
public:
  BsMcQuantoPricer(SPtrProduct prod,
                   SPtrYieldCurve discountYieldCurve,
                   SPtrYieldCurve growthYieldCurve,
                   double divYield,
                   SPtrVolatilityTermStructure assetVol,
                   double fxVol,
                   double correl,
                   double spot,
                   McParams mcparams);

  size_t nVariables();

  template<typename ITER>
  void simulate(StatisticsCalculator<ITER>& statsCalc, unsigned long npaths);

protected:
  double processOnePath(Matrix& pricePath);

private:
  SPtrProduct prod_;
  SPtrYieldCurve discyc_;
  SPtrYieldCurve growthyc_;
  double divyld_;
  double fxvol_;
  double correl_;
  SPtrVolatilityTermStructure vol_;
  double spot_;
  McParams mcparams_;

  SPtrPathGenerator pathgen_;
  Vector discfactors_;
  Vector drifts_;
  Vector stdevs_;
  Vector payamts_;
};

inline
size_t BsMcQuantoPricer::nVariables()
{
  return 1;
}

template<typename ITER>
void BsMcQuantoPricer::simulate(StatisticsCalculator<ITER>& statsCalc, unsigned long npaths)
{
  Matrix pricePath(pathgen_->nTimeSteps(), pathgen_->nFactors());
  QF_ASSERT(statsCalc.nVariables() == nVariables(), "the statistics calculator must track only one variable!");

  for (unsigned long i = 0; i < npaths; ++i) {
    double pv = processOnePath(pricePath);
    statsCalc.addSample(&pv, &pv + 1);
  }
}

END_NAMESPACE(qf)

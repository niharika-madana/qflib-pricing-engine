/**
@file  simplepricers.cpp
@brief Implementation of simple pricing functions
*/

#include <qflib/pricers/simplepricers.hpp>
#include <qflib/math/stats/normaldistribution.hpp>
#include <qflib/utils.hpp>

#include <cmath>

BEGIN_NAMESPACE(qf)

/** The forward price of an asset */
double fwdPrice(double spot, double timeToExp, double intRate, double divYield)
{
  QF_ASSERT(spot >= 0.0, "spot must be non-negative");
  QF_ASSERT(timeToExp >= 0.0, "time to expiration must be non-negative");
  QF_ASSERT(intRate >= 0.0, "interest rate must be non-negative");
  QF_ASSERT(divYield >= 0.0, "dividend yield must be non-negative");

  return spot * exp((intRate - divYield) * timeToExp);
}

/** The quanto forward price of an asset */
double quantoFwdPrice(double spot, double timeToExp, double intRate, double divYield,
                      double assetVol, double fxVol, double correl)
{
  double fwd = fwdPrice(spot, timeToExp, intRate, divYield);
  QF_ASSERT(assetVol >= 0.0, "asset volatility must be non-negative");
  QF_ASSERT(fxVol >= 0.0, "FX volatility must be non-negative");
  QF_ASSERT(correl <= 1.0 && correl >= -1.0, "asset-FX correlation must be in [-1, 1]");

  double cvx = exp(correl * assetVol * fxVol * timeToExp);
  return cvx * fwd;
}

/** Price of a European digital option in the Black-Scholes model*/
Vector digitalOptionBS(int payoffType, double spot, double strike, double timeToExp,
                       double intRate, double divYield, double volatility)
{
  QF_ASSERT(payoffType == 1 || payoffType == -1, "payoffType must be 1 or -1");
  QF_ASSERT(strike >= 0.0, "strike must be non-negative");
  QF_ASSERT(divYield >= 0.0, "dividend yield must be non-negative");
  QF_ASSERT(volatility >= 0.0, "volatility must be non-negative");

  double phi = payoffType;
  double fwd = fwdPrice(spot, timeToExp, intRate, divYield);
  double sigT = volatility * sqrt(timeToExp);
  double sig2 = volatility * volatility;

  double epsilon = 1.0e-012;  // a very small hard-coded number
  double d1 = log(fwd / (strike + epsilon)) / sigT + 0.5 * sigT;
  double d2 = log(fwd / strike) / sigT - 0.5 * sigT;
  NormalDistribution normal;

  // precompute common quantities
  double df = exp(-intRate * timeToExp);
  double nd2 = normal.cdf(phi * d2);
  double nprd2 = normal.pdf(d2);
  double sqrtT = sqrt(timeToExp);
  double spot2 = spot * spot;

  // price and Greeks
  double price = df * nd2;
  double delta = phi * df * nprd2 / (spot * sigT);
  delta = sigT < epsilon ? 0.0 : delta;
  double gamma = -phi * df * d1 * nprd2 / (spot2 * sig2 * timeToExp);
  gamma = sigT < epsilon ? 0.0 : gamma;

  double theta = intRate * price;
  theta += phi * df * nprd2 * (log(spot/(strike + epsilon)) / timeToExp - (intRate - divYield - sig2 / 2) ) / 2.0 / sigT;
  theta = sigT < epsilon ? 0.0 : theta;

  double vega = -phi * df * strike * sqrtT * nprd2;
  vega *= 0.5 + log(fwd / strike) / sig2 / timeToExp;
  vega = sigT < epsilon ? 0.0 : vega;

  Vector vec(5);
  vec[0] = price;
  vec[1] = delta;
  vec[2] = gamma;
  vec[3] = theta;
  vec[4] = vega;

  return vec;
}


/** Price and Greeks of a European option in the Black-Scholes model*/
Vector europeanOptionBS(int payoffType, double spot, double strike, double timeToExp, 
                        double intRate, double divYield, double volatility)
{
  QF_ASSERT(payoffType == 1 || payoffType == -1, "payoffType must be 1 or -1");
  QF_ASSERT(strike >= 0.0, "strike must be non-negative");
  QF_ASSERT(volatility >= 0.0, "volatility must be non-negative");

  double phi = payoffType;
  double fwd = fwdPrice(spot, timeToExp, intRate, divYield);
  double sigT = volatility * sqrt(timeToExp);
  double d1 = log(fwd / strike) / sigT + 0.5 * sigT;
  double d2 = d1 - sigT;
  NormalDistribution normal;
  double epsilon = 1.0e-012;  // a very small hard-coded number

  // precompute common quantities
  double df = exp(-intRate * timeToExp);
  double qf = exp(-divYield * timeToExp);
  double nd1 = normal.cdf(phi * d1);
  double nd2 = normal.cdf(phi * d2);
  double nprd1 = normal.pdf(d1);      // the normal density     
  double sqrtT = sqrt(timeToExp);

  // price and Greeks
  double price = phi * df * (fwd * nd1 - strike * nd2);
  double delta = phi * qf * nd1;
  double gamma = qf * nprd1 / (spot * volatility * sqrtT);
  gamma = sigT < epsilon ? 0.0 : gamma;
  double theta = -qf * nprd1 * spot * volatility / (2.0 * sqrtT);
  theta += phi * divYield * qf * spot * nd1;
  theta -= phi * intRate * df * strike * nd2;
  theta = sqrtT < epsilon ? 0.0 : theta;
  double vega = qf * sqrtT * spot * nprd1;

  Vector vec(5);
  vec[0] = price;
  vec[1] = delta;
  vec[2] = gamma;
  vec[3] = theta;
  vec[4] = vega;

  return vec;
}

/** Price of a single point knock-out forward contract*/
double knockoutFwd(double spot, double strike, double kolevel,
  double timeToExp, double timeToKO,
  double intRate, double divYield, double volatility)
{
  QF_ASSERT(strike >= 0.0, "strike must be non-negative");
  QF_ASSERT(kolevel >= 0.0, "knock-out level must be non-negative");
  QF_ASSERT(timeToKO <= timeToExp, "time to knock out must be less or equal to expiration");
  QF_ASSERT(volatility >= 0.0, "volatility must be non-negative");

  double dfko = exp(-divYield * (timeToExp - timeToKO));
  double price = europeanOptionBS(1, spot, kolevel, timeToKO, intRate, divYield, volatility)[0];
  double digimult = (kolevel - exp(-(intRate - divYield) * (timeToExp - timeToKO)) * strike);
  price += digimult * digitalOptionBS(1, spot, kolevel, timeToKO,
    intRate, divYield, volatility)[0];

  price *= dfko;
  return price;
}

/** Price of a European caplet/floorlet in the Black-Scholes model*/
double capFloorletBS(int payoffType, SPtrYieldCurve spyc, double strikeRate,
  double timeToReset, double tenor, double fwdRateVol)
{
  QF_ASSERT(payoffType == 1 || payoffType == -1, "payoffType must be 1 or -1");
  QF_ASSERT(strikeRate >= 0.0, "strike fwd rate must be non-negative");
  QF_ASSERT(timeToReset >= 0.0, "time to reset must be non-negative");
  QF_ASSERT(tenor >= 0.0, "fwd rate tenor must be non-negative");
  QF_ASSERT(fwdRateVol >= 0.0, "fwd rate volatility must be non-negative");

  double epsilon = 1.0e-012;  // a very small hard-coded number
  double phi = payoffType;
  double timeToPay = timeToReset + tenor;                 // T2, payment time
  double frate = spyc->fwdRate(timeToReset, timeToPay);   // F(0, T1, T2)
  size_t annfreq = (size_t) (1.0 / tenor + epsilon);
  frate = fromContCmpd(frate, annfreq);
  double df = spyc->discount(timeToPay);                  // P(0, T2)
  double pervol = fwdRateVol * std::sqrt(timeToReset);          // sigma*sqrt(T2-T1)

  double d1 = log(frate / strikeRate) / pervol + 0.5 * pervol;
  double d2 = d1 - pervol;
  NormalDistribution normal;

  // precompute common quantities
  double nd1 = normal.cdf(phi * d1);
  double nd2 = normal.cdf(phi * d2);
  double nprd1 = normal.pdf(d1);      // the normal density     

  double price = phi * df * (frate * nd1 - strikeRate * nd2) * tenor;

  return price;
}

/** Present value of a credit default swap */
Vector cdsPV(SPtrYieldCurve sprfyc, double credSprd, double cdsRate,
                  double recov, double timeToMat, size_t payFreq)
{
  QF_ASSERT(credSprd > 0.0, "credit spread must be non-negative");
  QF_ASSERT(cdsRate >= 0.0, "CDS rate must be non-negative");
  QF_ASSERT(recov >= 0.0 && recov <= 1.0, "recovery must be between 0.0 and 1.0");
  QF_ASSERT(timeToMat >= 0.0, "time to maturity must be non-negative");
  QF_ASSERT(payFreq >= 1, "lay frequency must be positive");

  double DeltaT = 1.0 / payFreq;                            // regular observation/accrual period
  size_t npay = (size_t) std::ceil(timeToMat * payFreq);    // number of periods within timeToMat
  double epsilon = 1.0e-012;  // a very small hard-coded number

  if (npay == 0)
    return Vector(2, arma::fill::zeros);

  Vector paytimes(npay);
  paytimes.fill(timeToMat);
  for (size_t i = 0; i < npay; ++i) {
    paytimes[npay - i - 1] -= i * DeltaT;
  }

  Vector survprob(npay);
  survprob.fill(1.0);
  for (size_t i = 0; i < npay; ++i) {
    survprob[i] = std::exp(-credSprd * paytimes[i]) - recov;
    survprob[i] = survprob[i] > 0.0 ? survprob[i] : 0.0;  // survival prob cannot be negative!
    survprob[i] /= (1.0 - recov + epsilon);               // add epsilon to handle the case recov=1
  }

  double pvpl = 0.0;
  double pvdl = 0.0;

  for (size_t i = 0; i < npay; ++i) {
    double df = sprfyc->discount(paytimes[i]);
    double DeltaT = i == 0 ? paytimes[i] : paytimes[i] - paytimes[i - 1];
    pvpl += cdsRate *  DeltaT * survprob[i] * df;
    double defprob = i == 0 ? (1 - survprob[i]) : survprob[i - 1] - survprob[i];
    pvdl += (1.0 - recov) * defprob * df;
  }
  Vector ret(2);
  ret[0] = pvdl;
  ret[1] = pvpl;

  return ret;
}

END_NAMESPACE(qf)

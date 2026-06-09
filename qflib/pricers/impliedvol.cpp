/**
@file  impliedvol.cpp
@brief Implementation of implied volatility inversion
*/
#include <qflib/pricers/impliedvol.hpp>
#include <qflib/pricers/simplepricers.hpp>
#include <cmath>

BEGIN_NAMESPACE(qf)

double impliedVol(int payoffType, double spot, double strike, double timeToExp,
                  double intRate, double divYield, double marketPrice)
{
  QF_ASSERT(payoffType == 1 || payoffType == -1, "payoffType must be 1 or -1");
  QF_ASSERT(marketPrice >= 0.0, "market price must be non-negative");

  const int    MAXIT = 100;
  const double XACC  = 1.0e-8;
  double sig = 0.2;                   // initial guess: 20% vol

  for (int i = 0; i < MAXIT; ++i) {
    Vector res  = europeanOptionBS(payoffType, spot, strike, timeToExp,
                                   intRate, divYield, sig);
    double diff = res[0] - marketPrice;
    if (std::abs(diff) < XACC) return sig;
    double vega = res[4];
    QF_ASSERT(std::abs(vega) > 1.0e-14,
              "impliedVol: vega too small — price may be outside BS range");
    sig -= diff / vega;
    if (sig < XACC) sig = XACC;      // keep vol positive
  }
  QF_ASSERT(0, "impliedVol: Newton-Raphson did not converge");
  return 0.0;
}

END_NAMESPACE(qf)

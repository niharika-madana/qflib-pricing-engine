/**
@file  impliedvol.hpp
@brief Implied Black-Scholes volatility from European option market prices
*/
#pragma once
#include <qflib/defines.hpp>
#include <qflib/exception.hpp>

BEGIN_NAMESPACE(qf)

/** Implied BS vol via Newton-Raphson on the vega.
    Returns sigma such that europeanOptionBS(sigma) == marketPrice. */
double impliedVol(int payoffType, double spot, double strike, double timeToExp,
                  double intRate, double divYield, double marketPrice);

END_NAMESPACE(qf)

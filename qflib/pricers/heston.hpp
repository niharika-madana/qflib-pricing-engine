/**
@file  heston.hpp
@brief Heston stochastic volatility model (Heston 1993)

  dS   = (r-q) S dt + sqrt(v) S dW1
  dv   = kappa*(theta-v) dt + xi*sqrt(v) dW2
  dW1 dW2 = rho dt
*/
#pragma once
#include <qflib/defines.hpp>
#include <qflib/exception.hpp>
#include <qflib/math/matrix.hpp>

BEGIN_NAMESPACE(qf)

struct HestonParams {
  double v0;     ///< initial variance              (> 0)
  double kappa;  ///< mean-reversion speed           (> 0)
  double theta;  ///< long-run variance              (> 0)
  double xi;     ///< vol of vol                     (> 0)
  double rho;    ///< asset/variance correlation     (-1, 1)
};

/** European call price via Heston characteristic function.
    Uses Gil-Pelaez inversion with composite Simpson quadrature. */
double hestonCall(double S, double K, double T, double r, double q,
                  HestonParams const& p);

/** Black-Scholes implied vol corresponding to a Heston price.
    payoffType: 1=call, -1=put (put priced via put-call parity). */
double hestonImpliedVol(int payoffType, double S, double K, double T,
                        double r, double q, HestonParams const& p);

/** Calibrate all 5 Heston params jointly to a market vol surface.
    marketVols: nK x nT matrix, entry (i,j) = market implied vol at
                (strikes[i], maturities[j]).
    All maturities are fitted simultaneously — one consistent parameter set. */
HestonParams hestonCalibrate(Matrix const& marketVols,
                             Vector const& strikes,
                             Vector const& maturities,
                             double S, double r, double q,
                             HestonParams const& x0);

END_NAMESPACE(qf)

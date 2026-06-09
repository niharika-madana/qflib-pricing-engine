/**
@file  heston.cpp
@brief Implementation of Heston model pricing and calibration
*/
#include <qflib/pricers/heston.hpp>
#include <qflib/pricers/impliedvol.hpp>
#include <qflib/math/optim/gaussnewton.hpp>
#include <complex>
#include <cmath>

BEGIN_NAMESPACE(qf)

// ── characteristic function ──────────────────────────────────────────────────
//
// Returns E^Q[ e^{iz * ln(S_T)} ] for complex argument z.
//
// Uses the Albrecher et al. (2007) formulation to avoid branch-cut
// discontinuities that arise in the original Heston (1993) form.
//
// d  = sqrt( (kappa - rho*xi*iz)^2 + xi^2*(iz + z^2) )
// g  = (kappa - rho*xi*iz - d) / (kappa - rho*xi*iz + d)
// C  = (kappa-rho*xi*iz-d)*T - 2*ln( (1 - g*e^{-dT}) / (1-g) )
// D  = (kappa-rho*xi*iz-d) / xi^2  *  (1-e^{-dT}) / (1 - g*e^{-dT})
//
static std::complex<double>
hestonCF(std::complex<double> z,
         double logS, double v0, double kappa, double theta,
         double xi,   double rho, double r, double q, double T)
{
  using cd = std::complex<double>;
  const cd I(0.0, 1.0);

  cd iz    = I * z;
  cd kterm = cd(kappa, 0.0) - rho * xi * iz;     // kappa - rho*xi*iz
  cd d     = std::sqrt(kterm * kterm
             + xi * xi * (iz + z * z));           // the "d" function

  cd g     = (kterm - d) / (kterm + d);
  cd expdT = std::exp(-d * T);

  cd C = (kterm - d) * T
       - 2.0 * std::log((1.0 - g * expdT) / (1.0 - g));
  cd D = (kterm - d) / (xi * xi)
       * (1.0 - expdT) / (1.0 - g * expdT);

  return std::exp(iz * (logS + (r - q) * T))
       * std::exp(kappa * theta / (xi * xi) * C + v0 * D);
}

// ── European call price ───────────────────────────────────────────────────────
//
// Gil-Pelaez two-probability inversion:
//
//   C = S*e^{-qT}*P1 - K*e^{-rT}*P2
//
//   P_j = 1/2 + 1/pi * integral_0^inf  Re[ integrand_j(u) ] du
//
//   integrand_2(u) = phi(u)    * e^{-iu*lnK} / (iu)
//   integrand_1(u) = phi(u-i)  * e^{-iu*lnK} / (iu * phi(-i))
//
// phi(-i) = E[S_T] = S * e^{(r-q)*T}  (the forward price)
//
double hestonCall(double S, double K, double T, double r, double q,
                  HestonParams const& p)
{
  QF_ASSERT(S > 0.0 && K > 0.0 && T > 0.0,
            "hestonCall: S, K, T must be positive");
  QF_ASSERT(p.v0 > 0.0 && p.kappa > 0.0 && p.theta > 0.0 && p.xi > 0.0,
            "hestonCall: v0, kappa, theta, xi must be positive");
  QF_ASSERT(p.rho > -1.0 && p.rho < 1.0,
            "hestonCall: rho must be in (-1, 1)");

  using cd = std::complex<double>;
  const cd I(0.0, 1.0);

  const double U_MAX = 100.0;
  const int    N     = 200;         // even — required for Simpson's rule
  const double h     = U_MAX / N;
  const double logS  = std::log(S);
  const double logK  = std::log(K);

  // phi(-i) = forward price S*e^{(r-q)*T}
  cd phi_neg_i = hestonCF(cd(0.0, -1.0), logS,
                           p.v0, p.kappa, p.theta, p.xi, p.rho, r, q, T);

  double sumP1 = 0.0, sumP2 = 0.0;

  for (int j = 0; j <= N; ++j) {
    double u = (j == 0) ? 1.0e-6 : j * h;   // skip u=0, limit is finite but avoids 1/(iu)

    cd eniulK = std::exp(-I * u * logK);      // e^{-iu*lnK}

    // P2: phi(u) real-axis evaluation
    cd phi_u  = hestonCF(cd(u, 0.0), logS,
                          p.v0, p.kappa, p.theta, p.xi, p.rho, r, q, T);
    double i2 = (phi_u * eniulK / (I * u)).real();

    // P1: phi(u - i) — shift argument by -i
    cd phi_ui = hestonCF(cd(u, -1.0), logS,
                          p.v0, p.kappa, p.theta, p.xi, p.rho, r, q, T);
    double i1 = (phi_ui * eniulK / (I * u * phi_neg_i)).real();

    // Simpson weights: 1, 4, 2, 4, 2, ..., 4, 1
    double w = (j == 0 || j == N) ? 1.0 : (j % 2 == 1 ? 4.0 : 2.0);
    sumP1 += w * i1;
    sumP2 += w * i2;
  }

  const double INV_PI = 1.0 / M_PI;
  double P1 = 0.5 + INV_PI * (h / 3.0) * sumP1;
  double P2 = 0.5 + INV_PI * (h / 3.0) * sumP2;

  return S * std::exp(-q * T) * P1 - K * std::exp(-r * T) * P2;
}

// ── implied vol wrapper ───────────────────────────────────────────────────────

double hestonImpliedVol(int payoffType, double S, double K, double T,
                        double r, double q, HestonParams const& p)
{
  QF_ASSERT(payoffType == 1 || payoffType == -1, "payoffType must be 1 or -1");

  double callPrice = hestonCall(S, K, T, r, q, p);

  if (payoffType == -1)                         // put via put-call parity
    callPrice = callPrice - S * std::exp(-q * T) + K * std::exp(-r * T);

  return impliedVol(payoffType, S, K, T, r, q, callPrice);
}

// ── joint multi-maturity calibration ─────────────────────────────────────────

HestonParams hestonCalibrate(Matrix const& marketVols,
                             Vector const& strikes,
                             Vector const& maturities,
                             double S, double r, double q,
                             HestonParams const& x0)
{
  QF_ASSERT(marketVols.n_rows == strikes.n_elem &&
            marketVols.n_cols == maturities.n_elem,
            "hestonCalibrate: marketVols must be nStrikes x nMaturities");

  // calibration state: x = [v0, kappa, theta, xi, rho]
  Vector x  = { x0.v0, x0.kappa, x0.theta, x0.xi, x0.rho };
  Vector lo = { 1.0e-6,  0.1,    1.0e-6,   1.0e-6, -0.999 };
  Vector hi = { 2.0,    20.0,    2.0,       5.0,    0.999  };

  size_t nK = strikes.n_elem;
  size_t nT = maturities.n_elem;

  auto residuals = [&](Vector const& xv) -> Vector {
    HestonParams p{ xv[0], xv[1], xv[2], xv[3], xv[4] };
    Vector res(nK * nT);

    for (size_t j = 0; j < nT; ++j) {
      double T_j = maturities[j];
      double F_j = S * std::exp((r - q) * T_j);

      for (size_t i = 0; i < nK; ++i) {
        double K_i  = strikes[i];
        int ptype   = (K_i <= F_j) ? 1 : -1;   // ITM options for stability
        double mVol = marketVols(i, j);
        double hVol = hestonImpliedVol(ptype, S, K_i, T_j, r, q, p);
        res[j * nK + i] = hVol - mVol;
      }
    }
    return res;
  };

  gaussNewton(x, lo, hi, residuals);
  return HestonParams{ x[0], x[1], x[2], x[3], x[4] };
}

END_NAMESPACE(qf)

/**
@file  volsurface.cpp
*/
#include <qflib/market/volsurface.hpp>
#include <cmath>
#include <algorithm>

BEGIN_NAMESPACE(qf)

VolatilitySurface::VolatilitySurface(Vector const& strikes,
                                     Vector const& maturities,
                                     Matrix const& vols)
  : strikes_(strikes), maturities_(maturities), vols_(vols)
{
  QF_ASSERT(strikes_.n_elem >= 2,    "VolatilitySurface: need at least 2 strikes");
  QF_ASSERT(maturities_.n_elem >= 2, "VolatilitySurface: need at least 2 maturities");
  QF_ASSERT(vols_.n_rows == strikes_.n_elem && vols_.n_cols == maturities_.n_elem,
            "VolatilitySurface: vol matrix dimensions mismatch");
  checkArbitrage();
}

void VolatilitySurface::checkArbitrage() const
{
  // calendar spread: total variance must be non-decreasing in T at each strike
  for (size_t i = 0; i < strikes_.n_elem; ++i) {
    double prevVar = 0.0;
    for (size_t j = 0; j < maturities_.n_elem; ++j) {
      double var = vols_(i, j) * vols_(i, j) * maturities_[j];
      QF_ASSERT(var >= prevVar - 1.0e-8,
                "VolatilitySurface: calendar spread arbitrage at strike "
                + std::to_string(strikes_[i]));
      prevVar = var;
    }
  }
}

double VolatilitySurface::impliedVol(double K, double T) const
{
  // clamp to grid boundaries
  K = std::max(strikes_[0],    std::min(K, strikes_[strikes_.n_elem - 1]));
  T = std::max(maturities_[0], std::min(T, maturities_[maturities_.n_elem - 1]));

  // bracket in K
  size_t i1 = strikes_.n_elem - 2;
  for (size_t i = 0; i < strikes_.n_elem - 1; ++i)
    if (K <= strikes_[i + 1]) { i1 = i; break; }
  size_t i2 = i1 + 1;
  double wK = (strikes_[i2] > strikes_[i1])
              ? (K - strikes_[i1]) / (strikes_[i2] - strikes_[i1]) : 0.0;

  // bracket in T
  size_t j1 = maturities_.n_elem - 2;
  for (size_t j = 0; j < maturities_.n_elem - 1; ++j)
    if (T <= maturities_[j + 1]) { j1 = j; break; }
  size_t j2 = j1 + 1;
  double wT = (maturities_[j2] > maturities_[j1])
              ? (T - maturities_[j1]) / (maturities_[j2] - maturities_[j1]) : 0.0;

  // bilinear interpolation on the four corners
  return (1 - wK) * (1 - wT) * vols_(i1, j1)
       +      wK  * (1 - wT) * vols_(i2, j1)
       + (1 - wK) *      wT  * vols_(i1, j2)
       +      wK  *      wT  * vols_(i2, j2);
}

double VolatilitySurface::totalVariance(double K, double T) const
{
  double v = impliedVol(K, T);
  return v * v * T;
}

double VolatilitySurface::atmVol(double T, double forward) const
{
  return impliedVol(forward, T);
}

END_NAMESPACE(qf)

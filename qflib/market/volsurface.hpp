/**
@file  volsurface.hpp
@brief 2D implied volatility surface with bilinear interpolation
*/
#pragma once
#include <qflib/defines.hpp>
#include <qflib/exception.hpp>
#include <qflib/math/matrix.hpp>
#include <memory>

BEGIN_NAMESPACE(qf)

/** 2D implied vol surface on a rectangular (strike x maturity) grid.
    Calendar-spread arbitrage is checked on construction.
    Bilinear interpolation; queries outside the grid are clamped to the boundary. */
class VolatilitySurface
{
public:
  /** strikes:    ascending, length nK
      maturities: ascending in years, length nT
      vols:       nK x nT matrix — entry (i,j) = sigma(strikes[i], maturities[j]) */
  VolatilitySurface(Vector const& strikes, Vector const& maturities,
                    Matrix const& vols);

  /** Interpolated implied vol at (K, T). */
  double impliedVol(double K, double T) const;

  /** sigma^2 * T — needed for Dupire local vol. */
  double totalVariance(double K, double T) const;

  /** ATM vol: strike = forward. */
  double atmVol(double T, double forward) const;

  Vector const& strikes()    const { return strikes_;    }
  Vector const& maturities() const { return maturities_; }
  Matrix const& vols()       const { return vols_;       }

private:
  void checkArbitrage() const;

  Vector strikes_;
  Vector maturities_;
  Matrix vols_;         // nK x nT
};

using SPtrVolatilitySurface = std::shared_ptr<VolatilitySurface>;

END_NAMESPACE(qf)

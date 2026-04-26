/**
@file  market.hpp
@brief Definition of the market singleton and the market() free function
*/

#pragma once

#include <qflib/defines.hpp>
#include <qflib/exception.hpp>
#include <qflib/sptrmap.hpp>
#include <qflib/market/yieldcurve.hpp>
#include <qflib/market/volatilitytermstructure.hpp>

BEGIN_NAMESPACE(qf)

class Market
{
public:

  /** Returns the unique instance */
  static Market& instance();

  /** Clears the market of all objects */
  void clear();

  /** Returns the yield curves map */
  SPtrMap<YieldCurve>& yieldCurves() { return ycmap_; }

  /** Returns the volatility termstructure map */
  SPtrMap<VolatilityTermStructure>& volatilities() { return volmap_; }

private:

  /** allow private default ctor */
  Market() {}

  /** forbid copy ctor, copy-assignment, move ctor and move assignment */
  Market(Market const& rhs) = delete;
  Market& operator=(Market const&) = delete;
  Market(Market&& rhs) = delete;
  Market& operator=(Market&&) = delete;

  // state
  SPtrMap<YieldCurve> ycmap_;
  SPtrMap<VolatilityTermStructure> volmap_;
};

/** Free function returning the market singleton */
Market& market();

END_NAMESPACE(qf)

/**
@file  bsmcpricer.hpp
@brief Monte Carlo pricer in the Black Scholes model
*/

#pragma once

#include <qflib/products/product.hpp>
#include <qflib/market/yieldcurve.hpp>
#include <qflib/market/volatilitytermstructure.hpp>
#include <qflib/methods/montecarlo/mcparams.hpp>
#include <qflib/methods/montecarlo/pathgenerator.hpp>
#include <qflib/methods/montecarlo/eulerpathgenerator.hpp>
#include <qflib/math/stats/statisticscalculator.hpp>

BEGIN_NAMESPACE(qf)

/** Monte Carlo pricer in the Black-Scholes model (deterministic rates and vols).
*/
class BsMcPricer
{
public:
  /** Initializing ctor */
  BsMcPricer(SPtrProduct prod,
             SPtrYieldCurve discountYieldCurve,
             double divYield,
             SPtrVolatilityTermStructure volatility,
             double spot,
             McParams mcparams);

  /** Returns the number of variables that can be tracked for stats */
  size_t nVariables();

  /** Runs the simulation and collects statistics */
  template<typename ITER>
  void simulate(StatisticsCalculator<ITER>& statsCalc, unsigned long npaths);

protected:

  /** Creates and processes one price path.
      It returns the PV of the product
      */
  double processOnePath(Matrix& pricePath);

private:
  SPtrProduct prod_;      // pointer to the product
  SPtrYieldCurve discyc_; // pointer to the discount curve
  double divyld_;         // the constant dividend yield   
  SPtrVolatilityTermStructure vol_;            // the volatility term structure
  double spot_;           // the initial spot
  McParams mcparams_;     // the Monte Carlo parameters

  SPtrPathGenerator pathgen_;  // pointer to the path generator
  Vector discfactors_;         // caches the pre-computed discount factors
  Vector drifts_;              // caches the pre-computed asset drifts
  Vector stdevs_;              // caches the pre-computed standard deviations 

  Vector payamts_;             // scratch array for writing the payments after each simulation
};

///////////////////////////////////////////////////////////////////////////////
// Inline definitions

inline
size_t BsMcPricer::nVariables()
{
  return 1;
}

template<typename ITER>
void BsMcPricer::simulate(StatisticsCalculator<ITER>& statsCalc, unsigned long npaths)
{
  // create the price path matrix
  Matrix pricePath(pathgen_->nTimeSteps(), pathgen_->nFactors());
  // check the size of the statistics calcuilator
  QF_ASSERT(statsCalc.nVariables() == nVariables(), "the statistics calculator must track only one variable!");

  // This is the HOT loop
  for (unsigned long i = 0; i < npaths; ++i) {
    double pv = processOnePath(pricePath);
    statsCalc.addSample(&pv, &pv + 1);
  }
}

END_NAMESPACE(qf)

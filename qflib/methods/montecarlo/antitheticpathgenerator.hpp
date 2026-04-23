/**
@file  antitheticpathgenerator.hpp
@brief Adds antithetic sampling to an existing path generator
*/

#pragma once

#include <qflib/methods/montecarlo/pathgenerator.hpp>

BEGIN_NAMESPACE(qf)

/** This class adds antithetic sampling capability to any path generator
*/
class AntitheticPathGenerator : public PathGenerator
{
public:
  /** Dtor */
  virtual ~AntitheticPathGenerator() {}

  /** Initializing ctor */
  AntitheticPathGenerator(SPtrPathGenerator pg);

  /** Returns the next price path.
      The Matrix is resized to size ntimesteps * nfactors
  */
  virtual void next(Matrix & pricePath) override;

protected:
  AntitheticPathGenerator() {}        // default ctor

  // state
  SPtrPathGenerator innerpathgen_;    // pointer to the inner path generator
  bool dogenerate_;                   // when dogenerate_ is true a new path must be generated
  Matrix pricePath_;                  // the cached generated path
};


///////////////////////////////////////////////////////////////////////////////
// Inline definitions
inline
AntitheticPathGenerator::AntitheticPathGenerator(SPtrPathGenerator pg)
: PathGenerator(*pg), innerpathgen_(pg), dogenerate_(true) {}

inline void
AntitheticPathGenerator::next(Matrix & pricePath)
{
  if (dogenerate_) {
    innerpathgen_->next(pricePath_);
    dogenerate_ = false;
  }
  else {
    pricePath_ *= -1.0;
    dogenerate_ = true;
  }
  pricePath = pricePath_;
}

END_NAMESPACE(qf)

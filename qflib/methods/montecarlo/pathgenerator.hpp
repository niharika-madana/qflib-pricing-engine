<<<<<<< HEAD
<<<<<<< HEAD
/**
@file  pathgenerator.hpp
@brief Base class for all Monte Carlo path generators
*/

#pragma once

#include <qflib/defines.hpp>
#include <qflib/exception.hpp>
#include <qflib/sptr.hpp>
#include <qflib/math/matrix.hpp>

BEGIN_NAMESPACE(qf)

/** The abstract base class for all Monte Carlo path generators.
    It must be inherited by specific path generators.
*/
class PathGenerator
{
public:
  /** Dtor */
  virtual ~PathGenerator() {}

  /** Returns the number of time steps */
  size_t nTimeSteps() const;

  /** Returns the number of simulated factors */
  size_t nFactors() const;

  /** Returns the next price path.
      The Matrix is resized to size ntimesteps * nfactors
  */
  virtual void next(qf::Matrix& pricePath) = 0;

protected:
  PathGenerator() {};     // default ctor
  PathGenerator(size_t ntimesteps, size_t nfactors, qf::Matrix const& correlation);

  // Does spectral truncation and Cholesky decomposition on the correlation matrix
  void initCorrelation(qf::Matrix const& correlation);

  size_t ntimesteps_;        // the number of time steps
  size_t nfactors_;          // the number of factors
  qf::Matrix sqrtCorrel_;    // the Cholesky factor of the correlation matrix
};

using SPtrPathGenerator = std::shared_ptr<PathGenerator>;

///////////////////////////////////////////////////////////////////////////////
// Inline definitions
inline
PathGenerator::PathGenerator(size_t ntimesteps, size_t nfactors, qf::Matrix const& correlMatrix)
: ntimesteps_(ntimesteps), nfactors_(nfactors)
{
  QF_ASSERT(correlMatrix.is_square(), "the correlation matrix is not square!");
  if (!correlMatrix.is_empty())
    QF_ASSERT(correlMatrix.n_rows == nfactors,
    "the correlation matrix number of rows is not equal to the number of factors!");
  initCorrelation(correlMatrix);
}

inline size_t PathGenerator::nTimeSteps() const
{
  return ntimesteps_;
}

inline size_t PathGenerator::nFactors() const
{
  return nfactors_;
}

END_NAMESPACE(qf)

=======
/**
@file  pathgenerator.hpp
@brief Base class for all Monte Carlo path generators
*/

#pragma once

#include <qflib/defines.hpp>
#include <qflib/exception.hpp>
#include <qflib/sptr.hpp>
#include <qflib/math/matrix.hpp>

BEGIN_NAMESPACE(qf)

/** The abstract base class for all Monte Carlo path generators.
    It must be inherited by specific path generators.
*/
class PathGenerator
{
public:
  /** Dtor */
  virtual ~PathGenerator() {}

  /** Returns the number of time steps */
  size_t nTimeSteps() const;

  /** Returns the number of simulated factors */
  size_t nFactors() const;

  /** Returns the next price path.
      The Matrix is resized to size ntimesteps * nfactors
  */
  virtual void next(qf::Matrix& pricePath) = 0;

protected:
  PathGenerator() {};     // default ctor
  PathGenerator(size_t ntimesteps, size_t nfactors, qf::Matrix const& correlation);

  // Does spectral truncation and Cholesky decomposition on the correlation matrix
  void initCorrelation(qf::Matrix const& correlation);

  size_t ntimesteps_;        // the number of time steps
  size_t nfactors_;          // the number of factors
  qf::Matrix sqrtCorrel_;    // the Cholesky factor of the correlation matrix
};

using SPtrPathGenerator = std::shared_ptr<PathGenerator>;

///////////////////////////////////////////////////////////////////////////////
// Inline definitions
inline
PathGenerator::PathGenerator(size_t ntimesteps, size_t nfactors, qf::Matrix const& correlMatrix)
: ntimesteps_(ntimesteps), nfactors_(nfactors)
{
  QF_ASSERT(correlMatrix.is_square(), "the correlation matrix is not square!");
  if (!correlMatrix.is_empty())
    QF_ASSERT(correlMatrix.n_rows == nfactors,
    "the correlation matrix number of rows is not equal to the number of factors!");
  initCorrelation(correlMatrix);
}

inline size_t PathGenerator::nTimeSteps() const
{
  return ntimesteps_;
}

inline size_t PathGenerator::nFactors() const
{
  return nfactors_;
}

END_NAMESPACE(qf)

>>>>>>> origin/yuyang-branch
=======
/**
@file  pathgenerator.hpp
@brief Base class for all Monte Carlo path generators
*/

#pragma once

#include <qflib/defines.hpp>
#include <qflib/exception.hpp>
#include <qflib/sptr.hpp>
#include <qflib/math/matrix.hpp>

BEGIN_NAMESPACE(qf)

/** The abstract base class for all Monte Carlo path generators.
    It must be inherited by specific path generators.
*/
class PathGenerator
{
public:
  /** Dtor */
  virtual ~PathGenerator() {}

  /** Returns the number of time steps */
  size_t nTimeSteps() const;

  /** Returns the number of simulated factors */
  size_t nFactors() const;

  /** Returns the next price path.
      The Matrix is resized to size ntimesteps * nfactors
  */
  virtual void next(qf::Matrix& pricePath) = 0;

protected:
  PathGenerator() {};     // default ctor
  PathGenerator(size_t ntimesteps, size_t nfactors, qf::Matrix const& correlation);

  // Does spectral truncation and Cholesky decomposition on the correlation matrix
  void initCorrelation(qf::Matrix const& correlation);

  size_t ntimesteps_;        // the number of time steps
  size_t nfactors_;          // the number of factors
  qf::Matrix sqrtCorrel_;    // the Cholesky factor of the correlation matrix
};

using SPtrPathGenerator = std::shared_ptr<PathGenerator>;

///////////////////////////////////////////////////////////////////////////////
// Inline definitions
inline
PathGenerator::PathGenerator(size_t ntimesteps, size_t nfactors, qf::Matrix const& correlMatrix)
: ntimesteps_(ntimesteps), nfactors_(nfactors)
{
  QF_ASSERT(correlMatrix.is_square(), "the correlation matrix is not square!");
  if (!correlMatrix.is_empty())
    QF_ASSERT(correlMatrix.n_rows == nfactors,
    "the correlation matrix number of rows is not equal to the number of factors!");
  initCorrelation(correlMatrix);
}

inline size_t PathGenerator::nTimeSteps() const
{
  return ntimesteps_;
}

inline size_t PathGenerator::nFactors() const
{
  return nfactors_;
}

END_NAMESPACE(qf)

>>>>>>> origin/fangyi-branch

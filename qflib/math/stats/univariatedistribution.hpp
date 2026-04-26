/**
@file  univariatedistribution.hpp
@brief Base class for all univariate distributions
*/

#pragma once

#include <qflib/defines.hpp>
#include <qflib/exception.hpp>

BEGIN_NAMESPACE(qf)

class UnivariateDistribution
{
public:
  /** Initializing ctor */
  UnivariateDistribution() {}

  /** Probability density function */
  virtual double pdf(double x) const = 0;

  /** Cumulative distribution function */
  virtual double cdf(double x) const = 0;

  /** Inverse cumulative distribution function */
  virtual double invcdf(double p) const = 0;
};

END_NAMESPACE(qf)

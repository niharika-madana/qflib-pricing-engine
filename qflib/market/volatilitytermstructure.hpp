<<<<<<< HEAD
/**
@file  volatilitytermstructure.hpp
@brief Class representing a volatility term structure
*/

#pragma once

#include <qflib/defines.hpp>
#include <qflib/exception.hpp>
#include <qflib/math/interpol/piecewisepolynomial.hpp>
#include <memory>
#include <string>

BEGIN_NAMESPACE(qf)

/** The volatility term structure */
class VolatilityTermStructure
{
public:
  enum class VolType { SPOTVOL, FWDVOL };

  template <typename XITER, typename YITER>
  VolatilityTermStructure(XITER tMatBegin,
                          XITER tMatEnd,
                          YITER volBegin,
                          YITER volEnd,
                          VolType vtype = VolType::SPOTVOL);

  /** Returns the spot rate at time tMat */
  double spotVol(double tMat) const;

  /** Returns the forward rate between times tMat1 and tMat2 */
  double fwdVol(double tMat1, double tMat2) const;

protected:
private:
  // helper functions
  void initFromSpotVols();
  void initFromFwdVols();

  PiecewisePolynomial fwdvars_;  // the piecewise constant forward variances
};

using SPtrVolatilityTermStructure = std::shared_ptr<VolatilityTermStructure>;

////////////////////////////////////////////////////////////////////////////.//
// Inline implementations

template <typename XITER, typename YITER>
VolatilityTermStructure::VolatilityTermStructure(XITER tMatBegin,
                                                 XITER tMatEnd,
                                                 YITER volBegin,
                                                 YITER volEnd,
                                                 VolType vtype)
  : fwdvars_(tMatBegin, tMatEnd, volBegin, 0)
{
  std::ptrdiff_t n = tMatEnd - tMatBegin;
  QF_ASSERT(n == volEnd - volBegin, "VolatilityTermStructure: different number of maturities and vols");
  auto it = std::find_if_not(tMatBegin, tMatEnd, [](double x) {return x > 0.0; });
  QF_ASSERT(it == tMatEnd, "VolatilityTermStructure: maturities must be positive");

  // NOTE: so far we have stored volatilites in the data member fwdvars_
  // These will be turned into variances in the init***() functions
  // This assumes that forward variances are constant between two breakpoints
  // Also, the breakpoints will be modified to start from 0.0 because PiecewisePolynomial is right continuous
  switch (vtype) {
  case VolatilityTermStructure::VolType::SPOTVOL:
    initFromSpotVols();
    break;
  case VolatilityTermStructure::VolType::FWDVOL:
    initFromFwdVols();
    break;
  default:
    QF_ASSERT(0, "VolatilityTermStructure: unknown volatility input type");
  }
}

END_NAMESPACE(qf)
=======
/**
@file  volatilitytermstructure.hpp
@brief Class representing a volatility term structure
*/

#pragma once

#include <qflib/defines.hpp>
#include <qflib/exception.hpp>
#include <qflib/math/interpol/piecewisepolynomial.hpp>
#include <memory>
#include <string>

BEGIN_NAMESPACE(qf)

/** The volatility term structure */
class VolatilityTermStructure
{
public:
  enum class VolType { SPOTVOL, FWDVOL };

  template <typename XITER, typename YITER>
  VolatilityTermStructure(XITER tMatBegin,
                          XITER tMatEnd,
                          YITER volBegin,
                          YITER volEnd,
                          VolType vtype = VolType::SPOTVOL);

  /** Returns the spot rate at time tMat */
  double spotVol(double tMat) const;

  /** Returns the forward rate between times tMat1 and tMat2 */
  double fwdVol(double tMat1, double tMat2) const;

protected:
private:
  // helper functions
  void initFromSpotVols();
  void initFromFwdVols();

  PiecewisePolynomial fwdvars_;  // the piecewise constant forward variances
};

using SPtrVolatilityTermStructure = std::shared_ptr<VolatilityTermStructure>;

////////////////////////////////////////////////////////////////////////////.//
// Inline implementations

template <typename XITER, typename YITER>
VolatilityTermStructure::VolatilityTermStructure(XITER tMatBegin,
                                                 XITER tMatEnd,
                                                 YITER volBegin,
                                                 YITER volEnd,
                                                 VolType vtype)
  : fwdvars_(tMatBegin, tMatEnd, volBegin, 0)
{
  std::ptrdiff_t n = tMatEnd - tMatBegin;
  QF_ASSERT(n == volEnd - volBegin, "VolatilityTermStructure: different number of maturities and vols");
  auto it = std::find_if_not(tMatBegin, tMatEnd, [](double x) {return x > 0.0; });
  QF_ASSERT(it == tMatEnd, "VolatilityTermStructure: maturities must be positive");

  // NOTE: so far we have stored volatilites in the data member fwdvars_
  // These will be turned into variances in the init***() functions
  // This assumes that forward variances are constant between two breakpoints
  // Also, the breakpoints will be modified to start from 0.0 because PiecewisePolynomial is right continuous
  switch (vtype) {
  case VolatilityTermStructure::VolType::SPOTVOL:
    initFromSpotVols();
    break;
  case VolatilityTermStructure::VolType::FWDVOL:
    initFromFwdVols();
    break;
  default:
    QF_ASSERT(0, "VolatilityTermStructure: unknown volatility input type");
  }
}

END_NAMESPACE(qf)
>>>>>>> origin/yuyang-branch

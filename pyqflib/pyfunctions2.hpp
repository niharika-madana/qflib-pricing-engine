/**
@file  pyfunctions2.hpp
@brief Implementation of Python callable functions
*/
#include <pyqflib/pyutils.hpp>

#include <qflib/defines.hpp>
#include <qflib/market/market.hpp>

static
PyObject*  pyQfMktList(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;

  std::vector<std::string> ycnames = qf::market().yieldCurves().list();
  std::vector<std::string> volnames = qf::market().volatilities().list();

  // return market contents as a Python dictionary
  PyObject* ret = PyDict_New();
  int ok = PyDict_SetItem(ret, asPyScalar("YieldCurves"), asPyList(ycnames));
  PyDict_SetItem(ret, asPyScalar("Volatilities"), asPyList(volnames));
  return ret;
PY_END;
}

static
PyObject*  pyQfMktClear(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;

  qf::market().clear();
  return asPyScalar(true);
PY_END;
}

static
PyObject*  pyQfYCCreate(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;

  PyObject* pyYCName(NULL);
  PyObject* pyTMats(NULL);
  PyObject* pyVals(NULL);
  PyObject* pyValType(NULL);
  if (!PyArg_ParseTuple(pyArgs, "OOOO", &pyYCName, &pyTMats, &pyVals, &pyValType))
    return NULL;

  std::string name = asString(pyYCName);
  qf::Vector tmats = asVector(pyTMats);
  qf::Vector vals = asVector(pyVals);

  int valtype = asInt(pyValType);
  qf::YieldCurve::InputType intype;
  switch (valtype) {
  case 0:
    intype = qf::YieldCurve::InputType::SPOTRATE;
    break;
  case 1:
    intype = qf::YieldCurve::InputType::FWDRATE;
    break;
  case 2:
    intype = qf::YieldCurve::InputType::ZEROBOND;
    break;
  default:
    QF_ASSERT(0, "error: unknown yield curve input type");
  }

  std::pair<std::string, unsigned long> pr =
    qf::market().yieldCurves().set(name,
      std::make_shared<qf::YieldCurve>(tmats.begin(), tmats.end(), vals.begin(), vals.end(), intype)
    );

  std::string tag = pr.first;
  return asPyScalar(tag);
PY_END;
}

static
PyObject*  pyQfDiscount(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;

  PyObject* pyCrvName(NULL);
  PyObject* pyMat(NULL);
  if (!PyArg_ParseTuple(pyArgs, "OO", &pyCrvName, &pyMat))
    return NULL;

  std::string name = asString(pyCrvName);
  double tmat = asDouble(pyMat);

  qf::SPtrYieldCurve spyc = qf::market().yieldCurves().get(name);
  QF_ASSERT(spyc, "error: yield curve " + name + " not found");

  double df = spyc->discount(tmat);
  return asPyScalar(df);
PY_END;
}

static
PyObject*  pyQfFwdDiscount(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;

  PyObject* pyCrvName(NULL);
  PyObject* pyMat1(NULL);
  PyObject* pyMat2(NULL);

  if (!PyArg_ParseTuple(pyArgs, "OOO", &pyCrvName, &pyMat1, &pyMat2))
    return NULL;

  std::string name = asString(pyCrvName);
  double T1 = asDouble(pyMat1);
  double T2 = asDouble(pyMat2);

  qf::SPtrYieldCurve spyc = qf::market().yieldCurves().get(name);
  QF_ASSERT(spyc, "error: yield curve " + name + " not found");

  double fdf = spyc->fwdDiscount(T1, T2);
  return asPyScalar(fdf);
PY_END;
}

static
PyObject*  pyQfSpotRate(PyObject* pyDummy, PyObject* pyArgs) 
{
PY_BEGIN;

  PyObject* pyCrvName(NULL);
  PyObject* pyMat(NULL);
  if (!PyArg_ParseTuple(pyArgs, "OO", &pyCrvName, &pyMat))
    return NULL;

  std::string name = asString(pyCrvName);
  double tmat = asDouble(pyMat);

  qf::SPtrYieldCurve spyc = qf::market().yieldCurves().get(name);
  QF_ASSERT(spyc, "error: yield curve " + name + " not found");

  double srate = spyc->spotRate(tmat);
  return asPyScalar(srate);
PY_END;
}

static
PyObject*  pyQfFwdRate(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;

  PyObject* pyCrvName(NULL);
  PyObject* pyMat1(NULL);
  PyObject* pyMat2(NULL);

  if (!PyArg_ParseTuple(pyArgs, "OOO", &pyCrvName, &pyMat1, &pyMat2))
    return NULL;

  std::string name = asString(pyCrvName);
  double T1 = asDouble(pyMat1);
  double T2 = asDouble(pyMat2);

  qf::SPtrYieldCurve spyc = qf::market().yieldCurves().get(name);
  QF_ASSERT(spyc, "error: yield curve " + name + " not found");

  double frate = spyc->fwdRate(T1, T2);
  return asPyScalar(frate);
PY_END;
}

static
PyObject*  pyQfVolCreate(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;

  PyObject* pyVolName(NULL);
  PyObject* pyTMats(NULL);
  PyObject* pyVals(NULL);
  PyObject* pyValType(NULL);
  if (!PyArg_ParseTuple(pyArgs, "OOOO", &pyVolName, &pyTMats, &pyVals, &pyValType))
    return NULL;

  std::string name = asString(pyVolName);
  qf::Vector tmats = asVector(pyTMats);
  qf::Vector vals = asVector(pyVals);

  int valtype = asInt(pyValType);
  qf::VolatilityTermStructure::VolType voltype;
  switch (valtype) {
  case 0:
    voltype = qf::VolatilityTermStructure::VolType::SPOTVOL;
    break;
  case 1:
    voltype = qf::VolatilityTermStructure::VolType::FWDVOL;
    break;
  default:
    QF_ASSERT(0, "error: unknown volatility input type");
  }

  std::pair<std::string, unsigned long> pr =
    qf::market().volatilities().set(name,
      std::make_shared<qf::VolatilityTermStructure>(tmats.begin(), tmats.end(), vals.begin(), vals.end(), voltype)
    );

  std::string tag = pr.first;
  return asPyScalar(tag);
PY_END;
}

static
PyObject*  pyQfSpotVol(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;

  PyObject* pyVolName(NULL);
  PyObject* pyMat(NULL);
  if (!PyArg_ParseTuple(pyArgs, "OO", &pyVolName, &pyMat))
    return NULL;

  std::string name = asString(pyVolName);
  double tmat = asDouble(pyMat);

  qf::SPtrVolatilityTermStructure spvol = qf::market().volatilities().get(name);
  QF_ASSERT(spvol, "error: volatility cruve " + name + " not found");

  double svol = spvol->spotVol(tmat);
  return asPyScalar(svol);
PY_END;
}

static
PyObject*  pyQfFwdVol(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;

  PyObject* pyVolName(NULL);
  PyObject* pyMat1(NULL);
  PyObject* pyMat2(NULL);

  if (!PyArg_ParseTuple(pyArgs, "OOO", &pyVolName, &pyMat1, &pyMat2))
    return NULL;

  std::string name = asString(pyVolName);
  double T1 = asDouble(pyMat1);
  double T2 = asDouble(pyMat2);

  qf::SPtrVolatilityTermStructure spvol = qf::market().volatilities().get(name);
  QF_ASSERT(spvol, "error: volatility curve " + name + " not found");

  double fvol = spvol->fwdVol(T1, T2);
  return asPyScalar(fvol);
PY_END;
}

static
PyObject*  pyQfCapFloorletBS(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;

  PyObject* pyPayType(NULL);
  PyObject* pyCrvName(NULL);
  PyObject* pyStrikeRate(NULL);
  PyObject* pyTimeToReset(NULL);
  PyObject* pyTenor(NULL);
  PyObject* pyFwdRateVol(NULL);

  if (!PyArg_ParseTuple(pyArgs, "OOOOOO", &pyPayType, &pyCrvName, &pyStrikeRate,
    &pyTimeToReset, &pyTenor, &pyFwdRateVol))
    return NULL;

  int payoffType = asInt(pyPayType);
  std::string ycname = asString(pyCrvName);
  double strikeRate = asDouble(pyStrikeRate);
  double T1 = asDouble(pyTimeToReset);
  double DeltaT = asDouble(pyTenor);      // tenor of fwd rate
  double fwdvol = asDouble(pyFwdRateVol);

  qf::SPtrYieldCurve spyc = qf::market().yieldCurves().get(ycname);
  QF_ASSERT(spyc, "error: yield curve " + ycname + " not found");

  double price = qf::capFloorletBS(payoffType, spyc, strikeRate, T1, DeltaT, fwdvol);
  return asPyScalar(price);
PY_END;
}

static
PyObject*  pyQfCDSPV(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;

  PyObject* pyCrvName(NULL);
  PyObject* pyCredSpread(NULL);
  PyObject* pyCdsRate(NULL);
  PyObject* pyRecov(NULL);
  PyObject* pyTimeToMat(NULL);
  PyObject* pyPayFreq(NULL);

  if (!PyArg_ParseTuple(pyArgs, "OOOOOO", &pyCrvName, &pyCredSpread, &pyCdsRate,
    &pyRecov, &pyTimeToMat, &pyPayFreq))
    return NULL;

  std::string ycname = asString(pyCrvName);
  double creadspread = asDouble(pyCredSpread);
  double cdsrate = asDouble(pyCdsRate);
  double recov = asDouble(pyRecov);
  double timetomat = asDouble(pyTimeToMat);
  int payfreq = asInt(pyPayFreq);

  qf::SPtrYieldCurve spyc = qf::market().yieldCurves().get(ycname);
  QF_ASSERT(spyc, "error: yield curve " + ycname + " not found");

  qf::Vector cdspv = cdsPV(spyc, creadspread, cdsrate, recov, timetomat, payfreq);
  return asPyList(arma::conv_to<std::vector<double>>::from(cdspv));

PY_END;
}

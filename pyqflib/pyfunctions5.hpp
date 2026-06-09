/**
@file  pyfunctions5.hpp
@brief Python bindings: impliedVol, Heston pricing/calibration, VolatilitySurface
*/
#include <pyqflib/pyutils.hpp>
#include <qflib/pricers/impliedvol.hpp>
#include <qflib/pricers/heston.hpp>
#include <qflib/market/volsurface.hpp>
#include <qflib/market/market.hpp>

// ── implied vol ──────────────────────────────────────────────────────────────

static PyObject* pyQfImpliedVol(PyObject*, PyObject* pyArgs)
{
PY_BEGIN;
  PyObject *pyPt, *pySp, *pySk, *pyT, *pyR, *pyQ, *pyMp;
  if (!PyArg_ParseTuple(pyArgs, "OOOOOOO",
      &pyPt, &pySp, &pySk, &pyT, &pyR, &pyQ, &pyMp))
    return NULL;
  return asPyScalar(qf::impliedVol(
    asInt(pyPt), asDouble(pySp), asDouble(pySk),
    asDouble(pyT), asDouble(pyR), asDouble(pyQ), asDouble(pyMp)));
PY_END;
}

// ── Heston call price ────────────────────────────────────────────────────────

static PyObject* pyQfHestonCall(PyObject*, PyObject* pyArgs)
{
PY_BEGIN;
  PyObject *pyS, *pyK, *pyT, *pyR, *pyQ;
  PyObject *pyV0, *pyKappa, *pyTheta, *pyXi, *pyRho;
  if (!PyArg_ParseTuple(pyArgs, "OOOOOOOOOO",
      &pyS, &pyK, &pyT, &pyR, &pyQ,
      &pyV0, &pyKappa, &pyTheta, &pyXi, &pyRho))
    return NULL;
  qf::HestonParams p{ asDouble(pyV0),   asDouble(pyKappa),
                      asDouble(pyTheta), asDouble(pyXi), asDouble(pyRho) };
  return asPyScalar(qf::hestonCall(
    asDouble(pyS), asDouble(pyK), asDouble(pyT),
    asDouble(pyR), asDouble(pyQ), p));
PY_END;
}

// ── Heston implied vol ───────────────────────────────────────────────────────

static PyObject* pyQfHestonVol(PyObject*, PyObject* pyArgs)
{
PY_BEGIN;
  PyObject *pyPt, *pyS, *pyK, *pyT, *pyR, *pyQ;
  PyObject *pyV0, *pyKappa, *pyTheta, *pyXi, *pyRho;
  if (!PyArg_ParseTuple(pyArgs, "OOOOOOOOOOO",
      &pyPt, &pyS, &pyK, &pyT, &pyR, &pyQ,
      &pyV0, &pyKappa, &pyTheta, &pyXi, &pyRho))
    return NULL;
  qf::HestonParams p{ asDouble(pyV0),   asDouble(pyKappa),
                      asDouble(pyTheta), asDouble(pyXi), asDouble(pyRho) };
  return asPyScalar(qf::hestonImpliedVol(
    asInt(pyPt), asDouble(pyS), asDouble(pyK), asDouble(pyT),
    asDouble(pyR), asDouble(pyQ), p));
PY_END;
}

// ── Heston calibration ───────────────────────────────────────────────────────

static PyObject* pyQfHestonCalibrate(PyObject*, PyObject* pyArgs)
{
PY_BEGIN;
  PyObject *pyMktVols, *pyStrikes, *pyMats;
  PyObject *pyS, *pyR, *pyQ;
  PyObject *pyV0, *pyKappa, *pyTheta, *pyXi, *pyRho;
  if (!PyArg_ParseTuple(pyArgs, "OOOOOOOOOOO",
      &pyMktVols, &pyStrikes, &pyMats,
      &pyS, &pyR, &pyQ,
      &pyV0, &pyKappa, &pyTheta, &pyXi, &pyRho))
    return NULL;

  qf::HestonParams x0{ asDouble(pyV0),   asDouble(pyKappa),
                       asDouble(pyTheta), asDouble(pyXi), asDouble(pyRho) };

  qf::HestonParams fit = qf::hestonCalibrate(
    asMatrix(pyMktVols), asVector(pyStrikes), asVector(pyMats),
    asDouble(pyS), asDouble(pyR), asDouble(pyQ), x0);

  PyObject* d = PyDict_New();
  PyDict_SetItemString(d, "V0",    asPyScalar(fit.v0));
  PyDict_SetItemString(d, "Kappa", asPyScalar(fit.kappa));
  PyDict_SetItemString(d, "Theta", asPyScalar(fit.theta));
  PyDict_SetItemString(d, "Xi",    asPyScalar(fit.xi));
  PyDict_SetItemString(d, "Rho",   asPyScalar(fit.rho));
  return d;
PY_END;
}

// ── VolatilitySurface ────────────────────────────────────────────────────────

static PyObject* pyQfVSCreate(PyObject*, PyObject* pyArgs)
{
PY_BEGIN;
  PyObject *pyName, *pyStrikes, *pyMats, *pyVols;
  if (!PyArg_ParseTuple(pyArgs, "OOOO",
      &pyName, &pyStrikes, &pyMats, &pyVols))
    return NULL;
  std::string name = asString(pyName);
  auto sp = std::make_shared<qf::VolatilitySurface>(
    asVector(pyStrikes), asVector(pyMats), asMatrix(pyVols));
  qf::market().volSurfaces().set(name, sp);
  return asPyScalar(name);
PY_END;
}

static PyObject* pyQfVSImpliedVol(PyObject*, PyObject* pyArgs)
{
PY_BEGIN;
  PyObject *pyName, *pyK, *pyT;
  if (!PyArg_ParseTuple(pyArgs, "OOO", &pyName, &pyK, &pyT))
    return NULL;
  auto sp = qf::market().volSurfaces().get(asString(pyName));
  QF_ASSERT(sp != nullptr, "vsImpliedVol: surface not found");
  return asPyScalar(sp->impliedVol(asDouble(pyK), asDouble(pyT)));
PY_END;
}

static PyObject* pyQfVSTotalVar(PyObject*, PyObject* pyArgs)
{
PY_BEGIN;
  PyObject *pyName, *pyK, *pyT;
  if (!PyArg_ParseTuple(pyArgs, "OOO", &pyName, &pyK, &pyT))
    return NULL;
  auto sp = qf::market().volSurfaces().get(asString(pyName));
  QF_ASSERT(sp != nullptr, "vsTotalVar: surface not found");
  return asPyScalar(sp->totalVariance(asDouble(pyK), asDouble(pyT)));
PY_END;
}

static PyObject* pyQfVSAtmVol(PyObject*, PyObject* pyArgs)
{
PY_BEGIN;
  PyObject *pyName, *pyT, *pyFwd;
  if (!PyArg_ParseTuple(pyArgs, "OOO", &pyName, &pyT, &pyFwd))
    return NULL;
  auto sp = qf::market().volSurfaces().get(asString(pyName));
  QF_ASSERT(sp != nullptr, "vsAtmVol: surface not found");
  return asPyScalar(sp->atmVol(asDouble(pyT), asDouble(pyFwd)));
PY_END;
}

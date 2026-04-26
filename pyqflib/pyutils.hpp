/**
@file  pyutils.hpp
@brief Utility functions for Python to qflib bidirectional type translation.
*/

#pragma once

#include <qflib/math/matrix.hpp>
#include <qflib/methods/montecarlo/mcparams.hpp>
#include <qflib/methods/pde/pdeparams.hpp>
#include <pyqflib/pycpp.hpp>   // NOTE: include the python headers last (before armadillo)

/** utility function for trimming strings */
inline
std::string trim(const std::string &s)
{
  auto wsfront = std::find_if_not(s.begin(), s.end(), ::isspace);
  auto wsback = std::find_if_not(s.rbegin(), s.rend(), ::isspace).base();
  return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
}

/** Converts a numpy 1-D array to an qf::Vector.
*/
static qf::Vector asVector(PyObject* pyVec)
{
  return qf::Vector(asDblVec(pyVec));
}

/** Converts an qf::Vector to a numpy vector
*/
static PyObject* asNumpy(qf::Vector const & vec)
{
  return asPyArray(arma::conv_to<std::vector<double>>::from(vec));
}

/** Converts a numpy 2-D array to an qf::Matrix.
*/
static qf::Matrix asMatrix(PyObject* pyMat)
{
  std::vector<std::vector<double>> dvecvec = asDblVecVec(pyMat);
  size_t nrows = dvecvec.size();
  size_t ncols = dvecvec.front().size();
  qf::Matrix mat(nrows, ncols);
  for (size_t i = 0; i < nrows; ++i)
    for (size_t j = 0; j < ncols; ++j)
      mat(i, j) = dvecvec[i][j];
  return mat;
}

/** Converts an qf::Matrix to numpy
*/
static PyObject* asNumpy(qf::Matrix const & mat)
{
  size_t nrows = mat.n_rows;
  size_t ncols = mat.n_cols;
  std::vector<std::vector<double>> dvecvec(nrows);
  for (size_t i = 0; i < nrows; ++i) {
    dvecvec[i].resize(ncols);
    for (size_t j = 0; j < ncols; ++j)
      dvecvec[i][j] = mat(i, j);
  }
  return asPyArray(dvecvec);
}

/** Converts a Python dictionary with name-value pairs to an McParams structure.
*/
static qf::McParams asMcParams(PyObject* dict)
{
  QF_ASSERT(PyDict_Check(dict) == 1, "asMcParams: input param must be a dictionary");

  qf::McParams mcparams;
  std::string paramvalue;

  std::string paramname = "PATHGENTYPE";
  QF_ASSERT(PyDict_Contains(dict, asPyScalar(paramname)) == 1, 
    "asMcParams: input dictionary does not contain key PATHGENTYPE");
  paramvalue = asString(PyDict_GetItemString(dict, paramname.c_str()));
  paramvalue = trim(paramvalue);
  std::transform(paramvalue.begin(), paramvalue.end(), paramvalue.begin(), ::toupper);
  if (paramvalue == "EULER")
    mcparams.pathGenType = qf::McParams::PathGenType::EULER;
  else
    QF_ASSERT(0, "asMcParams: invalid value for McParam " + paramname + "!");

  paramname = "URNGTYPE";
  QF_ASSERT(PyDict_Contains(dict, asPyScalar(paramname)) == 1,
    "asMcParams: input dictionary does not contain key URNGTYPE");
  paramvalue = asString(PyDict_GetItemString(dict, paramname.c_str()));
  paramvalue = trim(paramvalue);
  std::transform(paramvalue.begin(), paramvalue.end(), paramvalue.begin(), ::toupper);
  if (paramvalue == "MINSTDRAND")
    mcparams.urngType = qf::McParams::UrngType::MINSTDRAND;
  else if (paramvalue == "MT19937")
    mcparams.urngType = qf::McParams::UrngType::MT19937;
  else if (paramvalue == "RANLUX3")
    mcparams.urngType = qf::McParams::UrngType::RANLUX3;
  else if (paramvalue == "RANLUX4")
    mcparams.urngType = qf::McParams::UrngType::RANLUX4;
  else
    QF_ASSERT(0, "asMcParams: invalid value for McParam " + paramname + "!");

  paramname = "CONTROLVARTYPE";
  if (PyDict_Contains(dict, asPyScalar(paramname))) {
    paramvalue = asString(PyDict_GetItemString(dict, paramname.c_str()));
    paramvalue = trim(paramvalue);
    std::transform(paramvalue.begin(), paramvalue.end(), paramvalue.begin(), ::toupper);
    if (paramvalue == "ANTITHETIC")
      mcparams.controlVarType = qf::McParams::ControlVarType::ANTITHETIC;
    else if (paramvalue == "NONE" || paramvalue.empty())
      mcparams.controlVarType = qf::McParams::ControlVarType::NONE; // do nothing
    else
      QF_ASSERT(0, "asMcParams: unknown McParam " + paramname + "!");
  }
  else {  // list does not contain paramname
    mcparams.controlVarType = qf::McParams::ControlVarType::NONE; // do nothing, default
  }

  return mcparams;
}

/** Converts a Python dictionary with name-value pairs to an PdeParams structure.
*/
static qf::PdeParams asPdeParams(PyObject* dict)
{
  QF_ASSERT(PyDict_Check(dict) == 1, "asPdeParams: input param must be a dictionary");

  qf::PdeParams pdeparams;
  std::string paramvalue;

  std::string paramname = "NTIMESTEPS";
  QF_ASSERT(PyDict_Contains(dict, asPyScalar(paramname)) == 1,
    "asPdeParams: input dictionary does not contain key NTIMESTEPS");
  pdeparams.nTimeSteps = (size_t) asInt(PyDict_GetItemString(dict, paramname.c_str()));

  paramname = "NSPOTNODES";
  QF_ASSERT(PyDict_Contains(dict, asPyScalar(paramname)) == 1,
    "asPdeParams: input dictionary does not contain key NSPOTNODES");
  pdeparams.nSpotNodes[0] = (size_t) asInt(PyDict_GetItemString(dict, paramname.c_str()));

  paramname = "NSTDDEVS";
  QF_ASSERT(PyDict_Contains(dict, asPyScalar(paramname)) == 1,
    "asPdeParams: input dictionary does not contain key NSTDDEVS");
  pdeparams.nStdDevs[0] = asDouble(PyDict_GetItemString(dict, paramname.c_str()));

  paramname = "THETA";
  QF_ASSERT(PyDict_Contains(dict, asPyScalar(paramname)) == 1,
    "asPdeParams: input dictionary does not contain key THETA");
  pdeparams.theta = asDouble(PyDict_GetItemString(dict, paramname.c_str()));

  return pdeparams;
}

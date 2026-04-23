/**
@file   choldcmp.cpp
@brief  Implementation of the Cholesky decomposition
*/

#include <qflib/math/linalg/linalg.hpp>
#include <qflib/exception.hpp>

BEGIN_NAMESPACE(qf)

/** Cholesky decomposition of a positive semi-definite matrix inMat.
  The returned matrix is lower triangular, such that 
  outMat * outMat^T = inMat
*/
void choldcmp(Matrix const& inMat, Matrix& outMat)
{
  QF_ASSERT(inMat.is_square(), "choldcmp: input matrix must be square!");
  QF_ASSERT(arma::approx_equal(inMat, inMat.t(), "absdiff", 1.0e-16), "choldcmp: input matrix must be symmetric!");
  bool  ok = arma::chol(outMat, inMat, "lower");
  QF_ASSERT(ok, "choldcmp: input matrix not positive definite!");
  return;
}

END_NAMESPACE(qf)

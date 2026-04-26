/**
@file   eigensym.cpp
@brief  The eigenvalues and eigenvectors of a real symmetric matrix
*/

#include <qflib/math/linalg/linalg.hpp>
#include <qflib/exception.hpp>

BEGIN_NAMESPACE(qf)

void eigensym(Matrix const& inMat, Vector& eigenValues, Matrix& eigenVectors)
{
  QF_ASSERT(inMat.is_square(), "eigensym: input matrix must be square!");
  arma::eig_sym(eigenValues, eigenVectors, inMat);
  return;
}

END_NAMESPACE(qf)

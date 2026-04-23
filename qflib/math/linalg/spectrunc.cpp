/**
@file   spectrunc.cpp
@brief  Spectral truncation of the input symmetric matrix, to make it positive semi-definite
*/

#include <qflib/math/linalg/linalg.hpp>
#include <qflib/exception.hpp>
#include <algorithm>

BEGIN_NAMESPACE(qf)

/** Spectral truncation of the input symmetric matrix.
    The input matrix must be symmetric with ones along the diagonal
*/
void spectrunc(Matrix& corrmat, double tolerance)
{

  size_t matsize = corrmat.n_rows;
  // assert that the input matrix is a symmetric with 1.0 in the diagonal.
  QF_ASSERT(corrmat.is_square(),
    "spectrunc: input correlation matrix is not square!");
  for (size_t i = 0; i < matsize; ++i) {
    QF_ASSERT(corrmat(i, i) == 1.0,
      "spectrunc: input correlation matrix does not have all ones in the diagonal!");
  }

  Vector  myEigenvalues;
  Matrix myEigenvectors;
  try {
    arma::eig_sym(myEigenvalues, myEigenvectors, corrmat);
  }
  catch (...) {
    QF_ASSERT(0, "spectrunc: failed to diagonalize the correlation matrix!");
  }

  const double tol = tolerance;
  if (std::all_of(myEigenvalues.begin(), myEigenvalues.end(), [=](double x) {return x > tol; }))
    return;

  //////////////////////////////////////////////////////////////////////////
  // Correct the matrix
  // Eliminate negative eigenvalues
  //////////////////////////////////////////////////////////////////////////

  Vector coeffcorrection(matsize, arma::fill::zeros);
  for (size_t j = 0; j < matsize; ++j) {
    double tmp = myEigenvalues[j] = sqrt(std::max(myEigenvalues[j], 0.0));
    tmp = std::max(tmp, sqrt(tol));
    for (size_t i = 0; i < matsize; ++i) {
      double tmp2 = (myEigenvectors(i, j) *= tmp);
      coeffcorrection[i] += tmp2 * tmp2;
    }
  }

  for (size_t i = 0; i < matsize; ++i) {
    coeffcorrection[i] = sqrt(coeffcorrection[i]);
    QF_ASSERT(coeffcorrection[i] != 0.0,
      "spectrunc: zero eigenvector in correlation matrix!");
    for (size_t j = 0; j < matsize; ++j) {
      myEigenvectors(i, j) /= coeffcorrection[i];
    }
  }

  double tolcorrection = 0.0;
  for (size_t i = 0; i < matsize; ++i) {
    double tmp = 0.0;
    for (size_t j = 0; j < matsize; ++j) {
      tmp += myEigenvectors(i, j) * myEigenvectors(i, j);
    }
    tolcorrection = std::max(tolcorrection, tmp);
  }

  for (size_t i = 0; i < matsize; ++i) {
    corrmat(i, i) = 1.0;
    for (size_t j = 0; j < i; ++j) {
      double tmp = 0.0;
      for (size_t k = 0; k < matsize; ++k) {
        tmp += myEigenvectors(i, k) * myEigenvectors(j, k);
      }
      corrmat(i, j) = corrmat(j, i) = tmp / tolcorrection;
    }
  }
  return;
}

END_NAMESPACE(qf)

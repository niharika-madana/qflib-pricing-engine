<<<<<<< HEAD
<<<<<<< HEAD
/**
@file   linalg.hpp
@brief  Definition of linear algebra routines
*/

#pragma once

#include <qflib/math/matrix.hpp>

BEGIN_NAMESPACE(qf)

/** 
* Cholesky decomposition of a positive semi-definite matrix inMat.
* It computes the lower triangular part of outMat such that outMat * trans(outMat) = inMat.
*/
void choldcmp(Matrix const& inMat, Matrix& outMat);

/** 
* Eigenvalues and eigenvectors of a real symmetric matrix
*/
void eigensym(Matrix const& inputMatrix, Vector& eigenValues, Matrix& eigenVectors);

/** 
* Spectral truncation of the input correlation matrix.
* The input matrix must be symmetric with ones along the diagonal.
* Spectral truncation happens in place and the returned matrix is symmetric, 
* positive semi-definite and with ones along the diagonal.
*/
void spectrunc(Matrix& corrmat, double tolerance = 1e-8);

END_NAMESPACE(qf)
=======
/**
@file   linalg.hpp
@brief  Definition of linear algebra routines
*/

#pragma once

#include <qflib/math/matrix.hpp>

BEGIN_NAMESPACE(qf)

/** 
* Cholesky decomposition of a positive semi-definite matrix inMat.
* It computes the lower triangular part of outMat such that outMat * trans(outMat) = inMat.
*/
void choldcmp(Matrix const& inMat, Matrix& outMat);

/** 
* Eigenvalues and eigenvectors of a real symmetric matrix
*/
void eigensym(Matrix const& inputMatrix, Vector& eigenValues, Matrix& eigenVectors);

/** 
* Spectral truncation of the input correlation matrix.
* The input matrix must be symmetric with ones along the diagonal.
* Spectral truncation happens in place and the returned matrix is symmetric, 
* positive semi-definite and with ones along the diagonal.
*/
void spectrunc(Matrix& corrmat, double tolerance = 1e-8);

END_NAMESPACE(qf)
>>>>>>> origin/yuyang-branch
=======
/**
@file   linalg.hpp
@brief  Definition of linear algebra routines
*/

#pragma once

#include <qflib/math/matrix.hpp>

BEGIN_NAMESPACE(qf)

/** 
* Cholesky decomposition of a positive semi-definite matrix inMat.
* It computes the lower triangular part of outMat such that outMat * trans(outMat) = inMat.
*/
void choldcmp(Matrix const& inMat, Matrix& outMat);

/** 
* Eigenvalues and eigenvectors of a real symmetric matrix
*/
void eigensym(Matrix const& inputMatrix, Vector& eigenValues, Matrix& eigenVectors);

/** 
* Spectral truncation of the input correlation matrix.
* The input matrix must be symmetric with ones along the diagonal.
* Spectral truncation happens in place and the returned matrix is symmetric, 
* positive semi-definite and with ones along the diagonal.
*/
void spectrunc(Matrix& corrmat, double tolerance = 1e-8);

END_NAMESPACE(qf)
>>>>>>> origin/fangyi-branch

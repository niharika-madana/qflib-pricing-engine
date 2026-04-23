<<<<<<< HEAD
<<<<<<< HEAD
/**
@file   matrix.hpp
@brief  Definition of an mxn dense matrix of double values; wrapper around armadillo matrix
*/

#pragma once

#include <armadillo>
#include <qflib/defines.hpp>

BEGIN_NAMESPACE(qf)

/** The qf::Vector class is an alias for the armadillo column vector, a sequence of doubles */
using Vector = arma::vec;

/** The qf::RowVector class is an alias for the armadillo row vector, a sequence of doubles */
using RowVector = arma::rowvec;

/** The qf::Matrix class is an alias for the armadillo matrix, a dense matrix of doubles.
    The storage is column-wise. Access to the underlying data can be gained via the .memptr() method.
*/
using Matrix = arma::mat;

END_NAMESPACE(qf)
=======
/**
@file   matrix.hpp
@brief  Definition of an mxn dense matrix of double values; wrapper around armadillo matrix
*/

#pragma once

#include <armadillo>
#include <qflib/defines.hpp>

BEGIN_NAMESPACE(qf)

/** The qf::Vector class is an alias for the armadillo column vector, a sequence of doubles */
using Vector = arma::vec;

/** The qf::RowVector class is an alias for the armadillo row vector, a sequence of doubles */
using RowVector = arma::rowvec;

/** The qf::Matrix class is an alias for the armadillo matrix, a dense matrix of doubles.
    The storage is column-wise. Access to the underlying data can be gained via the .memptr() method.
*/
using Matrix = arma::mat;

END_NAMESPACE(qf)
>>>>>>> origin/yuyang-branch
=======
/**
@file   matrix.hpp
@brief  Definition of an mxn dense matrix of double values; wrapper around armadillo matrix
*/

#pragma once

#include <armadillo>
#include <qflib/defines.hpp>

BEGIN_NAMESPACE(qf)

/** The qf::Vector class is an alias for the armadillo column vector, a sequence of doubles */
using Vector = arma::vec;

/** The qf::RowVector class is an alias for the armadillo row vector, a sequence of doubles */
using RowVector = arma::rowvec;

/** The qf::Matrix class is an alias for the armadillo matrix, a dense matrix of doubles.
    The storage is column-wise. Access to the underlying data can be gained via the .memptr() method.
*/
using Matrix = arma::mat;

END_NAMESPACE(qf)
>>>>>>> origin/fangyi-branch

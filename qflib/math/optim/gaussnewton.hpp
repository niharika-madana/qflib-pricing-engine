/**
@file  gaussnewton.hpp
@brief Bounded Gauss-Newton solver with LM damping for nonlinear least squares
*/
#pragma once
#include <qflib/defines.hpp>
#include <qflib/exception.hpp>
#include <qflib/math/matrix.hpp>
#include <cmath>
#include <algorithm>

BEGIN_NAMESPACE(qf)

/**
  Minimizes 0.5*||f(x)||^2 subject to lo[i] <= x[i] <= hi[i].
  FUNC must implement: qf::Vector operator()(qf::Vector const& x)
  returning the residuals vector.
  x holds the initial guess on entry and the solution on exit.
*/
template <typename FUNC>
void gaussNewton(Vector& x, Vector const& lo, Vector const& hi,
                 FUNC& func, double tol = 1.0e-8, int maxIter = 200)
{
  const double EPS_JAC = 1.0e-6;
  int n = static_cast<int>(x.n_elem);

  for (int iter = 0; iter < maxIter; ++iter) {
    Vector r = func(x);
    if (arma::norm(r, 2) < tol) return;

    int m = static_cast<int>(r.n_elem);
    Matrix J(m, n);

    // forward finite-difference Jacobian
    for (int j = 0; j < n; ++j) {
      Vector xp = x;
      double h = EPS_JAC * std::max(1.0, std::abs(x[j]));
      xp[j] = std::min(x[j] + h, hi[j]);
      J.col(j) = (func(xp) - r) / h;
    }

    // normal equations with LM damping: (J'J + λI)δ = -J'r
    Matrix JtJ = J.t() * J;
    JtJ.diag() += 1.0e-4 * arma::trace(JtJ) / n;

    Vector delta;
    bool ok = arma::solve(delta, JtJ, -(J.t() * r));
    QF_ASSERT(ok, "gaussNewton: linear solve failed");

    // backtracking line search with bound projection
    double step  = 1.0;
    double norm0 = arma::norm(r, 2);
    for (int ls = 0; ls < 20; ++ls) {
      Vector xn = x + step * delta;
      for (int j = 0; j < n; ++j)
        xn[j] = std::min(std::max(xn[j], lo[j]), hi[j]);
      if (arma::norm(func(xn), 2) < norm0) { x = xn; break; }
      step *= 0.5;
    }
  }
}

END_NAMESPACE(qf)

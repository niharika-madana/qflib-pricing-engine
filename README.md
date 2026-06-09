# qflib

A C++20 quantitative finance library with Python bindings for pricing derivatives. Supports European, digital, American, Asian basket, and quanto options, using analytical Black-Scholes formulas, Monte Carlo simulation, finite difference PDE methods, and the Heston stochastic volatility model.

**Version:** 1.2.0 | **C++ Standard:** C++20 | **Matrix Library:** Armadillo 15.2.3

---

## Table of Contents

- [Features](#features)
- [Directory Structure](#directory-structure)
- [Dependencies](#dependencies)
- [Building](#building)
- [Python API Reference](#python-api-reference)
  - [Utilities](#utilities)
  - [Analytical Pricing](#analytical-pricing)
  - [Market Objects](#market-objects)
  - [Monte Carlo Pricing](#monte-carlo-pricing)
  - [PDE Pricing](#pde-pricing)
  - [Implied Volatility and Heston Model](#implied-volatility-and-heston-model)
- [Usage Examples](#usage-examples)
- [C++ API Overview](#c-api-overview)

---

## Features

- **Analytical pricing** — Black-Scholes closed-form for European and digital options; forward price
- **Monte Carlo simulation** — Single-asset and multi-asset correlated path generation with Euler discretization, antithetic variance reduction, and choice of RNG (Mersenne Twister, RANLUX)
- **PDE solver** — Backwards-induction finite difference solver with Crank-Nicolson, explicit, and implicit schemes; supports European and American exercise
- **Market data** — Yield curve construction from spot rates, forward rates, or zero bond prices; volatility term structure; 2D implied volatility surface
- **Heston model** — Characteristic-function pricing via Gil-Pelaez inversion; implied vol extraction; joint multi-maturity calibration via Gauss-Newton with Levenberg-Marquardt damping
- **Implied volatility** — Newton-Raphson solver inverting Black-Scholes to machine precision
- **Option types** — European call/put, digital call/put, American call/put, Asian basket call/put, worst-of digital, quanto
- **Math utilities** — Normal distribution (CDF, PDF, inverse CDF), piecewise polynomial interpolation/integration, Cholesky decomposition, spectral truncation of correlation matrices, root finding

---

## Directory Structure

```
qflib-1.2.0/
├── qflib/                    # Core C++ library (compiled to static library)
│   ├── market/               # YieldCurve, VolatilityTermStructure, VolatilitySurface, Market singleton
│   ├── math/
│   │   ├── interpol/         # PiecewisePolynomial
│   │   ├── linalg/           # Cholesky, eigenvalues, spectral truncation
│   │   ├── optim/            # Root finding (zbrak, rtsec), PolyFunc, Gauss-Newton
│   │   ├── random/           # NormalRng template, RNG type aliases
│   │   └── stats/            # NormalDistribution, ErrorFunction, MeanVarCalculator
│   ├── methods/
│   │   ├── montecarlo/       # PathGenerator, EulerPathGenerator, AntitheticPathGenerator
│   │   └── pde/              # Pde1DSolver, TridiagonalOp1D, PdeGrid
│   ├── pricers/              # BsMcPricer, MultiAssetBsMcPricer, BsMcQuantoPricer, simplepricers,
│   │                         # impliedvol, heston
│   └── products/             # EuropeanCallPut, DigitalCallPut, AmericanCallPut, AsianBasketCallPut, ...
├── pyqflib/                  # Python bindings (compiled to .pyd / .so)
│   ├── qflib/                # Python package (importable as `import qflib as qf`)
│   └── pyfunctions*.hpp      # C++-side Python callable implementations
├── examples/
│   └── Python/
│       ├── 01_quantooption_pricing.ipynb
│       └── 03_volsurface_heston.ipynb
├── lib/                      # Compiled output
└── CMakeLists.txt
```

---

## Dependencies

| Dependency | Version | Purpose |
|---|---|---|
| C++ compiler (MSVC or GCC) | C++20 | Core library |
| CMake | ≥ 3.25 | Build system |
| Armadillo | 15.2.3 | Vectors, matrices, linear algebra |
| BLAS / LAPACK / f2c | — | Numerical routines (linked by pyqflib) |
| Python | 3.12 | Python bindings |
| NumPy | — | Array interop in Python bindings |

---

## Building

The project uses CMake. Both the static C++ library and the Python extension module are built together.

```bash
# From the project root
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

Output artifacts:
- `lib/qflib.lib` — static C++ library
- `lib/pyqflib.pyd` (Windows) or `lib/pyqflib.so` (Linux) — Python extension

The `pyqflib/CMakeLists.txt` expects a Miniconda environment named `qfgb` at `$USERPROFILE/miniconda3/envs/qfgb`. Adjust paths if your Python installation differs.

---

## Python API Reference

Import the module:

```python
import qflib as qf
```

### Utilities

| Function | Description |
|---|---|
| `qf.version()` | Returns the library version string |
| `qf.sayHello(name)` | Echo greeting (sanity check) |
| `qf.outerProd(x, y)` | Outer product of two vectors |
| `qf.echoMatrix(m)` | Round-trip a NumPy matrix through C++ |
| `qf.toContCmpd(rate, freq)` | Convert rate to continuously compounded |
| `qf.fromContCmpd(rate, freq)` | Convert continuously compounded rate back |
| `qf.erf(x)` / `qf.invErf(x)` | Error function and its inverse |
| `qf.normalCdf(x)` / `qf.normalInvCdf(p)` | Normal CDF and inverse CDF |
| `qf.ppolyEval(xbkpts, yvals, order, xval, deriv)` | Evaluate piecewise polynomial (or its derivative) |
| `qf.ppolyIntegral(xbkpts, yvals, order, x0, xval)` | Definite integral of piecewise polynomial |
| `qf.polyBracket(coeffs, lo, hi, nsubs)` | Bracket roots of a polynomial |
| `qf.polySecant(coeffs, x0, x1, tol)` | Find root of a polynomial via secant method |
| `qf.eigenSym(m)` | Eigenvalues/vectors of a real symmetric matrix |
| `qf.specTrunc(corr)` | Spectral truncation of a non-PSD correlation matrix |

### Analytical Pricing

| Function | Description |
|---|---|
| `qf.fwdPrice(spot, timetoexp, intrate, divyield)` | Forward price |
| `qf.digiBS(payofftype, spot, timetoexp, strike, intrate, divyield, volatility)` | Digital option via Black-Scholes |
| `qf.euroBS(payofftype, spot, timetoexp, strike, intrate, divyield, volatility)` | European option via Black-Scholes |

`payofftype`: `1` = call, `-1` = put. Returns `[price, delta, gamma, vega, theta, rho]`.

### Market Objects

```python
# Create a yield curve from spot rates (valtype=0), forward rates (valtype=1), or zero bonds (valtype=2)
yc = qf.ycCreate(ycname, tmats, vals, valtype)

# Query the yield curve
qf.discount(ycname, tmat)          # Discount factor
qf.spotRate(ycname, tmat)          # Spot (zero) rate
qf.fwdRate(ycname, tmat1, tmat2)   # Forward rate between two maturities

# Manage market state
qf.mktList()    # List all stored market objects
qf.mktClear()   # Remove all market objects
```

### Monte Carlo Pricing

MC parameters are passed as a dict:

```python
mcparams = {
    'URNGTYPE':    'MT19937',   # or 'RANLUX3', 'RANLUX4'
    'PATHGENTYPE': 'EULER',     # or 'ANTITHETIC'
}
```

| Function | Description |
|---|---|
| `qf.euroBSMC(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, mcparams, npaths)` | European option via BS Monte Carlo |
| `qf.digiBSMC(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, mcparams, npaths)` | Digital option via BS Monte Carlo |
| `qf.asianBasketBSMC(payofftype, strike, fixtimes, assetquantities, spots, discountcrv, divyields, volatilities, correlmat, mcparams, npaths)` | Asian basket option via multi-asset BS Monte Carlo |
| `qf.quantoBSMC(...)` | Quanto option via BS Monte Carlo |

Returns a dict with keys `Mean`, `StdErr`, and optionally `StdDev`.

### PDE Pricing

PDE parameters are passed as a dict:

```python
pdeparams = {
    'NTIMESTEPS': 100,  # number of time steps
    'NSPOTNODES': 100,  # number of spot grid nodes
    'NSTDDEVS':   4,    # grid width in standard deviations
    'THETA':      0.5,  # 0=explicit, 1=implicit, 0.5=Crank-Nicolson
}
```

| Function | Description |
|---|---|
| `qf.euroBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams)` | European option via finite difference PDE |
| `qf.amerBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams)` | American option via finite difference PDE |

Returns a dict with key `Price`.

### Implied Volatility and Heston Model

#### Implied volatility

| Function | Description |
|---|---|
| `qf.impliedVol(payofftype, spot, strike, timetoexp, intrate, divyield, marketprice)` | Newton-Raphson implied BS vol from a market price |

#### Heston model

| Function | Description |
|---|---|
| `qf.hestonCall(spot, strike, timetoexp, intrate, divyield, v0, kappa, theta, xi, rho)` | European call price via Gil-Pelaez inversion |
| `qf.hestonVol(payofftype, spot, strike, timetoexp, intrate, divyield, v0, kappa, theta, xi, rho)` | BS implied vol from a Heston price |
| `qf.hestonCalibrate(mktVols, strikes, mats, spot, intrate, divyield, v0, kappa, theta, xi, rho)` | Calibrate all five Heston params to a market vol surface |

`hestonCalibrate` returns a dict with keys `V0`, `Kappa`, `Theta`, `Xi`, `Rho`.

Heston parameters: `v0` initial variance, `kappa` mean-reversion speed, `theta` long-run variance, `xi` vol-of-vol, `rho` asset-variance correlation.

#### Volatility surface

| Function | Description |
|---|---|
| `qf.vsCreate(name, strikes, mats, vols)` | Create a 2D implied vol surface (bilinear interpolation) |
| `qf.vsImpliedVol(name, strike, mat)` | Interpolated implied vol at (strike, maturity) |
| `qf.vsTotalVar(name, strike, mat)` | Total variance σ²·T at (strike, maturity) |
| `qf.vsAtmVol(name, mat, fwd)` | ATM implied vol at maturity using forward as ATM strike |

`vols` is a 2D array of shape `(len(strikes), len(mats))`. Vol surfaces are stored in the market singleton alongside yield curves.

---

## Usage Examples

### Analytical option pricing

```python
import qflib as qf

# Forward price
fwd = qf.fwdPrice(spot=100, timetoexp=1.0, intrate=0.04, divyield=0.02)

# European call via Black-Scholes (returns [price, delta, gamma, vega, theta, rho])
price, *greeks = qf.euroBS(payofftype=1, spot=100, timetoexp=1.0, strike=100,
                            intrate=0.04, divyield=0.02, volatility=0.4)
```

### Yield curve and market data

```python
yc = qf.ycCreate(
    ycname='USD',
    tmats =[1/12, 1/4,  1/2,  1,    2,    5,    10  ],
    vals  =[0.01, 0.02, 0.03, 0.04, 0.045, 0.05, 0.065],
    valtype=0   # 0=spot rates
)

df     = qf.discount(yc, 2.0)     # discount factor at 2Y
sr     = qf.spotRate(yc, 2.0)     # spot rate at 2Y
fr     = qf.fwdRate(yc, 1.0, 2.0) # 1Y×1Y forward rate
```

### Monte Carlo pricing

```python
mcparams = {'URNGTYPE': 'MT19937', 'PATHGENTYPE': 'EULER'}

result = qf.euroBSMC(payofftype=1, strike=100, timetoexp=1.0, spot=100,
                     discountcrv=yc, divyield=0.02, volatility=0.4,
                     mcparams=mcparams, npaths=200_000)
print(f"Price={result['Mean']:.4f}  StdErr={result['StdErr']:.4f}")
```

### Asian basket option (multi-asset MC)

```python
import numpy as np

correls = np.array([
    [1.0, 0.5, 0.7],
    [0.5, 1.0, 0.8],
    [0.7, 0.8, 1.0],
])

result = qf.asianBasketBSMC(
    payofftype=1, strike=100,
    fixtimes=[0.5, 1.0, 1.5, 2.0],
    assetquantities=[1/3, 1/3, 1/3],
    spots=[100, 100, 100],
    discountcrv=yc,
    divyields=[0.02, 0.02, 0.02],
    volatilities=[0.30, 0.30, 0.30],
    correlmat=correls,
    mcparams={'URNGTYPE': 'MT19937', 'PATHGENTYPE': 'EULER'},
    npaths=200_000,
)
print(f"Price={result['Mean']:.4f}  StdErr={result['StdErr']:.4f}")
```

### Implied vol and Heston calibration

```python
# Implied vol from a known market price
price = qf.euroBS(1, 100, 100, 1.0, 0.05, 0.02, 0.25)[0]
ivol  = qf.impliedVol(1, 100, 100, 1.0, 0.05, 0.02, price)  # recovers 0.25

# Build a market vol surface from Heston-generated quotes
strikes = [80, 90, 95, 100, 105, 110, 120]
mats    = [0.25, 0.5, 1.0, 2.0]
vols    = [[qf.hestonVol(1, 100, K, T, 0.05, 0.02,
                         0.04, 2.0, 0.04, 0.5, -0.7)
            for T in mats] for K in strikes]

qf.vsCreate('SURF', strikes, mats, vols)
print(qf.vsImpliedVol('SURF', 100, 1.0))   # ATM 1Y vol

# Calibrate Heston to the surface
fit = qf.hestonCalibrate(vols, strikes, mats, 100, 0.05, 0.02,
                          0.06, 1.0, 0.06, 0.3, -0.5)
print(fit)  # {'V0': ..., 'Kappa': ..., 'Theta': ..., 'Xi': ..., 'Rho': ...}
```

### PDE pricing — European and American

```python
pdeparams = {'NTIMESTEPS': 100, 'NSPOTNODES': 100, 'NSTDDEVS': 4, 'THETA': 0.5}

euro = qf.euroBSPDE(payofftype=1, strike=100, timetoexp=1.0, spot=100,
                    discountcrv=yc, divyield=0.02, volatility=0.4,
                    pdeparams=pdeparams)

amer = qf.amerBSPDE(payofftype=1, strike=100, timetoexp=1.0, spot=100,
                    discountcrv=yc, divyield=0.02, volatility=0.4,
                    pdeparams={'NTIMESTEPS': 800, 'NSPOTNODES': 800, 'NSTDDEVS': 4, 'THETA': 0.5})

print(f"European PDE: {euro['Price']:.4f}")
print(f"American PDE: {amer['Price']:.4f}")
```

---

## C++ API Overview

### Key classes

| Class | Header | Purpose |
|---|---|---|
| `YieldCurve` | `qflib/market/yieldcurve.hpp` | Discount factors and rates from bootstrapped curve |
| `VolatilityTermStructure` | `qflib/market/volatilitytermstructure.hpp` | Spot/forward volatility queries |
| `VolatilitySurface` | `qflib/market/volsurface.hpp` | 2D implied vol surface with bilinear interpolation |
| `Market` | `qflib/market/market.hpp` | Singleton registry for market objects |
| `EuropeanCallPut` | `qflib/products/europeancallput.hpp` | European payoff |
| `AmericanCallPut` | `qflib/products/americancallput.hpp` | American payoff with daily fixings |
| `DigitalCallPut` | `qflib/products/digitalcallput.hpp` | Binary payoff |
| `AsianBasketCallPut` | `qflib/products/asianbasketcallput.hpp` | Average-price basket payoff |
| `BsMcPricer` | `qflib/pricers/bsmcpricer.hpp` | Single-asset Black-Scholes MC pricer |
| `MultiAssetBsMcPricer` | `qflib/pricers/multiassetbsmcpricer.hpp` | Multi-asset correlated MC pricer |
| `BsMcQuantoPricer` | `qflib/pricers/bsmcquantopricer.hpp` | Quanto option MC pricer |
| `HestonParams` / `hestonCall` | `qflib/pricers/heston.hpp` | Heston pricing and calibration |
| `impliedVol` | `qflib/pricers/impliedvol.hpp` | Newton-Raphson BS implied vol solver |
| `EulerPathGenerator` | `qflib/methods/montecarlo/eulerpathgenerator.hpp` | Euler-scheme path generator template |
| `AntitheticPathGenerator` | `qflib/methods/montecarlo/antitheticpathgenerator.hpp` | Antithetic variance reduction |
| `Pde1DSolver` | `qflib/methods/pde/pde1dsolver.hpp` | 1D finite difference backwards induction solver |
| `PiecewisePolynomial` | `qflib/math/interpol/piecewisepolynomial.hpp` | Right-continuous piecewise polynomial |
| `NormalDistribution` | `qflib/math/stats/normaldistribution.hpp` | Normal PDF, CDF, inverse CDF |
| `NormalRng<Gen>` | `qflib/math/random/normalrng.hpp` | Box-Muller normal deviate generator |

### Vector and Matrix types

```cpp
#include "qflib/math/matrix.hpp"
// qf::Vector  — alias for arma::Col<double>
// qf::Matrix  — alias for arma::Mat<double>
```

### Error handling

```cpp
#include "qflib/exception.hpp"
QF_ASSERT(condition, "message");  // throws qf::Exception on failure
```

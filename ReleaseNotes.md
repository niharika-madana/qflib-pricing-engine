QFLIB Release Notes
====================

VERSION 1.1.0
--------------

### Additions

1. New files `qflib/pricers/bsmcquantopricer.hpp` and `bsmcquantopricer.cpp`.  
   Definition of the class `BsMcQuantoPricer`.  
   Prices a quanto option via Black-Scholes Monte Carlo, accounting for FX volatility and asset–FX correlation in the drift adjustment.

2. In files `qflib/pricers/simplepricers.hpp` and `simplepricers.cpp`.  
   Added the following analytical pricing functions:  
   - `quantoEuropeanOptionBS` — Black-Scholes price of a quanto European option.

3. In files `qflib/methods/pde/pdebase.hpp`, `pdebase.cpp`, and `pde1dsolver.hpp`.  
   Extended the PDE infrastructure to support a quanto drift adjustment in the 1D solver.

4. In file `pyqflib/pyfunctions1.hpp`.  
   Added definition of function `pyQfQEuroBS`.  
   Implements analytical Black-Scholes pricing for quanto European options.

5. In file `pyqflib/pyfunctions3.hpp`.  
   Added definitions of functions `pyQfQEuroBSMC`.  
   Implement MC pricing for quanto European options.

6. In file `pyqflib/pyfunctions4.hpp`.  
   Added definition of function `pyQfQuantoEuroBSPDE`.  
   Implements PDE pricing for quanto European options.

7. In files `pyqflib/pymodule.cpp` and `pyqflib/qflib/__init__.py`.  
   Registered the following new Python callable functions:  
   - `qf.qEuroBS` — analytical Black-Scholes price of a quanto European option  
   - `qf.qEuroBSMC` — MC price of a quanto European option  
   - `qf.qEuroBSPDE` — PDE price of a quanto European option  


VERSION 1.0.0
--------------

### Additions

1. Added solutions to homeworks 8-10


VERSION 0.11.0
--------------

### Additions

1. New file `qflib/products/americancallput.hpp`.  
	Definition of the class AmericanCallPut.

### Modifications

1. In files `pyqflib/pyfunctions4.hpp` and `pyqflib/qflib/__init__.py`.  
	Definition and registration of the Python function qf.amerBSPDE.


VERSION 0.10.0
-------------

### Additions

1. New folder `qflib/methods/pde`. It contains PDE related files.

2. New file `qflib/methods/pde/tridiagonalops1d.hpp`.  
	Definition of the class TridiagonalOperator and derived classes.

3. New file `qflib/methods/pde/pdegrid.hpp`.  
	Definition of the classes CoordinateChange and GridAxis.
	
4. New file `qflib/methods/pde/pdeparams.hpp`.  
	Definition of the class PdeParams.

5. New file `qflib/methods/pde/pderesults.hpp`.  
	Definition of the class PdeResults.

6. New file `qflib/math/interpol/interpolation1d.hpp`.  
	Definition of the class LinearInterpolation1D.

7. New files `qflib/methods/pde/pdebase.hpp` and `pdebase.cpp`.  
	Definition of the abstract base class PdeBase.
	
8. New files `qflib/methods/pde/pde1dsolver.hpp` and `pde1dsolver.cpp`.  
	Definition of the one spot dimension PDE solver.
	
9. New files `pyqflib/pyfunctions4.hpp` and `pyqflib/qflib/__init__.py`.  
	Definition and registration of the Python function qf.euroBSPDE.

10. In file `pyqflib/pyutils.hpp`, added utility function asPdeParams.

### Modifications

1. In file `qflib/products/product.hpp`.  
   Added method Product::timeSteps. It sets up the time steps to be used in the PDE solver.  

2. In file `qflib/products/product.hpp`.  
   Added method overload Product::eval. It evaluates the product at a specific point in time.  


VERSION 0.9.0
-------------

### Additions

1. New folder `qflib/math/linalg`  
	It will contain linear algebra related routines.

2. New files `choldcmp.cpp`, `eigensym.cpp`, `spectrunc.cpp` in folder `qrflib/math/linalg`  
	They contain implementations for Cholesky decomposition, eigenvalues/eigenvectors of 
	a real symmetric matrix and spectral truncation of a non-positive definite correlation matrix.

3. Added function declarations for above algorithms in new file `qflib/math/linalg/linalg.hpp`

4. New Python functions qf.eigenSym() and qf.specTrunc() in `pyqflib/pyfunctions0.hpp`  
	They allow testing of the diagonalization and spectral truncation of a correlation matrix.

5. New file `qflib/products/asianbasketcallput.hpp`  
	It defines the payoff of an Asian call or put option on a basket of assets.
  
6. New files `qflib/pricers/multiassetbsmcpricer.hpp` and `.cpp`  
	They define the multi-asset Black-Scholes Monte Carlo pricer class.
  
7. New Python function qf.asianBasketBSMC() implemented in the file `pyqflib/pyfunctions3.hpp`	
	Provides the Excel interface to pricing Asian baskets in Black-Scholes MC.

### Modifications

1. Added Cholesky decomposition and correlation spectral truncation to class PathGenerator

2. Widened the ctor of EulerPathGenerator to accept an optional correlation matrix

3. Added method nAssets() to class Product in file `qflib/products/product.hpp` and to class EuropeanCallPut

4. Added linking to f2c.lib, blas.lib and lapack.lib third party libraries in the `armadillo-14.2.2/lib` folder.  
   This is done in the `pyqflib/CMakelists.txt` file.


VERSION 0.8.0
-------------

### Additions

1. New folder `qflib/math/random`  
	It will contain files for random number generation.
  
2. New file `qflib/math/random/normalrng.hpp`  
	It defines the NormalRng class template that generates random normal deviates.
  
3. New file `qflib/math/random/rng.hpp`  
	It contains typedefs for common combinations of distributions and underlying generators.  
	This file is to be included by any other file that requires random samples.
  
4. New folder `qflib/methods/montecarlo`  
	It will contain files specific to MC path generation.
  
5. New files `qflib/methods/montecarlo/pathgenerator.hpp` and `eulerpathgenerator.hpp`  
	The first file defines the abstract base PathGenerator and the second file defines a class template 
	that generates paths using the Euler method.
  
6. New file `qflib/methods/montecarlo/mcparams.hpp`  
	It defines a struct to be used for collecting MC parameters.

7. New folder `qflib/products`  
	It will contain files specific to product payoffs.

8. New files `qflib/products/product.hpp` and `qflib/products/europeancallput.hpp`  
	The abstact product base class and the European option product class.

9. New file `qflib/math/stats/statisticscalculator.hpp`  
	It defines the base class template for classes that compute statistics of samples.
  
10. New file `qflib/math/stats/meanvarcalculator.hpp`  
	It defines the mean-variance calculator.

11. New files  `qflib/pricers/bsmcpricer.hpp` and `bsmcpricer.cpp`  
	They define the Black-Scholes Monte Carlo pricer class.
    
12. New Python file `pyqflib/pyfunctions3.cpp`  
	It implements the Python callable C++ function pyQfEuroBSMC.

13. New Python callable function qf.euroBSMC.

14. Added solutions to homeworks 1-7


VERSION 0.7.0
-------------

### Additions

1. New utility functions toContCmpd and fromContCpd in file `qflib/utils.hpp`  
   They convert an interest rate to/from  continuous compounding from/to compounding with a given annual frequency.

2. New folder `qflib/math/optim`  
  It contains root finding and optimization routines.
	
3. New file `qflib/math/optim/roots.hpp`  
  It contains the root finding routines zbrak and rtsec from NR C++ 3ed.

4. New file `qflib/math/optim/polyfunc.hpp`  
  It defines a class that models a polynomial.

5. New Python callable functions qf.polyBracket, qf.polySecant, qf.toContCmpd, qf.fromContCmpd


VERSION 0.6.0
-------------

### Additions

1. New folder `qflib/market` with two new files `yieldcurve.hpp` and `yieldcurve.cpp`.  
	They define and implement the YieldCurve class.

2. Two new files `qflib/market/market.hpp` and `market.cpp`.  
	They define and implement the Market singleton class.

3. New file `pyqflib/pyfunctions2.cpp` and additions to `pyqflib/module.cpp`
    and `pyqfflib/qflib/__init__.py`. 
    They implement and register the following Python callable functions  
	qf.mktList,  qf.mktClear, qf.ycCreate, qf.df, qf.fwdDf, qf.spotRate, qf.fwdRate  


VERSION 0.5.0
-------------

### Additions

1. New files `qflib/math/interpol/piecewisepolynomial.hpp` and `piecewisepolynomial.cpp`.   
	They define the PiecewisePolynomial class template.

2. New files `qflib/sptr.hpp` and `qflib/sptrmap.hpp`.  
	Smart pointer aliases and a string to smart poitner map class template.

### Modifications

1. In file `pyqflib/pyfunctions0.cpp`.  
    Added definition of functions pyQfPPolyEval and pyQfPPolyIntegral

2. In files `pyqflib/pymodule.cpp` and `pyqflib/qflib/__init__.py`   
    Added registration for functions qf.ppolyEval and qf.ppolyIntegral.

3. In files `examples/Python/qflib-examples.py` and `examples/Python/qflib-examples.ipynb`   
    Added example calls to qf.ppolyEval and qf.ppolyIntegral.


VERSION 0.4.0
-------------

### Additions

1. New file `qflib/math/matrix.hpp`.
	It defines aliases for the Vector and Matrix classes to be used in numerical work.

2. New file `pyqflib/pyutils.hpp`.
	It implements the utility functions asVector, asMatrix, asNumPy


### Modifications

1. Qflib now has dependency on the armadillo C++ matrix library.
  All `CMakeLists.txt` files have been updated.

2. In file `pyqflib/pyfunctions0.cpp`.
  Added definition of function pyQfEchoMatrix

3. In files `pyqflib/pymodule.cpp` and `pyqflib/qflib/__init__.py`
    Added registration for function qf.echoMatrix.

4. In files `examples/Python/qflib-examples.py` and `examples/Python/qflib-examples.ipynb`
    Added example calls to qf.echoMatrix.


VERSION 0.3.0
-------------

### Modifications

1. In `qflib/pricers/simplepricers.hpp` and `simplepricers.cpp`
  Added implementation of pricing functions digitalOptionBS and europeanOptionBS

2. In file `pyqflib/pyfunctions1.cpp`.
  Added definition of functions pyQfDigiBS and pyQfEuroBS.

3. In files `pyqflib/pymodule.cpp` and `pyqflib/qflib/__init__.py`
    Added registration for functions qf.digiBS and qf.euroBS

4. In files `examples/Python/qflib-examples.py` and `examples/Python/qflib-examples.ipynb`
    Added example calls to qf.digiBS and qf.euroBS


VERSION 0.2.0
-------------

### Additions

1. New file `qflib/exception.hpp`.  
    Definition of qf::Exception class and the QF_ASSERT macro.

2. New folder `qflib/math/stats` to contain statistics related source files.

3. New files `qflib/math/stats/errorfunction.hpp` and `errorfunction.cpp`.  
    Definition of class ErrorFunction.

4. New files `qflib/math/stats/univariatedistribution.hpp` and `normaldistribution.hpp`.  
    Definition of `UnivariateDistribution` and `NormalDistribution` classes.

5. New folder `qflib/math/pricers` to contain pricing related source files.

6. New files `qflib/pricers/simplepricers.hpp` and `simplepricers.cpp`.  
    Definition of the function fwdPrice.

7. In file `pyqflib/pyfunctions0.cpp`.  
    Added definition of the following functions:  
    pyQrfErf, pyQrfInvErf, pyQrfNormalCdf, pyQrfNormalInvCdf

8. New file `pyqrflib/pyfunctions1.cpp`.  
    Added definition of function pyQfFwdPrice.

9. In files `pyqflib/pymodule.cpp` and `pyqflib/qflib/__init__.py`   
    Added registration for functions:  
    qf.erf, qf.invErf, qf.normalCdf, qf.normalInvCdf, qf.fwdPrice

10. In files `examples/Python/qflib-examples.py` and `examples/Python/qflib-examples.ipynb`   
    Added example calls to qf.erf, qf.invErf, qf.normalCdf, qf.normalInvCdf, qf.fwdPrice

### Modifications

1. Removed unnecessary file `qflib/empty.cpp`


VERSION 0.1.0
-------------

### Additions

1. Top level CMakeLists.txt file with projet-wide settings

2. New folder `qflib` with CMakeLists.txt and start-up code for the core library.

3. New folder `pyqflib` with CMakeLists.txt and start-up code for the Python interface.

4. This release notes file.

5. `.gitignore` file for managing which files to keep under revision control.

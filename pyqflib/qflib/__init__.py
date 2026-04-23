<<<<<<< HEAD
<<<<<<< HEAD
import qflib.pyqflib

###################
# function group 0

def version(): 
    """qflib library version.

    Returns
    -------
    str
        version in the format Major.Minor.Revision
    """
    return pyqflib.version()


def sayHello(name): 
    """Says hello.

    Parameters
    ----------
    name : str
        caller name

    Returns
    -------
    str
        greeting
    """
    return pyqflib.sayHello(name)


def outerProd(vector1, vector2):
    """Computes the outer product of two numerical vectors.

    Parameters
    ----------
    vector1 : list(double) or 1D numpy array
        first vector
    vector2: list(double) or 1D numpy array
        second vector

    Returns
    -------
    2D numpy array
        outer product as matrix
    """
    return pyqflib.outerProd(vector1, vector2)


def polyProd(vector1, vector2):
    """Computes the product of two polynomials.

    Parameters
    ----------
    vector1 : list(double) or 1D numpy array
        coefficients of first vector, in decreasing order
    vector2: list(double) or 1D numpy array
        coefficients of second vector, in decreasing order

    Returns
    -------
    1D numpy array
        coeffcients of the polynomial product
    """
    return pyqflib.polyProd(vector1, vector2)


def erf(x):
    """Error function at `x`. 
    """
    return pyqflib.erf(x)


def invErf(x):
    """Inverse error function at `x`. 
    """
    return pyqflib.invErf(x)


def normalCdf(x):
    """Cumulative standard normal distribution at `x`. 
    """
    return pyqflib.normalCdf(x)


def normalInvCdf(x):
    """Inverse of the cumulative standard normal distribution at quantile `x`.
    """
    return pyqflib.normalInvCdf(x)


def echoMatrix(mat):
    """Echoes the input matrix.

    Parameters
    ----------
    mat : 2D numpy array
        input matrix

    Returns
    -------
    2D numpy array
        the input matrix `mat`
    """
    return pyqflib.echoMatrix(mat)


def cholDcmp(mat): 
    """Cholesky decomposition of the input matrix. 

    Parameters
    ----------
    mat : 2D numpy array
        input square matrix

    Returns
    -------
    2D numpy array
       lower triangular Cholesky factor
    """
    return pyqflib.cholDcmp(mat)


def eigenSym(mat): 
    """Eigenvalues and eigenvectors of a symmetric matrix. 

    Parameters
    ----------
    mat : 2D numpy array
        input symmetric matrix

    Returns
    -------
    dictionary
        Eigenvals :  1D numpy array
            the eigenvalues
        Eigenvecs : 2D numpy array
            the eigenvectors in column order
    """
    return pyqflib.eigenSym(mat)


def specTrunc(mat): 
    """Nearest positive definite matrix using spectral truncation. 

    Parameters
    ----------
    mat : 2D numpy array
        input symmetric matrix

    Returns
    -------
    2D numpy array
        the nearest to `mat` positive definite matrix
    """
    return pyqflib.specTrunc(mat)


def ppolyEval(bkpoints, values, polyorder, xvec, derivorder): 
    """Values and derivatives of a piecewise polynomial function at a set of points.

    Parameters
    ----------
    bkpoints : list(double) or 1D numpy array
        breakpoints of the piecewise polynomial function
    values : list(double) or 1D numpy array
        corresponding values at each breakpoint
    polyorder : {0, 1}
        polynomial order of the segments (constant or linear)
    xvec : list(double) or 1D numpy array
        points at which values or derivatives are evaluated
    derivorder : int (>= 0)
        if 0, values are computed, else derivatives of `derivorder` order  

    Returns
    -------
    1D numpy array
        values or derivatives at each point in `xvec`
    
    Notes
    -----
    1. If `polyorder`==0, the value at the left breakpoint is used for the segment.
    2. At points outside the breakpoint span constant extrapolation is used.
    """
    return pyqflib.ppolyEval(bkpoints, values, polyorder, xvec, derivorder)


def ppolyIntegral(bkpoints, values, polyorder, xstart, xvec): 
    """Integral of a piecewise polynomial function from `xstart` to each point in `xvec`.

    Parameters
    ----------
    bkpoints : list(double) or 1D numpy array
        breakpoints of the piecewise polynomial function
    values : list(double) or 1D numpy array
        corresponding values at each breakpoint
    polyorder : {0, 1}
        polynomial order of the segments (constant or linear)
    xstart : double
        starting point of each interval
    xvec : list(double) or 1D numpy array
        end points one for each interval

    Returns
    -------
    1D numpy array
        values of the integral
    
    Notes
    -----
    1. If `polyorder`==0, the value at the left breakpoint is used for the segment.
    2. At points outside the breakpoint span constant extrapolation is used.
    """
    return pyqflib.ppolyIntegral(bkpoints, values, polyorder, xstart, xvec)


def ppolySum(bkpoints1, values1, bkpoints2, values2, polyorder): 
    """Sum of two piecewise polynomial functions.

    Parameters
    ----------
    bkpoints1 : list(double) or 1D numpy array
        breakpoints of the first piecewise polynomial function
    values1 : list(double) or 1D numpy array
        corresponding values at each breakpoint of the first function
    bkpoints2 : list(double) or 1D numpy array
        breakpoints of the second piecewise polynomial function
    values2 : list(double) or 1D numpy array
        corresponding values at each breakpoint of the second function
    polyorder : {0, 1}
        polynomial order of the segments (constant or linear)

    Returns
    -------
    2D numpy array
        breakpoints and corresponding values of the sum
    
    """
    return pyqflib.ppolySum(bkpoints1, values1, bkpoints2, values2, polyorder)


def polyBracket(coeffs, lolim, uplim, nsubs): 
    """Bracketing the roots of a polynomial.

    Parameters
    ----------
    coeffs : list(double) or 1D numpy array
        polynomial coefficients in increasing order
    lolim : double
        lower limit of root search
    uplim : double
        upper limit of root search
    nsubs : int
        number of subdivisions of the (lolim, uplim) interval

    Returns
    -------
    2D numpy array
        n x 2 array, with n the number of detected roots. 
        Each row has the left and right boundary of a root bracketing interval.
    """
    return pyqflib.polyBracket(coeffs, lolim, uplim, nsubs)


def polySecant(coeffs, lolim, uplim, tol): 
    """Root search of a polynomial using the secant mathod.

    Parameters
    ----------
    coeffs : list(double) or 1D numpy array
        polynomial coefficients in increasing order
    lolim : double
        lower limit of root search
    uplim : double
        upper limit of root search
    tol : double
        search tolerance

    Returns
    -------
    double
        the root
    """
    return pyqflib.polySecant(coeffs, lolim, uplim, tol)


def toContCmpd(rate, annfreq): 
    """Continuously compounded from periodically compounded interest rate. 

    Parameters
    ----------
    rate : double
        periodically compounded rate
    annfreq : int (> 0)
        the annual compounding frequency

    Returns
    -------
    double
        equivalent continuously compounded rate
    """
    return pyqflib.toContCmpd(rate, annfreq)

def fromContCmpd(rate, annfreq): 
    """Periodically compounded from continuously compounded interest rate. 

    Parameters
    ----------
    rate : double
        continuously compounded rate
    annfreq : int (> 0)
        the annual comounding frequency

    Returns
    -------
    double
        equivalent periodically compounded rate
    """
    return pyqflib.fromContCmpd(rate, annfreq)


###################
# function group 1

def fwdPrice(spot, timetoexp, intrate, divyield):
    """Forward price of an asset.

    Parameters
    ----------
    spot : double
        asset spot price
    timetoexp : double
        time to expiration in years
    intrate : double
        interest rate, p.a. and c.c.
    divyield : double    
        asset dividend yield, p.a. and c.c.

    Returns
    -------
    double
        asset forward price
     """
    return pyqflib.fwdPrice(spot, timetoexp, intrate, divyield)


def qFwdPrice(spot, timetoexp, intrate, divyield, assetvol, fxvol, correl):
    """Quanto forward price of an asset. 

    Parameters
    ----------
    spot : double
        asset spot price in asset (foreign) currency
    timetoexp : double
        time to expiration in years
    intrate : double
        interest rate in the asset (foreign) market, p.a. and c.c.
    divyield : double    
        asset dividend yield, p.a. and c.c.
    assetvol : double
        asset return volatility, p.a.
    fxvol : double
        volatility of exchange rate between asset (foreign) and payoff (domestic) currency
    correl : double
        correlation between asset and FX returns, both in asset currency numeraire
    
    Returns
    -------
    double
        forward price of an asset quanto-ed into payoff (domestic) currency
    """
    return pyqflib.qFwdPrice(spot, timetoexp, intrate, divyield, assetvol, fxvol, correl)


def digiBS(payofftype, spot, strike, timetoexp, intrate, divyield, volatility):
    """Price and Greeks of a European digital option in the Black-Scholes model. 

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    spot : double
        asset spot price
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    intrate : double
        interest rate, p.a. and c.c.
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double
        asset return volatility

    Returns
    -------
    1D numpy array
        Array with Price, Delta, Gamma, Theta, Vega
    """
    return pyqflib.digiBS(payofftype, spot, strike, timetoexp, intrate, divyield, volatility)


def euroBS(payofftype, spot, strike, timetoexp, intrate, divyield, volatility):
    """Price and Greeks of a European option in the Black-Scholes model. 

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    spot : double
        asset spot price
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    intrate : double
        interest rate, p.a. and c.c.
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double
        asset return volatility

    Returns
    -------
    1D numpy array
        Array with Price, Delta, Gamma, Theta, Vega
    """
    return pyqflib.euroBS(payofftype, spot, strike, timetoexp, intrate, divyield, volatility)

def koFwd(spot, strike, kolevel, timetoexp, timetoko, intrate, divyield, volatility):
    """Price of a knockout forward contract in the Black-Scholes model. 

    Parameters
    ----------
    spot : double
        asset spot price
    strike : double
        strike price
    kolevel : double
        knockout level
    timetoexp : double
        time to expiration in years
    timetoko : double
        time to knockout
    intrate : double
        interest rate, p.a. and c.c.
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double
        asset return volatility

    Returns
    -------
    double
        price of the knockout forward
    """
    return pyqflib.koFwd(spot, strike, kolevel, timetoexp, timetoko, intrate, divyield, volatility)


def qEuroBS(payofftype, spot, strike, timetoexp, discrate, growthrate, divyield, assetvol, fxvol, correl):
    """Price of a quanto European option in the Black-Scholes model.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    spot : double
        asset spot price in asset (foreign) currency
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    discrate : double
        domestic risk-free rate rd, p.a. and c.c. (used for discounting)
    growthrate : double
        foreign risk-free rate rf, p.a. and c.c. (used for quanto drift)
    divyield : double
        asset dividend yield q, p.a. and c.c.
    assetvol : double
        asset return volatility sigmaS, p.a.
    fxvol : double
        FX volatility sigmaQ (CCY1/CCY2), p.a.
    correl : double
        correlation rho between asset and FX returns

    Returns
    -------
    double
        quanto European option price in payoff (domestic) currency CCY2

    Notes
    -----
    The quanto-adjusted dividend yield is q' = rd - rf + q - rho*sigmaS*sigmaQ.
    Pricing uses Black-Scholes with discount rate rd and dividend yield q'.
    As strike -> 0, the call price converges to exp(-rd*T) * exp((rf - q + rho*sigmaS*sigmaQ)*T) * spot.
    """
    return pyqflib.qEuroBS(payofftype, spot, strike, timetoexp, discrate, growthrate, divyield, assetvol, fxvol, correl)


###################
# function group 2

def mktList():
    """Names of all market objects.

    Returns
    -------
    dictionary
        YieldCurves : list with names of yield curves
        Volatilities : list with names of volatility term structures   
    """
    return pyqflib.mktList()


def mktClear():
    """Clears all market objects.

    Returns
    -------
    TRUE
    """
    return pyqflib.mktClear()


def ycCreate(ycname, tmats, vals, valtype):
    """Creates a new yield curve.

    Parameters
    ----------
    ycname : str
        new yield curve name
    tmats : list(double) or 1D numpy array
        maturities in years
    vals : list(double) or 1D numpy array
        zero bond prices or interest rates to each maturity in `tmats`
    valtype : {0, 1, 2}
        0: spot interest rates, 1: forward interest rates, 2: zero bond prices

    Returns
    -------
    str 
        name of the newly created yield curve

    Notes
    -----
    1. Yield curve names are case insensitive.
    2. A new yield curve replaces an existing one if they have the same name.
    """
    return pyqflib.ycCreate(ycname, tmats, vals, valtype)


def discount(ycname, tmat):
    """Discount factor from yield curve.

    Parameters
    ----------
    ycname : str
        name of the yield curve
    tmat : double
        time to maturity of the discount factor, in years

    Returns
    -------
    double
        discount factor
    """
    return pyqflib.discount(ycname, tmat)


def fwdDiscount(ycname, tmat1, tmat2):
    """Forward discount factor from yield curve.

    Parameters
    ----------
    ycname : str
        name of the yield curve
    tmat1 : double
        time to reset of the forward discount factor, in years
    tmat2 : double
        time to maturity of the forward discount factor, in years

    Returns
    -------
    double
        forward discount factor
    """
    return pyqflib.fwdDiscount(ycname, tmat1, tmat2)


def spotRate(ycname, tmat):
    """Spot interest rate from yield curve.

    Parameters
    ----------
    ycname : str
        name of the yield curve
    tmat : double
        time to maturity of the interest rate, in years

    Returns
    -------
    double
        spot interest rate
    """
    return pyqflib.spotRate(ycname, tmat)


def fwdRate(ycname, tmat1, tmat2):
    """Forward interest rate from yield curve.

    Parameters
    ----------
    ycname : str
        name of the yield curve
    tmat1 : double
        time to reset of the forward discount rate, in years
    tmat2 : double
        time to maturity of the forward discount rate, in years

    Returns
    -------
    double
        the forward discount rate
    """
    return pyqflib.fwdRate(ycname, tmat1, tmat2)


def volCreate(volname, tmats, vals, valtype):
    """Creates a new volatility term structure.

    Parameters
    ----------
    volname : str
        name of the volatility term structure
    tmats : list(double) or 1D numpy array
        maturities (expirations) in years
    vals : list(double) or 1D numpy array
        volatility values to each maturity in `tmats`
    valtype : {0, 1}
        0: spot volatilities, 1: forward volatilities

    Returns
    -------
    str 
        name of the newly created volatility term structure
    """
    return pyqflib.volCreate(volname, tmats, vals, valtype)


def spotVol(volname, tmat):
    """Spot volatility from term structure.

    Parameters
    ----------
    volname : str
        name of the volatility term structure
    tmat : double
        time to maturity (expiration) of the spot volatility, in years

    Returns
    -------
    double
        spot volatility
    """
    return pyqflib.spotVol(volname, tmat)


def fwdVol(volname, tmat1, tmat2):
    """Forward volatility from term structure.

    Parameters
    ----------
    volname : str
        name of the volatility term structure
    tmat1 : double
        time to reset of the forward volatility, in years
    tmat2 : double
        time to maturity (expiration) of the forward volatility, in years

    Returns
    -------
    double
        forward volatility
    """
    return pyqflib.fwdVol(volname, tmat1, tmat2)


###################
# function group 3

def euroBSMC(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, mcparams, npaths):
    """Price and standard error of a European option in the Black-Scholes model using Monte Carlo.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    spot : double
        asset spot price
    discountcrv : str
        discount yield curve name
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double or string
        asset return volatility or vol term structure name
    mcparams : dictionary
        URNGTYPE : 'MINSTDRAND', 'MT19937', 'RANLUX3', 'RANLUX4'
        PATHGENTYPE : 'EULER'
        CONTROLVARTYPE : 'ANTITHETIC', 'NONE'
    npaths : int
        number of Monte Carlo paths
    
    Returns
    -------
    dictionary
        Mean : Monte Carlo mean price
        StdErr : Monte Carlo standard error
    """
    return pyqflib.euroBSMC(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, mcparams, npaths)


def digiBSMC(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, mcparams, npaths):
    """Price and standard error of a digital option in the Black-Scholes model using Monte Carlo.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    spot : double
        asset spot price
    discountcrv : str
        discount yield curve name
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double or string
        asset return volatility or vol term structure name
    mcparams : dictionary
        URNGTYPE : 'MINSTDRAND', 'MT19937', 'RANLUX3', 'RANLUX4', 'SOBOL'
        PATHGENTYPE : 'EULER'
        CONTROLVARTYPE : 'ANTITHETIC', 'NONE'
    npaths : int
        number of Monte Carlo paths
    
    Returns
    -------
    dictionary
        Mean : Monte Carlo mean price
        StdErr : Monte Carlo standard error
    """
    return pyqflib.digiBSMC(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, mcparams, npaths)


def asianBasketBSMC(payofftype, strike, fixtimes, assetquantities, spots, discountcrv, divyields, 
                    volatilities, correlmat, mcparams, npaths):
    """Price and standard error of an Asian basket option in the Black-Scholes model using Monte Carlo.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    fixtimes : list(double) or 1D numpy array
        fixing times in years, unique and in increasing order
    assetquantities : list(double) or 1D numpy array
        asset quantities
    spots : list(double) or 1D numpy array
        asset spot prices
    discountcrv : str
        discount yield curve name
    divyields : list(double) or 1D numpy array
        asset dividend yields, p.a. and c.c.
    volatilities : list(double) or 1D numpy array
        asset return volatilities
    correlmat : 2D numpy array
        asset correlation matrix
    mcparams : dictionary
        URNGTYPE : 'MINSTDRAND', 'MT19937', 'RANLUX3', 'RANLUX4'
        PATHGENTYPE : 'EULER'
        CONTROLVARTYPE : 'ANTITHETIC', 'NONE'
    npaths : int
        number of Monte Carlo paths
    
    Returns
    -------
    dictionary
        Mean : Monte Carlo mean price
        StdErr : Monte Carlo standard error
    """
    return pyqflib.asianBasketBSMC(payofftype, strike, fixtimes, assetquantities, spots, discountcrv, divyields, 
                                   volatilities, correlmat, mcparams, npaths)


def worstofDigiBSMC(payofftype, strike, timetofix, timetoexp, spots, discountcrv, divyields, 
                    volatilities, correlmat, mcparams, npaths):
    """Price and standard error of a worst-of digital option in the Black-Scholes model using Monte Carlo.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    timetofix : double
        time to fix in years
    timetoexp : double
        time to expire in years
    spots : list(double) or 1D numpy array
        asset spot prices
    discountcrv : str
        discount yield curve name
    divyields : list(double) or 1D numpy array
        asset dividend yields, p.a. and c.c.
    volatilities : list(double) or 1D numpy array
        asset return volatilities
    correlmat : 2D numpy array
        asset correlation matrix
    mcparams : dictionary
        URNGTYPE : 'MINSTDRAND', 'MT19937', 'RANLUX3', 'RANLUX4'
        PATHGENTYPE : 'EULER'
        CONTROLVARTYPE : 'ANTITHETIC', 'NONE'
    npaths : int
        number of Monte Carlo paths
    
    Returns
    -------
    dictionary
        Mean : Monte Carlo mean price
        StdErr : Monte Carlo standard error
    """
    return pyqflib.worstofDigiBSMC(payofftype, strike, timetofix, timetoexp, spots, discountcrv, divyields, 
                                   volatilities, correlmat, mcparams, npaths)


###################
# function group 4

def euroBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams, allresults=False):
    """Price of a European option in the Black-Scholes model using finite difference PDE.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    spot : double
        asset spot price
    discountcrv : str
        discount yield curve name
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double
        asset return volatility
    pdeparams : dictionary
        NTIMESTEPS : (int) number of time steps
        NSPOTNODES : (int) number of spot nodes
        NSTDDEVS : (double) number of standard deviations for the spot range
        THETA : (double) scheme implicitness
    allresults : bool
        FALSE for price only; TRUE for the full grid of results
    
    Returns
    -------
    dictionary
        Price : PDE price
        Times : 1D array with times
        Spots : 1D array with spots
        Values : 2D array with option values

    Notes
    -----
    The keys `Times`, `Spots` and `Values` are available only if `allresults`==True.
    """
    return pyqflib.euroBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams, allresults)


def digiBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams, allresults=False):
    """Price of a digital option in the Black-Scholes model using finite difference PDE.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    spot : double
        asset spot price
    discountcrv : str
        discount yield curve name
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double
        asset return volatility
    pdeparams : dictionary
        NTIMESTEPS : (int) number of time steps
        NSPOTNODES : (int) number of spot nodes
        NSTDDEVS : (double) number of standard deviations for the spot range
        THETA : (double) scheme implicitness
    allresults : bool
        FALSE for price only; TRUE for the full grid of results
    
    Returns
    -------
    dictionary
        Price : PDE price
        Times : 1D array with times
        Spots : 1D array with spots
        Values : 2D array with option values

    Notes
    -----
    The keys `Times`, `Spots` and `Values` are available only if `allresults`==True.
    """
    return pyqflib.digiBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams, allresults)


def amerBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams, allresults=False):
    """Price of an American option in the Black-Scholes model using finite difference PDE.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    spot : double
        asset spot price
    discountcrv : str
        discount yield curve name
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double
        asset return volatility
    pdeparams : dictionary
        NTIMESTEPS : (int) number of time steps
        NSPOTNODES : (int) number of spot nodes
        NSTDDEVS : (double) number of standard deviations for the spot range
        THETA : (double) scheme implicitness
    allresults : bool
        False for price only; True for the full grid of results
    
    Returns
    -------
    dictionary
        Price : PDE price
        Times : 1D array with times
        Spots : 1D array with spots
        Values : 2D array with option values

    Notes
    -----
    The keys `Times`, `Spots` and `Values` are available only if `allresults`==True.
    """
    return pyqflib.amerBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams, allresults)
=======
import qflib.pyqflib

###################
# function group 0

def version(): 
    """qflib library version.

    Returns
    -------
    str
        version in the format Major.Minor.Revision
    """
    return pyqflib.version()


def sayHello(name): 
    """Says hello.

    Parameters
    ----------
    name : str
        caller name

    Returns
    -------
    str
        greeting
    """
    return pyqflib.sayHello(name)


def outerProd(vector1, vector2):
    """Computes the outer product of two numerical vectors.

    Parameters
    ----------
    vector1 : list(double) or 1D numpy array
        first vector
    vector2: list(double) or 1D numpy array
        second vector

    Returns
    -------
    2D numpy array
        outer product as matrix
    """
    return pyqflib.outerProd(vector1, vector2)


def polyProd(vector1, vector2):
    """Computes the product of two polynomials.

    Parameters
    ----------
    vector1 : list(double) or 1D numpy array
        coefficients of first vector, in decreasing order
    vector2: list(double) or 1D numpy array
        coefficients of second vector, in decreasing order

    Returns
    -------
    1D numpy array
        coeffcients of the polynomial product
    """
    return pyqflib.polyProd(vector1, vector2)


def erf(x):
    """Error function at `x`. 
    """
    return pyqflib.erf(x)


def invErf(x):
    """Inverse error function at `x`. 
    """
    return pyqflib.invErf(x)


def normalCdf(x):
    """Cumulative standard normal distribution at `x`. 
    """
    return pyqflib.normalCdf(x)


def normalInvCdf(x):
    """Inverse of the cumulative standard normal distribution at quantile `x`.
    """
    return pyqflib.normalInvCdf(x)


def echoMatrix(mat):
    """Echoes the input matrix.

    Parameters
    ----------
    mat : 2D numpy array
        input matrix

    Returns
    -------
    2D numpy array
        the input matrix `mat`
    """
    return pyqflib.echoMatrix(mat)


def cholDcmp(mat): 
    """Cholesky decomposition of the input matrix. 

    Parameters
    ----------
    mat : 2D numpy array
        input square matrix

    Returns
    -------
    2D numpy array
       lower triangular Cholesky factor
    """
    return pyqflib.cholDcmp(mat)


def eigenSym(mat): 
    """Eigenvalues and eigenvectors of a symmetric matrix. 

    Parameters
    ----------
    mat : 2D numpy array
        input symmetric matrix

    Returns
    -------
    dictionary
        Eigenvals :  1D numpy array
            the eigenvalues
        Eigenvecs : 2D numpy array
            the eigenvectors in column order
    """
    return pyqflib.eigenSym(mat)


def specTrunc(mat): 
    """Nearest positive definite matrix using spectral truncation. 

    Parameters
    ----------
    mat : 2D numpy array
        input symmetric matrix

    Returns
    -------
    2D numpy array
        the nearest to `mat` positive definite matrix
    """
    return pyqflib.specTrunc(mat)


def ppolyEval(bkpoints, values, polyorder, xvec, derivorder): 
    """Values and derivatives of a piecewise polynomial function at a set of points.

    Parameters
    ----------
    bkpoints : list(double) or 1D numpy array
        breakpoints of the piecewise polynomial function
    values : list(double) or 1D numpy array
        corresponding values at each breakpoint
    polyorder : {0, 1}
        polynomial order of the segments (constant or linear)
    xvec : list(double) or 1D numpy array
        points at which values or derivatives are evaluated
    derivorder : int (>= 0)
        if 0, values are computed, else derivatives of `derivorder` order  

    Returns
    -------
    1D numpy array
        values or derivatives at each point in `xvec`
    
    Notes
    -----
    1. If `polyorder`==0, the value at the left breakpoint is used for the segment.
    2. At points outside the breakpoint span constant extrapolation is used.
    """
    return pyqflib.ppolyEval(bkpoints, values, polyorder, xvec, derivorder)


def ppolyIntegral(bkpoints, values, polyorder, xstart, xvec): 
    """Integral of a piecewise polynomial function from `xstart` to each point in `xvec`.

    Parameters
    ----------
    bkpoints : list(double) or 1D numpy array
        breakpoints of the piecewise polynomial function
    values : list(double) or 1D numpy array
        corresponding values at each breakpoint
    polyorder : {0, 1}
        polynomial order of the segments (constant or linear)
    xstart : double
        starting point of each interval
    xvec : list(double) or 1D numpy array
        end points one for each interval

    Returns
    -------
    1D numpy array
        values of the integral
    
    Notes
    -----
    1. If `polyorder`==0, the value at the left breakpoint is used for the segment.
    2. At points outside the breakpoint span constant extrapolation is used.
    """
    return pyqflib.ppolyIntegral(bkpoints, values, polyorder, xstart, xvec)


def ppolySum(bkpoints1, values1, bkpoints2, values2, polyorder): 
    """Sum of two piecewise polynomial functions.

    Parameters
    ----------
    bkpoints1 : list(double) or 1D numpy array
        breakpoints of the first piecewise polynomial function
    values1 : list(double) or 1D numpy array
        corresponding values at each breakpoint of the first function
    bkpoints2 : list(double) or 1D numpy array
        breakpoints of the second piecewise polynomial function
    values2 : list(double) or 1D numpy array
        corresponding values at each breakpoint of the second function
    polyorder : {0, 1}
        polynomial order of the segments (constant or linear)

    Returns
    -------
    2D numpy array
        breakpoints and corresponding values of the sum
    
    """
    return pyqflib.ppolySum(bkpoints1, values1, bkpoints2, values2, polyorder)


def polyBracket(coeffs, lolim, uplim, nsubs): 
    """Bracketing the roots of a polynomial.

    Parameters
    ----------
    coeffs : list(double) or 1D numpy array
        polynomial coefficients in increasing order
    lolim : double
        lower limit of root search
    uplim : double
        upper limit of root search
    nsubs : int
        number of subdivisions of the (lolim, uplim) interval

    Returns
    -------
    2D numpy array
        n x 2 array, with n the number of detected roots. 
        Each row has the left and right boundary of a root bracketing interval.
    """
    return pyqflib.polyBracket(coeffs, lolim, uplim, nsubs)


def polySecant(coeffs, lolim, uplim, tol): 
    """Root search of a polynomial using the secant mathod.

    Parameters
    ----------
    coeffs : list(double) or 1D numpy array
        polynomial coefficients in increasing order
    lolim : double
        lower limit of root search
    uplim : double
        upper limit of root search
    tol : double
        search tolerance

    Returns
    -------
    double
        the root
    """
    return pyqflib.polySecant(coeffs, lolim, uplim, tol)


def toContCmpd(rate, annfreq): 
    """Continuously compounded from periodically compounded interest rate. 

    Parameters
    ----------
    rate : double
        periodically compounded rate
    annfreq : int (> 0)
        the annual compounding frequency

    Returns
    -------
    double
        equivalent continuously compounded rate
    """
    return pyqflib.toContCmpd(rate, annfreq)

def fromContCmpd(rate, annfreq): 
    """Periodically compounded from continuously compounded interest rate. 

    Parameters
    ----------
    rate : double
        continuously compounded rate
    annfreq : int (> 0)
        the annual comounding frequency

    Returns
    -------
    double
        equivalent periodically compounded rate
    """
    return pyqflib.fromContCmpd(rate, annfreq)


###################
# function group 1

def fwdPrice(spot, timetoexp, intrate, divyield):
    """Forward price of an asset.

    Parameters
    ----------
    spot : double
        asset spot price
    timetoexp : double
        time to expiration in years
    intrate : double
        interest rate, p.a. and c.c.
    divyield : double    
        asset dividend yield, p.a. and c.c.

    Returns
    -------
    double
        asset forward price
     """
    return pyqflib.fwdPrice(spot, timetoexp, intrate, divyield)


def qFwdPrice(spot, timetoexp, intrate, divyield, assetvol, fxvol, correl):
    """Quanto forward price of an asset. 

    Parameters
    ----------
    spot : double
        asset spot price in asset (foreign) currency
    timetoexp : double
        time to expiration in years
    intrate : double
        interest rate in the asset (foreign) market, p.a. and c.c.
    divyield : double    
        asset dividend yield, p.a. and c.c.
    assetvol : double
        asset return volatility, p.a.
    fxvol : double
        volatility of exchange rate between asset (foreign) and payoff (domestic) currency
    correl : double
        correlation between asset and FX returns, both in asset currency numeraire
    
    Returns
    -------
    double
        forward price of an asset quanto-ed into payoff (domestic) currency
    """
    return pyqflib.qFwdPrice(spot, timetoexp, intrate, divyield, assetvol, fxvol, correl)


def digiBS(payofftype, spot, strike, timetoexp, intrate, divyield, volatility):
    """Price and Greeks of a European digital option in the Black-Scholes model. 

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    spot : double
        asset spot price
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    intrate : double
        interest rate, p.a. and c.c.
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double
        asset return volatility

    Returns
    -------
    1D numpy array
        Array with Price, Delta, Gamma, Theta, Vega
    """
    return pyqflib.digiBS(payofftype, spot, strike, timetoexp, intrate, divyield, volatility)


def euroBS(payofftype, spot, strike, timetoexp, intrate, divyield, volatility):
    """Price and Greeks of a European option in the Black-Scholes model. 

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    spot : double
        asset spot price
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    intrate : double
        interest rate, p.a. and c.c.
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double
        asset return volatility

    Returns
    -------
    1D numpy array
        Array with Price, Delta, Gamma, Theta, Vega
    """
    return pyqflib.euroBS(payofftype, spot, strike, timetoexp, intrate, divyield, volatility)

def koFwd(spot, strike, kolevel, timetoexp, timetoko, intrate, divyield, volatility):
    """Price of a knockout forward contract in the Black-Scholes model. 

    Parameters
    ----------
    spot : double
        asset spot price
    strike : double
        strike price
    kolevel : double
        knockout level
    timetoexp : double
        time to expiration in years
    timetoko : double
        time to knockout
    intrate : double
        interest rate, p.a. and c.c.
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double
        asset return volatility

    Returns
    -------
    double
        price of the knockout forward
    """
    return pyqflib.koFwd(spot, strike, kolevel, timetoexp, timetoko, intrate, divyield, volatility)


###################
# function group 2

def mktList():
    """Names of all market objects.

    Returns
    -------
    dictionary
        YieldCurves : list with names of yield curves
        Volatilities : list with names of volatility term structures   
    """
    return pyqflib.mktList()


def mktClear():
    """Clears all market objects.

    Returns
    -------
    TRUE
    """
    return pyqflib.mktClear()


def ycCreate(ycname, tmats, vals, valtype):
    """Creates a new yield curve.

    Parameters
    ----------
    ycname : str
        new yield curve name
    tmats : list(double) or 1D numpy array
        maturities in years
    vals : list(double) or 1D numpy array
        zero bond prices or interest rates to each maturity in `tmats`
    valtype : {0, 1, 2}
        0: spot interest rates, 1: forward interest rates, 2: zero bond prices

    Returns
    -------
    str 
        name of the newly created yield curve

    Notes
    -----
    1. Yield curve names are case insensitive.
    2. A new yield curve replaces an existing one if they have the same name.
    """
    return pyqflib.ycCreate(ycname, tmats, vals, valtype)


def discount(ycname, tmat):
    """Discount factor from yield curve.

    Parameters
    ----------
    ycname : str
        name of the yield curve
    tmat : double
        time to maturity of the discount factor, in years

    Returns
    -------
    double
        discount factor
    """
    return pyqflib.discount(ycname, tmat)


def fwdDiscount(ycname, tmat1, tmat2):
    """Forward discount factor from yield curve.

    Parameters
    ----------
    ycname : str
        name of the yield curve
    tmat1 : double
        time to reset of the forward discount factor, in years
    tmat2 : double
        time to maturity of the forward discount factor, in years

    Returns
    -------
    double
        forward discount factor
    """
    return pyqflib.fwdDiscount(ycname, tmat1, tmat2)


def spotRate(ycname, tmat):
    """Spot interest rate from yield curve.

    Parameters
    ----------
    ycname : str
        name of the yield curve
    tmat : double
        time to maturity of the interest rate, in years

    Returns
    -------
    double
        spot interest rate
    """
    return pyqflib.spotRate(ycname, tmat)


def fwdRate(ycname, tmat1, tmat2):
    """Forward interest rate from yield curve.

    Parameters
    ----------
    ycname : str
        name of the yield curve
    tmat1 : double
        time to reset of the forward discount rate, in years
    tmat2 : double
        time to maturity of the forward discount rate, in years

    Returns
    -------
    double
        the forward discount rate
    """
    return pyqflib.fwdRate(ycname, tmat1, tmat2)


def volCreate(volname, tmats, vals, valtype):
    """Creates a new volatility term structure.

    Parameters
    ----------
    volname : str
        name of the volatility term structure
    tmats : list(double) or 1D numpy array
        maturities (expirations) in years
    vals : list(double) or 1D numpy array
        volatility values to each maturity in `tmats`
    valtype : {0, 1}
        0: spot volatilities, 1: forward volatilities

    Returns
    -------
    str 
        name of the newly created volatility term structure
    """
    return pyqflib.volCreate(volname, tmats, vals, valtype)


def spotVol(volname, tmat):
    """Spot volatility from term structure.

    Parameters
    ----------
    volname : str
        name of the volatility term structure
    tmat : double
        time to maturity (expiration) of the spot volatility, in years

    Returns
    -------
    double
        spot volatility
    """
    return pyqflib.spotVol(volname, tmat)


def fwdVol(volname, tmat1, tmat2):
    """Forward volatility from term structure.

    Parameters
    ----------
    volname : str
        name of the volatility term structure
    tmat1 : double
        time to reset of the forward volatility, in years
    tmat2 : double
        time to maturity (expiration) of the forward volatility, in years

    Returns
    -------
    double
        forward volatility
    """
    return pyqflib.fwdVol(volname, tmat1, tmat2)


###################
# function group 3

def euroBSMC(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, mcparams, npaths):
    """Price and standard error of a European option in the Black-Scholes model using Monte Carlo.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    spot : double
        asset spot price
    discountcrv : str
        discount yield curve name
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double or string
        asset return volatility or vol term structure name
    mcparams : dictionary
        URNGTYPE : 'MINSTDRAND', 'MT19937', 'RANLUX3', 'RANLUX4'
        PATHGENTYPE : 'EULER'
        CONTROLVARTYPE : 'ANTITHETIC', 'NONE'
    npaths : int
        number of Monte Carlo paths
    
    Returns
    -------
    dictionary
        Mean : Monte Carlo mean price
        StdErr : Monte Carlo standard error
    """
    return pyqflib.euroBSMC(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, mcparams, npaths)


def qEuroBSMC(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, mcparams, npaths,
              growthcrv, fxvol, correl):
    return pyqflib.qEuroBSMC(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, mcparams, npaths,
                              growthcrv, fxvol, correl)


def digiBSMC(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, mcparams, npaths):
    """Price and standard error of a digital option in the Black-Scholes model using Monte Carlo.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    spot : double
        asset spot price
    discountcrv : str
        discount yield curve name
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double or string
        asset return volatility or vol term structure name
    mcparams : dictionary
        URNGTYPE : 'MINSTDRAND', 'MT19937', 'RANLUX3', 'RANLUX4', 'SOBOL'
        PATHGENTYPE : 'EULER'
        CONTROLVARTYPE : 'ANTITHETIC', 'NONE'
    npaths : int
        number of Monte Carlo paths
    
    Returns
    -------
    dictionary
        Mean : Monte Carlo mean price
        StdErr : Monte Carlo standard error
    """
    return pyqflib.digiBSMC(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, mcparams, npaths)


def asianBasketBSMC(payofftype, strike, fixtimes, assetquantities, spots, discountcrv, divyields, 
                    volatilities, correlmat, mcparams, npaths):
    """Price and standard error of an Asian basket option in the Black-Scholes model using Monte Carlo.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    fixtimes : list(double) or 1D numpy array
        fixing times in years, unique and in increasing order
    assetquantities : list(double) or 1D numpy array
        asset quantities
    spots : list(double) or 1D numpy array
        asset spot prices
    discountcrv : str
        discount yield curve name
    divyields : list(double) or 1D numpy array
        asset dividend yields, p.a. and c.c.
    volatilities : list(double) or 1D numpy array
        asset return volatilities
    correlmat : 2D numpy array
        asset correlation matrix
    mcparams : dictionary
        URNGTYPE : 'MINSTDRAND', 'MT19937', 'RANLUX3', 'RANLUX4'
        PATHGENTYPE : 'EULER'
        CONTROLVARTYPE : 'ANTITHETIC', 'NONE'
    npaths : int
        number of Monte Carlo paths
    
    Returns
    -------
    dictionary
        Mean : Monte Carlo mean price
        StdErr : Monte Carlo standard error
    """
    return pyqflib.asianBasketBSMC(payofftype, strike, fixtimes, assetquantities, spots, discountcrv, divyields, 
                                   volatilities, correlmat, mcparams, npaths)


def worstofDigiBSMC(payofftype, strike, timetofix, timetoexp, spots, discountcrv, divyields, 
                    volatilities, correlmat, mcparams, npaths):
    """Price and standard error of a worst-of digital option in the Black-Scholes model using Monte Carlo.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    timetofix : double
        time to fix in years
    timetoexp : double
        time to expire in years
    spots : list(double) or 1D numpy array
        asset spot prices
    discountcrv : str
        discount yield curve name
    divyields : list(double) or 1D numpy array
        asset dividend yields, p.a. and c.c.
    volatilities : list(double) or 1D numpy array
        asset return volatilities
    correlmat : 2D numpy array
        asset correlation matrix
    mcparams : dictionary
        URNGTYPE : 'MINSTDRAND', 'MT19937', 'RANLUX3', 'RANLUX4'
        PATHGENTYPE : 'EULER'
        CONTROLVARTYPE : 'ANTITHETIC', 'NONE'
    npaths : int
        number of Monte Carlo paths
    
    Returns
    -------
    dictionary
        Mean : Monte Carlo mean price
        StdErr : Monte Carlo standard error
    """
    return pyqflib.worstofDigiBSMC(payofftype, strike, timetofix, timetoexp, spots, discountcrv, divyields, 
                                   volatilities, correlmat, mcparams, npaths)


###################
# function group 4

def euroBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams, allresults=False):
    """Price of a European option in the Black-Scholes model using finite difference PDE.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    spot : double
        asset spot price
    discountcrv : str
        discount yield curve name
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double
        asset return volatility
    pdeparams : dictionary
        NTIMESTEPS : (int) number of time steps
        NSPOTNODES : (int) number of spot nodes
        NSTDDEVS : (double) number of standard deviations for the spot range
        THETA : (double) scheme implicitness
    allresults : bool
        FALSE for price only; TRUE for the full grid of results
    
    Returns
    -------
    dictionary
        Price : PDE price
        Times : 1D array with times
        Spots : 1D array with spots
        Values : 2D array with option values

    Notes
    -----
    The keys `Times`, `Spots` and `Values` are available only if `allresults`==True.
    """
    return pyqflib.euroBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams, allresults)


def digiBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams, allresults=False):
    """Price of a digital option in the Black-Scholes model using finite difference PDE.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    spot : double
        asset spot price
    discountcrv : str
        discount yield curve name
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double
        asset return volatility
    pdeparams : dictionary
        NTIMESTEPS : (int) number of time steps
        NSPOTNODES : (int) number of spot nodes
        NSTDDEVS : (double) number of standard deviations for the spot range
        THETA : (double) scheme implicitness
    allresults : bool
        FALSE for price only; TRUE for the full grid of results
    
    Returns
    -------
    dictionary
        Price : PDE price
        Times : 1D array with times
        Spots : 1D array with spots
        Values : 2D array with option values

    Notes
    -----
    The keys `Times`, `Spots` and `Values` are available only if `allresults`==True.
    """
    return pyqflib.digiBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams, allresults)


def amerBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams, allresults=False):
    """Price of an American option in the Black-Scholes model using finite difference PDE.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    spot : double
        asset spot price
    discountcrv : str
        discount yield curve name
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double
        asset return volatility
    pdeparams : dictionary
        NTIMESTEPS : (int) number of time steps
        NSPOTNODES : (int) number of spot nodes
        NSTDDEVS : (double) number of standard deviations for the spot range
        THETA : (double) scheme implicitness
    allresults : bool
        False for price only; True for the full grid of results
    
    Returns
    -------
    dictionary
        Price : PDE price
        Times : 1D array with times
        Spots : 1D array with spots
        Values : 2D array with option values

    Notes
    -----
    The keys `Times`, `Spots` and `Values` are available only if `allresults`==True.
    """
    return pyqflib.amerBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams, allresults)
>>>>>>> origin/yuyang-branch
=======
import qflib.pyqflib

###################
# function group 0

def version(): 
    """qflib library version.

    Returns
    -------
    str
        version in the format Major.Minor.Revision
    """
    return pyqflib.version()


def sayHello(name): 
    """Says hello.

    Parameters
    ----------
    name : str
        caller name

    Returns
    -------
    str
        greeting
    """
    return pyqflib.sayHello(name)


def outerProd(vector1, vector2):
    """Computes the outer product of two numerical vectors.

    Parameters
    ----------
    vector1 : list(double) or 1D numpy array
        first vector
    vector2: list(double) or 1D numpy array
        second vector

    Returns
    -------
    2D numpy array
        outer product as matrix
    """
    return pyqflib.outerProd(vector1, vector2)


def polyProd(vector1, vector2):
    """Computes the product of two polynomials.

    Parameters
    ----------
    vector1 : list(double) or 1D numpy array
        coefficients of first vector, in decreasing order
    vector2: list(double) or 1D numpy array
        coefficients of second vector, in decreasing order

    Returns
    -------
    1D numpy array
        coeffcients of the polynomial product
    """
    return pyqflib.polyProd(vector1, vector2)


def erf(x):
    """Error function at `x`. 
    """
    return pyqflib.erf(x)


def invErf(x):
    """Inverse error function at `x`. 
    """
    return pyqflib.invErf(x)


def normalCdf(x):
    """Cumulative standard normal distribution at `x`. 
    """
    return pyqflib.normalCdf(x)


def normalInvCdf(x):
    """Inverse of the cumulative standard normal distribution at quantile `x`.
    """
    return pyqflib.normalInvCdf(x)


def echoMatrix(mat):
    """Echoes the input matrix.

    Parameters
    ----------
    mat : 2D numpy array
        input matrix

    Returns
    -------
    2D numpy array
        the input matrix `mat`
    """
    return pyqflib.echoMatrix(mat)


def cholDcmp(mat): 
    """Cholesky decomposition of the input matrix. 

    Parameters
    ----------
    mat : 2D numpy array
        input square matrix

    Returns
    -------
    2D numpy array
       lower triangular Cholesky factor
    """
    return pyqflib.cholDcmp(mat)


def eigenSym(mat): 
    """Eigenvalues and eigenvectors of a symmetric matrix. 

    Parameters
    ----------
    mat : 2D numpy array
        input symmetric matrix

    Returns
    -------
    dictionary
        Eigenvals :  1D numpy array
            the eigenvalues
        Eigenvecs : 2D numpy array
            the eigenvectors in column order
    """
    return pyqflib.eigenSym(mat)


def specTrunc(mat): 
    """Nearest positive definite matrix using spectral truncation. 

    Parameters
    ----------
    mat : 2D numpy array
        input symmetric matrix

    Returns
    -------
    2D numpy array
        the nearest to `mat` positive definite matrix
    """
    return pyqflib.specTrunc(mat)


def ppolyEval(bkpoints, values, polyorder, xvec, derivorder): 
    """Values and derivatives of a piecewise polynomial function at a set of points.

    Parameters
    ----------
    bkpoints : list(double) or 1D numpy array
        breakpoints of the piecewise polynomial function
    values : list(double) or 1D numpy array
        corresponding values at each breakpoint
    polyorder : {0, 1}
        polynomial order of the segments (constant or linear)
    xvec : list(double) or 1D numpy array
        points at which values or derivatives are evaluated
    derivorder : int (>= 0)
        if 0, values are computed, else derivatives of `derivorder` order  

    Returns
    -------
    1D numpy array
        values or derivatives at each point in `xvec`
    
    Notes
    -----
    1. If `polyorder`==0, the value at the left breakpoint is used for the segment.
    2. At points outside the breakpoint span constant extrapolation is used.
    """
    return pyqflib.ppolyEval(bkpoints, values, polyorder, xvec, derivorder)


def ppolyIntegral(bkpoints, values, polyorder, xstart, xvec): 
    """Integral of a piecewise polynomial function from `xstart` to each point in `xvec`.

    Parameters
    ----------
    bkpoints : list(double) or 1D numpy array
        breakpoints of the piecewise polynomial function
    values : list(double) or 1D numpy array
        corresponding values at each breakpoint
    polyorder : {0, 1}
        polynomial order of the segments (constant or linear)
    xstart : double
        starting point of each interval
    xvec : list(double) or 1D numpy array
        end points one for each interval

    Returns
    -------
    1D numpy array
        values of the integral
    
    Notes
    -----
    1. If `polyorder`==0, the value at the left breakpoint is used for the segment.
    2. At points outside the breakpoint span constant extrapolation is used.
    """
    return pyqflib.ppolyIntegral(bkpoints, values, polyorder, xstart, xvec)


def ppolySum(bkpoints1, values1, bkpoints2, values2, polyorder): 
    """Sum of two piecewise polynomial functions.

    Parameters
    ----------
    bkpoints1 : list(double) or 1D numpy array
        breakpoints of the first piecewise polynomial function
    values1 : list(double) or 1D numpy array
        corresponding values at each breakpoint of the first function
    bkpoints2 : list(double) or 1D numpy array
        breakpoints of the second piecewise polynomial function
    values2 : list(double) or 1D numpy array
        corresponding values at each breakpoint of the second function
    polyorder : {0, 1}
        polynomial order of the segments (constant or linear)

    Returns
    -------
    2D numpy array
        breakpoints and corresponding values of the sum
    
    """
    return pyqflib.ppolySum(bkpoints1, values1, bkpoints2, values2, polyorder)


def polyBracket(coeffs, lolim, uplim, nsubs): 
    """Bracketing the roots of a polynomial.

    Parameters
    ----------
    coeffs : list(double) or 1D numpy array
        polynomial coefficients in increasing order
    lolim : double
        lower limit of root search
    uplim : double
        upper limit of root search
    nsubs : int
        number of subdivisions of the (lolim, uplim) interval

    Returns
    -------
    2D numpy array
        n x 2 array, with n the number of detected roots. 
        Each row has the left and right boundary of a root bracketing interval.
    """
    return pyqflib.polyBracket(coeffs, lolim, uplim, nsubs)


def polySecant(coeffs, lolim, uplim, tol): 
    """Root search of a polynomial using the secant mathod.

    Parameters
    ----------
    coeffs : list(double) or 1D numpy array
        polynomial coefficients in increasing order
    lolim : double
        lower limit of root search
    uplim : double
        upper limit of root search
    tol : double
        search tolerance

    Returns
    -------
    double
        the root
    """
    return pyqflib.polySecant(coeffs, lolim, uplim, tol)


def toContCmpd(rate, annfreq): 
    """Continuously compounded from periodically compounded interest rate. 

    Parameters
    ----------
    rate : double
        periodically compounded rate
    annfreq : int (> 0)
        the annual compounding frequency

    Returns
    -------
    double
        equivalent continuously compounded rate
    """
    return pyqflib.toContCmpd(rate, annfreq)

def fromContCmpd(rate, annfreq): 
    """Periodically compounded from continuously compounded interest rate. 

    Parameters
    ----------
    rate : double
        continuously compounded rate
    annfreq : int (> 0)
        the annual comounding frequency

    Returns
    -------
    double
        equivalent periodically compounded rate
    """
    return pyqflib.fromContCmpd(rate, annfreq)


###################
# function group 1

def fwdPrice(spot, timetoexp, intrate, divyield):
    """Forward price of an asset.

    Parameters
    ----------
    spot : double
        asset spot price
    timetoexp : double
        time to expiration in years
    intrate : double
        interest rate, p.a. and c.c.
    divyield : double    
        asset dividend yield, p.a. and c.c.

    Returns
    -------
    double
        asset forward price
     """
    return pyqflib.fwdPrice(spot, timetoexp, intrate, divyield)


def qFwdPrice(spot, timetoexp, intrate, divyield, assetvol, fxvol, correl):
    """Quanto forward price of an asset. 

    Parameters
    ----------
    spot : double
        asset spot price in asset (foreign) currency
    timetoexp : double
        time to expiration in years
    intrate : double
        interest rate in the asset (foreign) market, p.a. and c.c.
    divyield : double    
        asset dividend yield, p.a. and c.c.
    assetvol : double
        asset return volatility, p.a.
    fxvol : double
        volatility of exchange rate between asset (foreign) and payoff (domestic) currency
    correl : double
        correlation between asset and FX returns, both in asset currency numeraire
    
    Returns
    -------
    double
        forward price of an asset quanto-ed into payoff (domestic) currency
    """
    return pyqflib.qFwdPrice(spot, timetoexp, intrate, divyield, assetvol, fxvol, correl)


def digiBS(payofftype, spot, strike, timetoexp, intrate, divyield, volatility):
    """Price and Greeks of a European digital option in the Black-Scholes model. 

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    spot : double
        asset spot price
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    intrate : double
        interest rate, p.a. and c.c.
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double
        asset return volatility

    Returns
    -------
    1D numpy array
        Array with Price, Delta, Gamma, Theta, Vega
    """
    return pyqflib.digiBS(payofftype, spot, strike, timetoexp, intrate, divyield, volatility)


def euroBS(payofftype, spot, strike, timetoexp, intrate, divyield, volatility):
    """Price and Greeks of a European option in the Black-Scholes model. 

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    spot : double
        asset spot price
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    intrate : double
        interest rate, p.a. and c.c.
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double
        asset return volatility

    Returns
    -------
    1D numpy array
        Array with Price, Delta, Gamma, Theta, Vega
    """
    return pyqflib.euroBS(payofftype, spot, strike, timetoexp, intrate, divyield, volatility)

def koFwd(spot, strike, kolevel, timetoexp, timetoko, intrate, divyield, volatility):
    """Price of a knockout forward contract in the Black-Scholes model. 

    Parameters
    ----------
    spot : double
        asset spot price
    strike : double
        strike price
    kolevel : double
        knockout level
    timetoexp : double
        time to expiration in years
    timetoko : double
        time to knockout
    intrate : double
        interest rate, p.a. and c.c.
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double
        asset return volatility

    Returns
    -------
    double
        price of the knockout forward
    """
    return pyqflib.koFwd(spot, strike, kolevel, timetoexp, timetoko, intrate, divyield, volatility)


###################
# function group 2

def mktList():
    """Names of all market objects.

    Returns
    -------
    dictionary
        YieldCurves : list with names of yield curves
        Volatilities : list with names of volatility term structures   
    """
    return pyqflib.mktList()


def mktClear():
    """Clears all market objects.

    Returns
    -------
    TRUE
    """
    return pyqflib.mktClear()


def ycCreate(ycname, tmats, vals, valtype):
    """Creates a new yield curve.

    Parameters
    ----------
    ycname : str
        new yield curve name
    tmats : list(double) or 1D numpy array
        maturities in years
    vals : list(double) or 1D numpy array
        zero bond prices or interest rates to each maturity in `tmats`
    valtype : {0, 1, 2}
        0: spot interest rates, 1: forward interest rates, 2: zero bond prices

    Returns
    -------
    str 
        name of the newly created yield curve

    Notes
    -----
    1. Yield curve names are case insensitive.
    2. A new yield curve replaces an existing one if they have the same name.
    """
    return pyqflib.ycCreate(ycname, tmats, vals, valtype)


def discount(ycname, tmat):
    """Discount factor from yield curve.

    Parameters
    ----------
    ycname : str
        name of the yield curve
    tmat : double
        time to maturity of the discount factor, in years

    Returns
    -------
    double
        discount factor
    """
    return pyqflib.discount(ycname, tmat)


def fwdDiscount(ycname, tmat1, tmat2):
    """Forward discount factor from yield curve.

    Parameters
    ----------
    ycname : str
        name of the yield curve
    tmat1 : double
        time to reset of the forward discount factor, in years
    tmat2 : double
        time to maturity of the forward discount factor, in years

    Returns
    -------
    double
        forward discount factor
    """
    return pyqflib.fwdDiscount(ycname, tmat1, tmat2)


def spotRate(ycname, tmat):
    """Spot interest rate from yield curve.

    Parameters
    ----------
    ycname : str
        name of the yield curve
    tmat : double
        time to maturity of the interest rate, in years

    Returns
    -------
    double
        spot interest rate
    """
    return pyqflib.spotRate(ycname, tmat)


def fwdRate(ycname, tmat1, tmat2):
    """Forward interest rate from yield curve.

    Parameters
    ----------
    ycname : str
        name of the yield curve
    tmat1 : double
        time to reset of the forward discount rate, in years
    tmat2 : double
        time to maturity of the forward discount rate, in years

    Returns
    -------
    double
        the forward discount rate
    """
    return pyqflib.fwdRate(ycname, tmat1, tmat2)


def volCreate(volname, tmats, vals, valtype):
    """Creates a new volatility term structure.

    Parameters
    ----------
    volname : str
        name of the volatility term structure
    tmats : list(double) or 1D numpy array
        maturities (expirations) in years
    vals : list(double) or 1D numpy array
        volatility values to each maturity in `tmats`
    valtype : {0, 1}
        0: spot volatilities, 1: forward volatilities

    Returns
    -------
    str 
        name of the newly created volatility term structure
    """
    return pyqflib.volCreate(volname, tmats, vals, valtype)


def spotVol(volname, tmat):
    """Spot volatility from term structure.

    Parameters
    ----------
    volname : str
        name of the volatility term structure
    tmat : double
        time to maturity (expiration) of the spot volatility, in years

    Returns
    -------
    double
        spot volatility
    """
    return pyqflib.spotVol(volname, tmat)


def fwdVol(volname, tmat1, tmat2):
    """Forward volatility from term structure.

    Parameters
    ----------
    volname : str
        name of the volatility term structure
    tmat1 : double
        time to reset of the forward volatility, in years
    tmat2 : double
        time to maturity (expiration) of the forward volatility, in years

    Returns
    -------
    double
        forward volatility
    """
    return pyqflib.fwdVol(volname, tmat1, tmat2)


###################
# function group 3

def euroBSMC(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, mcparams, npaths):
    """Price and standard error of a European option in the Black-Scholes model using Monte Carlo.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    spot : double
        asset spot price
    discountcrv : str
        discount yield curve name
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double or string
        asset return volatility or vol term structure name
    mcparams : dictionary
        URNGTYPE : 'MINSTDRAND', 'MT19937', 'RANLUX3', 'RANLUX4'
        PATHGENTYPE : 'EULER'
        CONTROLVARTYPE : 'ANTITHETIC', 'NONE'
    npaths : int
        number of Monte Carlo paths
    
    Returns
    -------
    dictionary
        Mean : Monte Carlo mean price
        StdErr : Monte Carlo standard error
    """
    return pyqflib.euroBSMC(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, mcparams, npaths)


def digiBSMC(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, mcparams, npaths):
    """Price and standard error of a digital option in the Black-Scholes model using Monte Carlo.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    spot : double
        asset spot price
    discountcrv : str
        discount yield curve name
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double or string
        asset return volatility or vol term structure name
    mcparams : dictionary
        URNGTYPE : 'MINSTDRAND', 'MT19937', 'RANLUX3', 'RANLUX4', 'SOBOL'
        PATHGENTYPE : 'EULER'
        CONTROLVARTYPE : 'ANTITHETIC', 'NONE'
    npaths : int
        number of Monte Carlo paths
    
    Returns
    -------
    dictionary
        Mean : Monte Carlo mean price
        StdErr : Monte Carlo standard error
    """
    return pyqflib.digiBSMC(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, mcparams, npaths)


def asianBasketBSMC(payofftype, strike, fixtimes, assetquantities, spots, discountcrv, divyields, 
                    volatilities, correlmat, mcparams, npaths):
    """Price and standard error of an Asian basket option in the Black-Scholes model using Monte Carlo.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    fixtimes : list(double) or 1D numpy array
        fixing times in years, unique and in increasing order
    assetquantities : list(double) or 1D numpy array
        asset quantities
    spots : list(double) or 1D numpy array
        asset spot prices
    discountcrv : str
        discount yield curve name
    divyields : list(double) or 1D numpy array
        asset dividend yields, p.a. and c.c.
    volatilities : list(double) or 1D numpy array
        asset return volatilities
    correlmat : 2D numpy array
        asset correlation matrix
    mcparams : dictionary
        URNGTYPE : 'MINSTDRAND', 'MT19937', 'RANLUX3', 'RANLUX4'
        PATHGENTYPE : 'EULER'
        CONTROLVARTYPE : 'ANTITHETIC', 'NONE'
    npaths : int
        number of Monte Carlo paths
    
    Returns
    -------
    dictionary
        Mean : Monte Carlo mean price
        StdErr : Monte Carlo standard error
    """
    return pyqflib.asianBasketBSMC(payofftype, strike, fixtimes, assetquantities, spots, discountcrv, divyields, 
                                   volatilities, correlmat, mcparams, npaths)


def worstofDigiBSMC(payofftype, strike, timetofix, timetoexp, spots, discountcrv, divyields, 
                    volatilities, correlmat, mcparams, npaths):
    """Price and standard error of a worst-of digital option in the Black-Scholes model using Monte Carlo.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    timetofix : double
        time to fix in years
    timetoexp : double
        time to expire in years
    spots : list(double) or 1D numpy array
        asset spot prices
    discountcrv : str
        discount yield curve name
    divyields : list(double) or 1D numpy array
        asset dividend yields, p.a. and c.c.
    volatilities : list(double) or 1D numpy array
        asset return volatilities
    correlmat : 2D numpy array
        asset correlation matrix
    mcparams : dictionary
        URNGTYPE : 'MINSTDRAND', 'MT19937', 'RANLUX3', 'RANLUX4'
        PATHGENTYPE : 'EULER'
        CONTROLVARTYPE : 'ANTITHETIC', 'NONE'
    npaths : int
        number of Monte Carlo paths
    
    Returns
    -------
    dictionary
        Mean : Monte Carlo mean price
        StdErr : Monte Carlo standard error
    """
    return pyqflib.worstofDigiBSMC(payofftype, strike, timetofix, timetoexp, spots, discountcrv, divyields, 
                                   volatilities, correlmat, mcparams, npaths)


###################
# function group 4

def euroBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams, allresults=False):
    """Price of a European option in the Black-Scholes model using finite difference PDE.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    spot : double
        asset spot price
    discountcrv : str
        discount yield curve name
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double
        asset return volatility
    pdeparams : dictionary
        NTIMESTEPS : (int) number of time steps
        NSPOTNODES : (int) number of spot nodes
        NSTDDEVS : (double) number of standard deviations for the spot range
        THETA : (double) scheme implicitness
    allresults : bool
        FALSE for price only; TRUE for the full grid of results
    
    Returns
    -------
    dictionary
        Price : PDE price
        Times : 1D array with times
        Spots : 1D array with spots
        Values : 2D array with option values

    Notes
    -----
    The keys `Times`, `Spots` and `Values` are available only if `allresults`==True.
    """
    return pyqflib.euroBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams, allresults)


def digiBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams, allresults=False):
    """Price of a digital option in the Black-Scholes model using finite difference PDE.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    spot : double
        asset spot price
    discountcrv : str
        discount yield curve name
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double
        asset return volatility
    pdeparams : dictionary
        NTIMESTEPS : (int) number of time steps
        NSPOTNODES : (int) number of spot nodes
        NSTDDEVS : (double) number of standard deviations for the spot range
        THETA : (double) scheme implicitness
    allresults : bool
        FALSE for price only; TRUE for the full grid of results
    
    Returns
    -------
    dictionary
        Price : PDE price
        Times : 1D array with times
        Spots : 1D array with spots
        Values : 2D array with option values

    Notes
    -----
    The keys `Times`, `Spots` and `Values` are available only if `allresults`==True.
    """
    return pyqflib.digiBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams, allresults)


def qEuroBSPDE(payofftype, strike, timetoexp, spot, discountcrv, growthcrv, divyield,
               volatility, fxvol, correl, pdeparams, allresults=False):
    """Price of a quanto European option in the Black-Scholes model using finite difference PDE.

    The asset is denominated in a local (foreign) currency, while the option payoff is paid
    in the domestic (payoff) currency. The drift used for evolving the asset in the domestic
    risk-neutral measure is (rf - q + rho * sigmaS * sigmaQ), where rf is read from the
    growth yield curve, and cash flows are discounted with the discount yield curve (rd).

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price (in payoff currency units per unit of asset)
    timetoexp : double
        time to expiration in years
    spot : double
        asset spot price
    discountcrv : str
        discount (domestic) yield curve name
    growthcrv : str
        growth (foreign / local) yield curve name
    divyield : double
        asset dividend yield, p.a. and c.c.
    volatility : double or string
        asset return volatility or volatility term structure name
    fxvol : double
        FX (payoff/local) volatility
    correl : double
        asset-FX correlation, in [-1, 1]
    pdeparams : dictionary
        NTIMESTEPS : (int) number of time steps
        NSPOTNODES : (int) number of spot nodes
        NSTDDEVS : (double) number of standard deviations for the spot range
        THETA : (double) scheme implicitness
    allresults : bool
        False for price only; True for the full grid of results

    Returns
    -------
    dictionary
        Price : PDE price
        Times : 1D array with times
        Spots : 1D array with spots
        Values : 2D array with option values

    Notes
    -----
    The keys `Times`, `Spots` and `Values` are available only if `allresults`==True.
    """
    return pyqflib.qEuroBSPDE(payofftype, strike, timetoexp, spot, discountcrv, growthcrv,
                              divyield, volatility, fxvol, correl, pdeparams, allresults)


def amerBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams, allresults=False):
    """Price of an American option in the Black-Scholes model using finite difference PDE.

    Parameters
    ----------
    payofftype : {1, -1}
        1 for call, -1 for put
    strike : double
        strike price
    timetoexp : double
        time to expiration in years
    spot : double
        asset spot price
    discountcrv : str
        discount yield curve name
    divyield : double    
        asset dividend yield, p.a. and c.c.
    volatility : double
        asset return volatility
    pdeparams : dictionary
        NTIMESTEPS : (int) number of time steps
        NSPOTNODES : (int) number of spot nodes
        NSTDDEVS : (double) number of standard deviations for the spot range
        THETA : (double) scheme implicitness
    allresults : bool
        False for price only; True for the full grid of results
    
    Returns
    -------
    dictionary
        Price : PDE price
        Times : 1D array with times
        Spots : 1D array with spots
        Values : 2D array with option values

    Notes
    -----
    The keys `Times`, `Spots` and `Values` are available only if `allresults`==True.
    """
    return pyqflib.amerBSPDE(payofftype, strike, timetoexp, spot, discountcrv, divyield, volatility, pdeparams, allresults)
>>>>>>> origin/fangyi-branch

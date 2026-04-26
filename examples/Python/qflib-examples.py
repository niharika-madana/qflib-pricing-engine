# qflib library examples

#%%
import qflib as qf
import numpy as np
import os

ver = qf.version()
print(f'qflib version: {ver}')
pid = os.getpid()
print(f'pid: {pid}')

# Greet
print('----------------')
name = "World"
print(qf.sayHello(name))

# Outer product
print('----------------')
x = [1, 2, 3]
y = [4, 5]
op = qf.outerProd(x, y)
print(f'x: {x}\ny: {y}')
print(f'outerProd:\n{op}')

# Matrix
print('----------------')
m = np.array([[1, 2, 3], [4, 5, 6]])
em = qf.echoMatrix(m)
print(f'orig matrix:\n{m}')
print(f'echo matrix:\n{em}')

#PPolyEval
print('----------------')
xbpt = np.arange(1, 6)
yval =  np.arange(-10, 15, 5)
pord = 1
xval = np.arange(0.5, 6.0, 0.5)
pval = qf.ppolyEval(xbpt, yval, pord, xval, 0)
pder = qf.ppolyEval(xbpt, yval, pord, xval, 1)
pint = qf.ppolyIntegral(xbpt, yval, pord, xval[0], xval)
print('Piecewise polynomial')
print(f'bkpts={xbpt}')
print(f'yvals={yval}')
print(f'pord={pord}')
print(f'xval={xval}')
print(f'pval={pval}')
print(f'pder={pder}')
print(f'pint={pint}')

#Root bracketing and secant method search
print('----------------')
pcoeffs = [0, 2, 1]
lolim = -4
uplim = 3
nsubs = 10

brkts = qf.polyBracket(pcoeffs, lolim, uplim, nsubs)
print(f"Roots of polynomial: {pcoeffs}")
print(f"Root brackets:\n {brkts}")

root = qf.polySecant(pcoeffs, brkts[0, 0], brkts[0, 1], 1e-12)
print(f"root: {root:.4f}")

#ToContCmpd, FromContComp
print('----------------')
anfreq = 1
inrate = 0.10
ccrate = qf.toContCmpd(inrate, anfreq)
outrate = qf.fromContCmpd(ccrate, anfreq)
print('To and from continuous compounding')
print(f'InRate={inrate:.4f}, CCRate={ccrate:.4f}, PerRate={outrate:.4f}')

#%%
# function group 1
print('================')
print('Analytic prices')

#fwdprice
fwdpx = qf.fwdPrice(spot = 100, timetoexp = 1.0, intrate = 0.04, divyield = 0.02)
print('Forward price analytic solution')
print(f'Price={fwdpx:.4f}')

digi = qf.digiBS(payofftype = 1, spot = 100, timetoexp = 1.0, strike = 100,
                 intrate = 0.04, divyield = 0.02, volatility = 0.4)[0]
print('Digital option using Black-Scholes analytic solution')
print(f'Price={digi:.4f}')

euro = qf.euroBS(payofftype = 1, spot = 100, timetoexp = 1.0, strike = 100,
                intrate = 0.04, divyield = 0.02, volatility = 0.4)[0]
print('European option using Black-Scholes analytic solution')
print(f'Price={euro:.4f}')

#%%
# function group 2
print('================')
print('Market objects')

#yccreate
yc = qf.ycCreate(ycname = 'USD', 
                 tmats =  [1/12,  1/4,  1/2,   3/4,    1,     2,    3,     4,    5,      10],
                 vals = [0.01,   0.02, 0.03, 0.035, 0.04, 0.045, 0.05, 0.055, 0.0575, 0.065],
                 valtype = 0)
print(f'Created yield curve: {yc}')

#discount, spotrate, fwdrate
df = qf.discount(ycname = yc, tmat = 2)
spotrate = qf.spotRate(ycname = yc, tmat = 2)
fwdrate = qf.fwdRate(ycname = yc, tmat1 = 1, tmat2 = 2)
print(f'DF={df:.4f}, SpotRate={spotrate:.4f} FwdRate={fwdrate:.4f}')

print('Market list')
print(qf.mktList())

#%%
# function group 3
print('=================')
print('European option using Black-Scholes Monte Carlo')

#eurobsmc
mcpars0 = {'URNGTYPE': 'MT19937', 'PATHGENTYPE': 'EULER'}
npaths0 = 200000
euromc0 = qf.euroBSMC(payofftype = 1, strike = 100, timetoexp = 1.0, spot = 100,
                       discountcrv =  yc, divyield = 0.02, volatility = 0.4,
                       mcparams = mcpars0, npaths = npaths0)
print(f'URNGTYPE={mcpars0["URNGTYPE"]} PATHGENTYPE={mcpars0["PATHGENTYPE"]} NPATHS={npaths0}')
print(f'Price={euromc0['Mean']:0.4f}  StdErr={euromc0['StdErr']:0.4f}')

print('=================')
print('Asian basket option using Black-Scholes Monte Carlo')

#asianbasketbsmc
fixtimes = [  0.5,   1.0,   1.5,    2.0]
assqts   = [  0.2,   0.2,   0.2,   0.2,   0.2]
spots    = [100.0, 100.0, 100.0, 100.0, 100.0]
divylds  = [ 0.02,  0.02,  0.02,  0.02,  0.02]
vols     = [ 0.30,  0.30,  0.30,  0.30,  0.30]
correls  = np.array([
     [1.0,  0.5,  0.7, 0.6, 0.6],
     [0.5,  1.0,  0.8, 0.7, 0.5],
     [0.7,  0.8,  1.0, 0.7, 0.5], 
     [0.6,  0.7,  0.7, 1.0, 0.6],
     [0.6,  0.5,  0.5, 0.6, 1.0]])

mcpars1 = {'URNGTYPE': 'MT19937', 'PATHGENTYPE': 'EULER'}
npaths1 = 200000
asianmc = qf.asianBasketBSMC(payofftype = 1, strike = 100, fixtimes = fixtimes, 
                             assetquantities = assqts, spots = spots,
                             discountcrv =  yc, divyields = divylds, 
                             volatilities= vols, correlmat = correls,
                             mcparams = mcpars1, npaths = npaths1)
print(f'URNGTYPE={mcpars1["URNGTYPE"]} PATHGENTYPE={mcpars1["PATHGENTYPE"]} NPATHS={npaths1}')
print(f'Price={asianmc['Mean']:0.4f}  StdErr={asianmc['StdErr']:0.4f}')

#%%
# function group 4
print('=================')
print('European option using Black-Scholes PDE')

ntimesteps = 50
nspotnodes = 50
nstdevs = 4

pdepars0 = {'NTIMESTEPS': ntimesteps, 'NSPOTNODES': nspotnodes, 'NSTDDEVS': 4, 'THETA': 0}

europde0 = qf.euroBSPDE(payofftype = 1, strike = 100, timetoexp = 1.0, spot = 100,
                        discountcrv =  yc, divyield = 0.02, volatility = 0.4, pdeparams = pdepars0)

print(f'NTIMESTEPS={pdepars0["NTIMESTEPS"]} NSPOTNODES={pdepars0["NSPOTNODES"]} NSTDDEVS={pdepars0["NSTDDEVS"]} THETA={pdepars0["THETA"]}')
print(f'Price={europde0["Price"]:0.4f}')

pdepars1 = {'NTIMESTEPS': ntimesteps, 'NSPOTNODES': nspotnodes, 'NSTDDEVS': 4, 'THETA': 1}

europde1 = qf.euroBSPDE(payofftype = 1, strike = 100, timetoexp = 1.0, spot = 100,
                         discountcrv =  yc, divyield = 0.02, volatility = 0.4, pdeparams = pdepars1)

print(f'NTIMESTEPS={pdepars1["NTIMESTEPS"]} NSPOTNODES={pdepars1["NSPOTNODES"]} NSTDDEVS={pdepars1["NSTDDEVS"]} THETA={pdepars1["THETA"]}')
print(f'Price={europde1["Price"]:0.4f}')

pdepars2 = {'NTIMESTEPS': ntimesteps, 'NSPOTNODES': nspotnodes, 'NSTDDEVS': 4, 'THETA': 0.5}

europde2 = qf.euroBSPDE(payofftype = 1, strike = 100, timetoexp = 1.0, spot = 100,
                         discountcrv =  yc, divyield = 0.02, volatility = 0.4, pdeparams = pdepars2)

print(f'NTIMESTEPS={pdepars2["NTIMESTEPS"]} NSPOTNODES={pdepars2["NSPOTNODES"]} NSTDDEVS={pdepars2["NSTDDEVS"]} THETA={pdepars2["THETA"]}')
print(f'Price={europde2["Price"]:0.4f}')

# exact price
eurobs = qf.euroBS(payofftype = 1, strike = 100, timetoexp = 1.0, spot = 100,
                   intrate = qf.spotRate(yc, 1.0), divyield = 0.02, volatility = 0.4)[0]

print(f'BSPrice={eurobs:0.4f}')

print('=================')
print('American option using Black-Scholes PDE')
pdeparams = {'NTIMESTEPS': 800, 'NSPOTNODES': 800, 'NSTDDEVS': 4, 'THETA': 0.5}
paytype = 1
opttype = 'call' if paytype == 1 else 'put'

amerpde = qf.amerBSPDE(payofftype = paytype, strike = 100, timetoexp = 1.0, spot = 100,
                        discountcrv =  yc, divyield = 0.02, volatility = 0.4, pdeparams = pdeparams)

print(f'NTIMESTEPS={pdeparams["NTIMESTEPS"]} NSPOTNODES={pdeparams["NSPOTNODES"]} NSTDDEVS={pdeparams["NSTDDEVS"]} THETA={pdeparams["THETA"]}\n')
print(f'American {opttype} option:')
print(f'Price={amerpde["Price"]:0.4f}')

# compare with corresponding European
europde = qf.euroBSPDE(payofftype = paytype, strike = 100, timetoexp = 1.0, spot = 100,
                        discountcrv =  yc, divyield = 0.02, volatility = 0.4, pdeparams = pdeparams)
print(f'European {opttype} option:')
print(f'Price={europde["Price"]:0.4f}')

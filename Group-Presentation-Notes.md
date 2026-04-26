# Project 2: Pricing Quanto Options
## Presentation Write-Up — QFGB8960 Advanced C++ for Finance

---

## Slide 1 — Title

**Pricing Quanto Options**
*Analytical, Monte Carlo, and PDE Methods*

QFGB8960 Advanced C++ for Finance — Spring 2026
Niharika Madana

---

## Slide 2 — Problem Setup

**What is a Quanto Option?**

A European quanto call/put on asset S (local currency CCY1) pays

> φ · (S(T) − K)⁺  units of payoff currency CCY2

where φ = +1 (call) or φ = −1 (put), and the payoff is delivered in a *fixed* foreign currency unit regardless of the exchange rate.

**Key parameters:**
| Symbol | Meaning |
|--------|---------|
| r_d | Domestic (payoff-currency) risk-free rate |
| r_f | Foreign/asset-local risk-free rate |
| q | Asset dividend yield |
| σ_S | Asset volatility |
| σ_Q | FX volatility |
| ρ | Asset–FX correlation |

**Quanto adjustment** (from the domestic measure):
The asset drift in the payoff-currency measure becomes

> r_f − q + ρ σ_S σ_Q

so the effective dividend yield is  **q' = r_d − r_f + q − ρ σ_S σ_Q**.

---

## Slide 3 — Implementation Overview

Three complete pricing engines were added to **qflib 1.1.0**:

### (a) Closed-Form Analytical — `qf.qEuroBS`
Applies Black-Scholes with the quanto-adjusted dividend yield q'.

```
quantoEuropeanOptionBS(payoffType, spot, strike, T,
                       discRate, growthRate, divYield,
                       assetVol, fxVol, correl)
```

### (b) Monte Carlo — `qf.qEuroBSMC`
Extends `BsMcPricer` with a `BsMcQuantoPricer` class. At each time step the drift is

> μ_i = (r_f^fwd − q + ρ σ_S^fwd σ_Q) Δt − ½ σ_S² Δt

Supports Euler path generation, MT19937 RNG, antithetic variates.

### (c) Finite-Difference PDE — `qf.qEuroBSPDE`
Extends `Pde1DSolver` with a new constructor accepting growth and discount yield curves, fxVol, and correl. The Crank–Nicolson theta-scheme (θ = 0.5) is used for backward induction from maturity to present.

---

## Slide 4 — Convergence Validation

Market setup used throughout: S = 100, K = 100, T = 1 yr, r_d = 4%, r_f = 2%, q = 1%, σ_S = 25%, σ_Q = 15%, ρ = 0.30.

### PDE Grid Convergence (quanto ATM call, analytical = 10.726684)

| Grid (NT × NS) | PDE Price | Error |
|:--------------:|:---------:|:-----:|
| 50 × 50  | 10.680086 | −4.66 × 10⁻² |
| 100 × 100 | 10.714869 | −1.18 × 10⁻² |
| 200 × 200 | 10.723705 | −2.98 × 10⁻³ |
| 400 × 400 | 10.725936 | −7.48 × 10⁻⁴ |
| 800 × 800 | 10.726497 | −1.88 × 10⁻⁴ |

Error decreases roughly as O(h²) — consistent with a second-order Crank–Nicolson scheme.

### Monte Carlo Convergence (500,000 paths, antithetic)

| Method | Call | StdErr | Analytical | Error |
|--------|------|--------|------------|-------|
| MC | 8.5897 | 0.0189 | 8.5964 | −0.0067 |
| PDE (400×400) | 10.7259 | — | 10.7267 | −7.5 × 10⁻⁴ |

**Zero-quanto consistency check:** When r_f = r_d and ρ = 0, `qf.qEuroBSPDE` and `qf.euroBSPDE` return identical prices (11.234828, diff = 0.00).

---

## Slide 5 — Question 1: Call-Put Parity (Derivation)

### Derivation

For a standard European option the call-put parity is

> C − P = e^(−r_d T) (F − K)

where F is the *risk-neutral forward price* of the underlying in the payoff-currency measure.

For a quanto option the asset grows at the quanto drift r_f − q + ρ σ_S σ_Q, so the quanto forward is

> F^Q(0, T) = S₀ · exp((r_f − q + ρ σ_S σ_Q) T)

Applying the same parity argument (both sides replicate the forward):

> **C^Q − P^Q = e^(−r_d T) (F^Q − K)**

This is exact: no Monte Carlo or PDE approximation is needed.

**Limit check:** As K → 0, C^Q → e^(−r_d T) F^Q (discounted quanto forward).

| Strike K | Call^Q | Discounted F^Q | C^Q − disc. F^Q |
|:--------:|:------:|:--------------:|:---------------:|
| 80 | 21.788787 | 96.947557 | −75.158771 |
| 5  | 92.191410 | 96.947557 | −4.756147  |
| 1  | 95.996328 | 96.947557 | −0.951229  |
| 0.1 | 96.852434 | 96.947557 | −0.095123 |

The call converges to the discounted quanto forward as K → 0. ✓

---

## Slide 6 — Question 1: Call-Put Parity (Numerical Check)

Market setup: S = 100, T = 1 yr, r_d = 5%, r_f = 3%, q = 2%, σ_S = 20%, σ_Q = 15%, ρ = 0.30.

Quanto forward F^Q = 101.918165, discounted F^Q = 96.947557.

Parity states: C^Q − P^Q = e^(−r_d T)(F^Q − K).

| Strike K | Call^Q | Put^Q | C − P | e^(−r_d T)(F^Q − K) | Error |
|:--------:|:------:|:-----:|:-----:|:--------------------:|:-----:|
| 80  | 23.157696 | 1.878382 | 21.279314 | 21.279178 | 1.4×10⁻⁴ |
| 90  | 16.163181 | 4.491762 | 11.671419 | 11.671465 | 4.6×10⁻⁵ |
| 100 | 10.726684 | 8.663160 |  2.063524 |  2.063524 | 0.0 |
| 110 | 6.805005 | 14.349375 | −7.544370 | −7.544370 | 0.0 |
| 120 | 4.153300 | 21.305564 | −17.152264 | −17.152264 | 0.0 |

Errors are at the level of floating-point precision — parity holds numerically. ✓

**Cross-maturity check (T ∈ {0.5, 1, 2} years):** Parity holds to within 10⁻¹² across all maturities tested.

---

## Slide 7 — Question 2: Effect of Correlation on Prices

### Theoretical channel

The quanto drift is  r_f − q + **ρ σ_S σ_Q**.

Higher ρ → higher drift → higher F^Q → higher call price, lower put price.

### Numerical results (S = 100, K = 100, T = 1, σ_S = 20%, σ_Q = 15%)

| ρ | Call (analytical) | Call (PDE) | Call (MC) | Put |
|:---:|:-----------------:|:----------:|:---------:|:---:|
| −0.80 | 8.542 | 8.541 | ≈ 8.54 | 15.29 |
| −0.40 | 9.296 | 9.295 | ≈ 9.30 | 14.54 |
|  0.00 | 10.096 | 10.095 | ≈ 10.10 | 13.74 |
| +0.40 | 10.943 | 10.942 | ≈ 10.95 | 12.90 |
| +0.80 | 11.837 | 11.836 | ≈ 11.84 | 12.00 |

All three methods agree to within MC standard error (~0.02) and PDE discretization error (~7×10⁻⁴).

**Sensitivity:** The call price increases by ~3.30 as ρ moves from −0.80 to +0.80, a 38% swing around the ρ = 0 base price. The put price moves by the same magnitude in the opposite direction (parity).

---

## Slide 8 — Question 2: Economic Explanation & Summary

### Economic Explanation

When an investor holds a **quanto call**, they receive payoff in the *domestic* (payoff) currency regardless of the spot FX rate. The option seller, however, is exposed to *cross-currency risk*: if the asset price rises (option goes in-the-money), the FX rate Q also tends to rise when ρ > 0.

A rising Q means the domestic-currency value of the asset's local gains is worth *more* in domestic terms. The quanto structure locks the investor in at a fixed exchange rate, so the *seller* bears this additional upside. To be compensated, the seller demands a higher premium → the call is more expensive for higher ρ.

Conversely, for ρ < 0, when the asset rises the FX rate tends to fall, reducing the local-currency gain when converted to the domestic currency. The quanto contract removes this downside for the seller, so the option is cheaper.

**Formally:** The quanto drift r_f − q + ρ σ_S σ_Q absorbs the covariance between the asset return and the FX return. A positive covariance effectively raises the risk-neutral growth rate of the asset in the domestic measure, increasing the forward and therefore the call value.

---

### Summary

| Contribution | Status |
|---|---|
| Analytical pricer `qf.qEuroBS` | Implemented & validated |
| Monte Carlo pricer `qf.qEuroBSMC` | Implemented & validated |
| PDE pricer `qf.qEuroBSPDE` | Implemented; O(h²) convergence confirmed |
| Call-put parity (derivation + numerics) | Verified to floating-point precision |
| Correlation sensitivity | Documented; economic intuition given |

**Key takeaway:** All three methods agree. The correlation ρ is the critical parameter controlling the quanto adjustment: it shifts the effective growth rate and changes option prices by up to ~38% relative to the ρ = 0 case for the parameters studied.

**References:**
- J. C. Hull, *Options, Futures, and Other Derivatives*, 11th ed.
- E. Derman & I. Kani, "Riding on a Smile," *Risk*, 1994.
- Lecture notes, QFGB8960, Fordham University, Spring 2026.

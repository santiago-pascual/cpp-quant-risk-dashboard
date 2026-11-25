# Statistical methodology

Let P_t be positive closing prices sorted by unique calendar date, n the number of returns, A the configured observations per year, f the effective annual risk-free rate and q = (1+f)^(1/A)-1. All rates are decimal fractions. Let r_t = P_t/P_(t-1)-1 and l_t = log(P_t)-log(P_(t-1)).

| Metric | Definition |
|---|---|
| Arithmetic mean | sum(r)/n |
| Mean log return | sum(l)/n |
| Geometric mean | exp(mean(l))-1 |
| Sample variance | sum((r-mean(r))²)/(n-1) |
| Volatility | square root of sample variance |
| Annual volatility | volatility × sqrt(A) |
| Annual arithmetic return | A × mean(r) |
| Annual geometric return | exp(A × mean(l))-1 |
| Calendar CAGR | exp(sum(l) × 365.2425 / elapsed calendar days)-1 |
| Sharpe | sqrt(A) × (mean(r)-q)/volatility |
| Downside deviation | sqrt(sum(min(0,r-q)²)/n), including all returns |
| Sortino | sqrt(A) × (mean(r)-q)/downside deviation |
| Drawdown | 1-P_t/max(P_0,...,P_t), positive loss magnitude |
| Maximum drawdown | maximum drawdown over all observations |
| Rolling volatility | trailing W returns, sample standard deviation × sqrt(A); no lookahead |
| Historical VaR | sorted losses L=-r, nearest-rank quantile at index ceil(confidence × n), one-based |
| Historical ES | average of largest (1-confidence) × n losses, fractional weight on boundary observation |

VaR and ES are single-observation loss measures; negative values are possible if all relevant returns are positive. ES integrates the empirical quantile function, rather than averaging all observations tied at VaR. No normality assumption. Small samples yield unstable tail estimates. Annualized volatility and ratios use conventional square-root scaling, which assumes sufficiently weak serial dependence and comparable observation intervals. Annual arithmetic return is not compounded. Calendar CAGR uses actual elapsed days, not trading session count.

Undefined values are N/A: no returns for return statistics, fewer than two returns for sample variance, zero denominator for risk ratios, incomplete rolling window. Nonfinite scalar results are also N/A. One observation has zero drawdown. Missing dates are not interpolated; no trading calendar validation or corporate-action adjustment is performed. Prices must be adjusted externally if total-return analysis is desired.

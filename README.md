# C++ Quantitative Returns & Volatility Dashboard

A lightweight quantitative finance analytics tool built from scratch in **C++17**, designed to analyze historical asset prices, calculate financial returns, and measure volatility without relying on external financial libraries.

**Project 02/30 — Quantitative Finance Programming Series**

## Overview

Financial returns are not as straightforward as they initially appear.

An asset can have a positive arithmetic average return while experiencing much lower compounded growth due to volatility.

This project explores the mathematical foundations of quantitative risk analysis by implementing financial statistics directly in C++.

Rather than relying on ready-made analytical libraries, the objective is to understand how each calculation works, from raw historical prices to annualized risk and return metrics.

## Features

### Implemented

- Historical price loading from CSV files
- Input validation and error handling
- Chronological ordering of historical observations
- Simple returns
- Logarithmic returns
- Arithmetic mean returns
- Sample variance
- Standard deviation
- Annualized arithmetic mean return
- Annualized volatility
- Compound Annual Growth Rate (CAGR)
- Terminal-based statistical output

### Planned Improvements

- Independent validation against Python (NumPy/Pandas)
- Additional CSV format support
- Sharpe and Sortino ratios
- Maximum drawdown analysis
- Rolling volatility
- Exportable analysis results
- Automated unit tests

## Mathematical Framework

### 1. Simple Returns

The percentage change in an asset's price between two consecutive observations.

\[
R_t = \frac{P_t-P_{t-1}}{P_{t-1}}
\]

### 2. Logarithmic Returns

Logarithmic returns are additive across consecutive time periods.

\[
r_t = \ln\left(\frac{P_t}{P_{t-1}}\right)
\]

### 3. Arithmetic Mean Return

\[
\bar R = \frac{1}{N}\sum_{t=1}^{N}R_t
\]

### 4. Sample Variance

\[
s^2 = \frac{1}{N-1}\sum_{t=1}^{N}(R_t-\bar R)^2
\]

### 5. Volatility

\[
\sigma = \sqrt{s^2}
\]

### 6. Annualized Volatility

\[
\sigma_{\text{annual}} = \sigma_{\text{daily}}\sqrt{252}
\]

This conventional scaling assumes sufficiently weak serial dependence in returns.

### 7. Annualized Arithmetic Return

\[
\mu_{\text{annual}} = 252\bar R
\]

This is an arithmetic annualization, not a compounded return forecast.

### 8. Compound Annual Growth Rate

\[
CAGR = \left(\frac{P_{\text{final}}}{P_{\text{initial}}}\right)^{252/N}-1
\]

Where \(N\) is the number of return periods.

## Volatility Drag and Compounding

Consider an investment starting at $100.

| Period | Return | Portfolio Value |
|---|---:|---:|
| Initial | — | $100 |
| 1 | +50% | $150 |
| 2 | −50% | $75 |

The arithmetic average return is 0%, but the total compounded return is −25%.

This illustrates why arithmetic returns and geometric growth are not interchangeable.

Under appropriate assumptions, the relationship between arithmetic and geometric growth can be approximated by:

\[
g \approx \mu-\frac{\sigma^2}{2}
\]

Higher volatility can reduce compounded growth relative to the arithmetic average.

The dashboard provides the basic statistics needed to investigate this relationship using historical data.

## Historical Data

The application loads historical asset prices from a user-specified CSV file.

The current parser expects a Nasdaq-style CSV containing:

- First column: Date
- Second column: Close/Last

For example:

```csv
Date,Close/Last,Volume,Open,High,Low
11/21/2026,$150.00,1000000,$148.00,$151.00,$147.00
11/20/2026,$148.00,900000,$146.00,$149.00,$145.00
11/19/2026,$146.00,850000,$144.00,$147.00,$143.00
```

The application assumes observations are ordered from newest to oldest and reverses them before calculating returns.

It also validates closing prices, rejecting invalid, non-finite, or non-positive values.

**Important:** The current implementation does not verify the actual dates or calculate elapsed calendar time. It assumes approximately 252 observations per trading year.

For dividend-paying assets, raw closing prices do not necessarily represent total investment returns. Adjusted or total-return data should be used when appropriate.

## Technologies

- C++17
- C++ Standard Library
- Git / GitHub
- CSV historical market data

No external C++ dependencies are required.

## Build and Run

### Requirements

A C++ compiler supporting C++17 or later.

### Compile

```bash
g++ -std=c++17 -O2 -Wall -Wextra "returns&volatility.cpp" -o dashboard
```

### Run on Windows (PowerShell)

```powershell
.\dashboard.exe
```

### Run on Linux/macOS

```bash
./dashboard
```

When prompted, enter the path to a compatible historical CSV file.

The program will calculate and display the financial statistics in the terminal.

## Project Structure

```text
cpp-quant-risk-dashboard/
├── returns&volatility.cpp
├── HistoricalData_1795299932817.csv
├── .gitignore
└── README.md
```

## Current Limitations

- Supports a specific Nasdaq-style CSV layout.
- Assumes reverse-chronological observations.
- Does not validate date ordering or missing trading sessions.
- Does not automatically adjust prices for dividends, splits, or corporate actions.
- Uses 252 periods per year for annualization.
- Assumes sufficiently weak serial correlation when annualizing volatility.
- Does not currently calculate drawdowns, portfolio correlations, or multi-asset risk.
- Has not yet been independently cross-validated against a separate statistical implementation.

The tool is intended for education and quantitative research, not investment recommendations.

## Project Roadmap

- [x] Implement simple and logarithmic returns
- [x] Implement mean, variance, and standard deviation
- [x] Implement annualized returns and volatility
- [x] Implement CAGR
- [x] Load historical prices from CSV
- [x] Implement basic input validation
- [ ] Cross-validate against NumPy/Pandas
- [ ] Implement Sharpe and Sortino ratios
- [ ] Add maximum drawdown calculations
- [ ] Implement rolling risk metrics
- [ ] Add automated testing
- [ ] Support additional historical data formats

## Why I Built This

I'm currently developing my quantitative finance and C++ programming skills through a series of 30 progressively more advanced projects.

The purpose isn't simply to reproduce calculations that existing libraries already perform.

It's to understand the mathematics, numerical assumptions, and implementation decisions behind the tools used in quantitative research.

This is the second project in that series.

Future projects will explore portfolio optimization, stochastic processes, statistical modeling, and systematic trading.

## Author

**Santiago Pascual**

Aspiring Quantitative Researcher | Quantitative Finance | C++ | Python

GitHub: https://github.com/santiago-pascual

## Disclaimer

This software is provided for educational and research purposes only. Historical statistics do not guarantee future performance.

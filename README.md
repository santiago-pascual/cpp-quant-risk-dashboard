# C++ Quantitative Returns & Volatility Dashboard

A lightweight quantitative finance analytics tool built from scratch in **C++**.

This project calculates statistical measures of financial returns and volatility, with a focus on understanding the mathematics behind quantitative finance and implementing the calculations directly in C++.

**Project 02/30 — Quantitative Finance Programming Series**

## Overview

The dashboard processes historical asset prices and calculates descriptive statistics and annualized performance metrics.

Rather than relying on external financial libraries, the core calculations are implemented using the C++ Standard Library.

## Features

### Implemented

- Simple returns
- Logarithmic returns
- Arithmetic mean returns
- Sample variance
- Standard deviation (volatility)
- Annualized arithmetic mean returns
- Annualized volatility
- Compound Annual Growth Rate (CAGR)
- Terminal-based statistical output

### In Development

- Historical market data loading from CSV files
- Input validation and error handling
- Cross-validation of results against Python (NumPy/Pandas)

## Mathematical Framework

**Simple Returns**

R(t) = (P(t) - P(t-1)) / P(t-1)

**Logarithmic Returns**

r(t) = ln(P(t) / P(t-1))

**Sample Variance**

s² = Σ(R(t) - μ)² / (N - 1)

**Volatility**

σ = √s²

**Annualized Volatility**

σ(annual) = σ(daily) × √252

**Annualized Arithmetic Mean Return**

μ(annual) = μ(daily) × 252

**Compound Annual Growth Rate**

CAGR = (P(final) / P(initial))^(252/N) - 1

Where N is the number of return periods. The annualization formulas assume daily observations and approximately 252 trading periods per year. Square-root-of-time volatility scaling also assumes negligible serial correlation.

## Technologies

- C++
- C++ Standard Library
- Git / GitHub

No external dependencies are required for the current version.

## Getting Started

### Requirements

- A C++ compiler supporting C++11 or later
- Git (optional)

### Compile

Using G++:

```bash
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o dashboard
```

### Run

On Windows:

```powershell
.\dashboard.exe
```

On Linux/macOS:

```bash
./dashboard
```

The current version uses a sample vector of historical prices defined in `main.cpp`.

## Project Structure

```text
cpp-quant-risk-dashboard/
├── main.cpp
├── .gitignore
└── README.md
```

## Limitations

- The current implementation uses hardcoded sample prices rather than downloaded market data.
- Annualized statistics are extrapolations and should not be interpreted as forecasts.
- The current dashboard does not model transaction costs, dividends, or corporate actions.
- The application is intended for educational and research purposes, not investment advice.

## Roadmap

- [x] Implement returns and volatility calculations
- [x] Implement annualization and CAGR
- [ ] Load historical prices from CSV
- [ ] Validate calculations against Python
- [ ] Improve error handling and documentation

## Purpose

This is the second project in a series of 30 progressively more advanced quantitative finance programming projects.

The objective is to develop practical skills in C++, numerical programming, financial mathematics, and reproducible quantitative research.

Future projects will explore more advanced topics in statistical modeling, portfolio risk, stochastic processes, and quantitative trading.

## Author

Santiago Pascual

Aspiring Quantitative Researcher | Quantitative Finance & C++

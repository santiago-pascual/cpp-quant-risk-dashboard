#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <limits>
#include <fstream>
#include <string>

using namespace std;

// Function declarations
vector<double> calculateReturns(const vector<double> &prices);
vector<double> calculateLogReturns(const vector<double> &prices);
double calculateMean(const vector<double> &returns);
double calculateVariance(const vector<double> &returns, double mean);
double calculateVolatility(const vector<double> &returns, double mean);
double annualizedVolatility(double volatility, int periodsPerYear);
double annualizedReturns(const vector<double> &returns, int periodsPerYear);
double returnsCAGR(const vector<double> &prices, int periodsPerYear);

int main()
{
    // Historical asset prices
    vector<double> prices = {
        100, 103, 101, 105, 108,
        110, 107, 111, 115, 120,
        118, 122, 125, 130, 128,
        132, 135, 138, 140, 145};

    cout << fixed << setprecision(4);

    cout << "===== RETURNS & VOLATILITY DASHBOARD =====\n\n";

    // 1. Calculate returns
    vector<double> returns = calculateReturns(prices);
    vector<double> log_returns = calculateLogReturns(prices);

    // 2. Display simple returns
    cout << "Simple Returns:\n";

    for (const auto &ret : returns)
    {
        cout << ret * 100 << "% ";
    }

    cout << "\n\n";

    // 3. Display logarithmic returns
    cout << "Log Returns:\n";

    for (const auto &log_ret : log_returns)
    {
        cout << log_ret * 100 << "% ";
    }

    cout << "\n\n";

    // 4. Calculate mean returns
    double mean = calculateMean(returns);
    double log_mean = calculateMean(log_returns);

    // 5. Calculate sample variance
    double variance = calculateVariance(returns, mean);

    // 6. Calculate volatility
    double volatility = calculateVolatility(returns, mean);

    // 7. Display statistics
    cout << "===== STATISTICS =====\n\n";

    cout << "Price Observations: " << prices.size() << endl;
    cout << "Return Observations: " << returns.size() << endl;

    cout << "Mean Simple Return: "
         << mean * 100 << "%" << endl;

    cout << "Mean Log Return: "
         << log_mean * 100 << "%" << endl;

    cout << "Sample Variance: "
         << setprecision(8) << variance << endl;

    cout << setprecision(4);

    cout << "Volatility: "
         << volatility * 100 << "%" << endl;

    double annualized_volatility = annualizedVolatility(volatility, 252);
    cout << "Annualized Volatility: "
         << annualized_volatility * 100 << "%" << endl;

    cout
        << "Annualized Returns: "
        << annualizedReturns(returns, 252) * 100 << "%" << endl;

    cout
        << "CAGR: "
        << returnsCAGR(prices, 252) * 100 << "%" << endl;

    return 0;
}

// Calculate simple returns
vector<double> calculateReturns(const vector<double> &prices)
{
    vector<double> returns;

    for (size_t i = 1; i < prices.size(); ++i)
    {
        double ret = (prices[i] - prices[i - 1]) / prices[i - 1];

        returns.push_back(ret);
    }

    return returns;
}

// Calculate logarithmic returns
vector<double> calculateLogReturns(const vector<double> &prices)
{
    vector<double> log_returns;

    for (size_t i = 1; i < prices.size(); ++i)
    {
        double log_ret = log(prices[i] / prices[i - 1]);

        log_returns.push_back(log_ret);
    }

    return log_returns;
}

// Calculate arithmetic mean
double calculateMean(const vector<double> &returns)
{
    if (returns.empty())
    {
        return numeric_limits<double>::quiet_NaN();
    }

    double sum = 0.0;

    for (const auto &ret : returns)
    {
        sum += ret;
    }

    return sum / returns.size();
}

// Calculate sample variance
double calculateVariance(const vector<double> &returns, double mean)
{
    if (returns.size() < 2)
    {
        return numeric_limits<double>::quiet_NaN();
    }

    double variance = 0.0;

    for (const auto &ret : returns)
    {
        variance += pow(ret - mean, 2);
    }

    return variance / (returns.size() - 1);
}

// Calculate standard deviation (volatility)
double calculateVolatility(const vector<double> &returns, double mean)
{
    double variance = calculateVariance(returns, mean);

    return sqrt(variance);
}

double annualizedVolatility(double volatility, int periodsPerYear)
{
    return volatility * sqrt(periodsPerYear);
}

double annualizedReturns(const vector<double> &returns, int periodsPerYear)
{
    double mean = calculateMean(returns);

    return mean * periodsPerYear;
}

double returnsCAGR(const vector<double> &prices, int periodsPerYear)
{
    if (prices.size() < 2 || periodsPerYear <= 0)
    {
        return numeric_limits<double>::quiet_NaN();
    }

    double initialPrice = prices.front();
    double finalPrice = prices.back();

    if (initialPrice <= 0 || finalPrice <= 0)
    {
        return numeric_limits<double>::quiet_NaN();
    }

    double periods = static_cast<double>(prices.size() - 1);

    double exponent = periodsPerYear / periods;

    return pow(finalPrice / initialPrice, exponent) - 1.0;
}

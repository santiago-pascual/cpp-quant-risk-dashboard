#pragma once
#include "risk/csv.hpp"
#include <map>
namespace risk {
struct Config { double periods=252, rf=0, confidence=.95; size_t window=20; };
struct Analysis { std::map<std::string,double> metrics; std::vector<double> returns, logs, drawdown, rolling; };
Analysis analyze(const std::vector<Observation>& a, const Config& c);
}

#pragma once
#include <string>
#include <vector>
namespace risk {
struct Observation { std::string date; int day; double price; };
std::vector<Observation> load_csv(const std::string& path);
}

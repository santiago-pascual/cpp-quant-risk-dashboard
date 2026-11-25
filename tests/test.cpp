#include "risk/analytics.hpp"
#include <cmath>
#include <fstream>
#include <stdexcept>
#include <cstdio>
static void check(bool b){if(!b)throw std::runtime_error("Test failed");}
static void near(double a,double b){check(std::abs(a-b)<1e-10);}
int main(){using namespace risk;Config c;c.window=2;c.confidence=.75;auto z=analyze({{"a",1,100},{"b",2,150},{"c",3,75}},c);near(z.returns[0],.5);near(z.returns[1],-.5);near(z.metrics.at("sample_variance"),.5);near(z.metrics.at("max_drawdown"),.5);near(z.metrics.at("es"),.5);near(z.metrics.at("var"),.5);near(z.rolling.back(),std::sqrt(126.));auto flat=analyze({{"a",1,100},{"b",2,100},{"c",3,100}},c);check(std::isnan(flat.metrics.at("sharpe")));check(std::isnan(flat.metrics.at("sortino")));check(std::isnan(analyze({{"a",1,100}},c).metrics.at("sample_variance")));auto csv=[](const char* s){std::ofstream f("test_input.csv");f<<s;f.close();return load_csv("test_input.csv");};auto a=csv("Date,Close\n2024-03-01,101\n02/29/2024,$100\n");check(a[0].price==100&&a[1].day-a[0].day==1);for(auto s:{"Bad,Close\n2024-01-01,1\n","Date,Close\n2023-02-29,1\n","Date,Close\n2024-01-01,0\n","Date,Close\n2024-01-01,nan\n","Date,Close\n2024-01-01,1\n01/01/2024,2\n","Date,Close\n2024-01-01,1,2\n"}){bool rejected=false;try{csv(s);}catch(const std::exception&){rejected=true;}check(rejected);}std::remove("test_input.csv");}

#include "risk/csv.hpp"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <regex>
#include <stdexcept>
namespace risk {
static std::string trim(std::string s) { auto a=s.find_first_not_of(" \t\r"); if(a==std::string::npos)return {}; return s.substr(a,s.find_last_not_of(" \t\r")-a+1); }
static std::vector<std::string> fields(const std::string& s) {
 std::vector<std::string> out; std::string v; bool quoted=false, closed=false;
 for(size_t i=0;i<s.size();++i){char c=s[i]; if(quoted){if(c=='"'){if(i+1<s.size()&&s[i+1]=='"'){v+='"';++i;}else{quoted=false;closed=true;}}else v+=c;}else if(c==','){out.push_back(trim(v));v.clear();closed=false;}else if(c=='"'&&v.empty()&&!closed)quoted=true;else if(c=='"'||(closed&&c!=' '&&c!='\r'&&c!='\t'))throw std::runtime_error("Malformed CSV quoting");else v+=c;}
 if(quoted)throw std::runtime_error("Unclosed quote");
 out.push_back(trim(v));return out;
}
static Observation parse(std::string d,std::string p){
 std::smatch m; int y,mo,da; static const std::regex iso(R"((\d{4})-(\d{2})-(\d{2}))"), us(R"((\d{1,2})/(\d{1,2})/(\d{4}))");
 if(std::regex_match(d,m,iso)){y=std::stoi(m[1]);mo=std::stoi(m[2]);da=std::stoi(m[3]);}else if(std::regex_match(d,m,us)){mo=std::stoi(m[1]);da=std::stoi(m[2]);y=std::stoi(m[3]);}else throw std::runtime_error("Invalid date format");
 auto leap=[](int n){return n%4==0&&(n%100!=0||n%400==0);}; int days[]={31,28,31,30,31,30,31,31,30,31,30,31}; days[1]+=leap(y);
 if(y<1||mo<1||mo>12||da<1||da>days[mo-1])throw std::runtime_error("Invalid calendar date");
 int prev=y-1;int serial=365*prev+prev/4-prev/100+prev/400+da;for(int i=0;i<mo-1;++i)serial+=days[i];
 if(!p.empty()&&p.front()=='$')p.erase(0,1);
 size_t n=0;double price=std::stod(p,&n);if(n!=p.size()||!std::isfinite(price)||price<=0)throw std::runtime_error("Invalid price");
 auto pad=[](int x){return (x<10?"0":"")+std::to_string(x);};return {std::string(4-std::to_string(y).size(),'0')+std::to_string(y)+"-"+pad(mo)+"-"+pad(da),serial,price};
}
std::vector<Observation> load_csv(const std::string& path){std::ifstream f(path);std::string line;if(!std::getline(f,line))throw std::runtime_error("Cannot read CSV header");if(line.compare(0,3,"\xef\xbb\xbf")==0)line.erase(0,3);auto h=fields(line);size_t d=h.size(),p=h.size();for(size_t i=0;i<h.size();++i){if(h[i]=="Date"){if(d!=h.size())throw std::runtime_error("Duplicate Date header");d=i;}if(h[i]=="Close"||h[i]=="Close/Last"){if(p!=h.size())throw std::runtime_error("Ambiguous close header");p=i;}}if(d==h.size()||p==h.size())throw std::runtime_error("Required headers: Date and Close or Close/Last");std::vector<Observation> a;size_t row=1;while(std::getline(f,line)){++row;try{auto v=fields(line);if(v.size()!=h.size())throw std::runtime_error("Wrong field count");a.push_back(parse(v[d],v[p]));}catch(const std::exception& e){throw std::runtime_error("Row "+std::to_string(row)+": "+e.what());}}if(f.bad()||a.empty())throw std::runtime_error("Missing observations or read error");std::sort(a.begin(),a.end(),[](auto& x,auto& y){return x.day<y.day;});for(size_t i=1;i<a.size();++i)if(a[i].day==a[i-1].day)throw std::runtime_error("Duplicate date: "+a[i].date);return a;}
}

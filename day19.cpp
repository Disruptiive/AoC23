#include <iostream>
#include <map>
#include <tuple>
#include <sstream>
#include <algorithm>


#include "helpers.hpp"

enum more_less{
    more_than,
    less_than,
};

enum symbols{
    x,
    m,
    a,
    s
};

class Condition{
    public:
        std::string name;
        std::vector<std::tuple<symbols,more_less,int,string>> conditions;
        std::string else_name;

        Condition(string n) : name(n), else_name() {};
        Condition() : name(), else_name() {};
};

struct Line{
    int x;
    int m;
    int a;
    int s;
};

size_t createMap(std::vector<string> lines,  std::map<string,Condition> &mp){
    for(int i = 0;i<lines.size();i++){
        if (lines[i].empty()){
            return i;
        }
        else{
            size_t start = lines[i].find('{');
            size_t end = lines[i].find('}');
            string cond = lines[i].substr(start+1,end-start-1);
            string name = lines[i].substr(0,start);
            std::vector<std::string> cond_vec = splitAtEvery(cond, ',');

            Condition c = Condition(name);
            std::vector<std::tuple<symbols,more_less,int,string>> conditions;
            for (int j=0;j<cond_vec.size()-1;j++){
                std::vector<std::string> split = splitAtEvery(cond_vec[j], ':');
                string before = split[0];
                string label = split[1];

                size_t bigger = before.find('>');
                size_t less = before.find('<');
                
                symbols symbol;
                int num;
                
                if(bigger !=std::string::npos){
                    char symb = before.substr(0,bigger).front();
                    switch(symb){
                        case 'a':
                            symbol = a;
                            break;
                        case 'x':
                            symbol = x;
                            break;
                        case 's':
                            symbol = s;
                            break;
                        case 'm':
                            symbol = m;
                            break;
                        default:
                            cout << "couldn't parse symbol" << endl;
                            break;
                    }
                    string n = before.substr(bigger+1);
                    num = stoi(n);
                    conditions.push_back({symbol,more_than,num,label});
                }
                else if(less !=std::string::npos){
                    char symb = before.substr(0,less).front();
                    switch(symb){
                        case 'a':
                            symbol = a;
                            break;
                        case 'x':
                            symbol = x;
                            break;
                        case 's':
                            symbol = s;
                            break;
                        case 'm':
                            symbol = m;
                            break;
                        default:
                            cout << "couldn't parse symbol" << endl;
                            break;
                    }
                    string n = before.substr(less+1);
                    num = stoi(n);
                    conditions.push_back({symbol,less_than,num,label});
                }
                else{
                    cout << "couldn't parse >/<" << endl;
                }
            }
            c.conditions = conditions;
            c.else_name = cond_vec.back();
            mp[name] = c;
        }
    }
    return 0;
}

int main(){
    std::vector<string> lines = fileSplitLines("day19.txt");
    std::vector<Line> ratings;
    std::map<string,Condition> mp;

    size_t idx = createMap(lines,mp);

    for(size_t i=idx+1;i<lines.size();i++){
        Line l;
        //lines[i].erase(std::remove_if(lines[i].begin(),lines[i].end(), [](char c) {return !isdigit(c);}),lines[i].end());
        std::replace_if(lines[i].begin(),lines[i].end(), [](char c) {return !isdigit(c);}, ' ');

        std::stringstream ss(lines[i]);

        ss >> l.x >> l.m >> l.a >> l.s;

        ratings.push_back(l);
    }

    cout << ratings.size() << endl;
    /*
    for(int k = 0;k<mp["ntv"].conditions.size();k++){
        cout << std::get<0>(mp["ntv"].conditions[k]) << " " << std::get<1>(mp["ntv"].conditions[k]) << " " << std::get<2>(mp["ntv"].conditions[k]) << " " << std::get<3>(mp["ntv"].conditions[k]) << "  " << k << endl;
    }
    */


    return 0;
}
#include <iostream>
#include <map>
#include <ostream>
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

struct Range{
    int x_min;
    int x_max;
    int m_min;
    int m_max;
    int a_min;
    int a_max;
    int s_min;
    int s_max;
    string label;
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

string processLabel(Line rating, Condition condition){
    string end_label;
    for(int i=0;i<condition.conditions.size();i++){
        auto c = condition.conditions[i];
        if(std::get<0>(c) == x){
            if(std::get<1>(c) == more_than){
                if (rating.x > std::get<2>(c)){
                    end_label = std::get<3>(c);
                    return end_label;
                }
            }

            else if(std::get<1>(c) == less_than){
                if (rating.x < std::get<2>(c)){
                    end_label = std::get<3>(c);
                    return end_label;
                }
            }
        }
        else if(std::get<0>(c) == m){
            if(std::get<1>(c) == more_than){
                if (rating.m > std::get<2>(c)){
                    end_label = std::get<3>(c);
                    return end_label;
                }
            }
            else if(std::get<1>(c) == less_than){
                if (rating.m < std::get<2>(c)){
                    end_label = std::get<3>(c);
                    return end_label;
                }
            }
        }
        else if(std::get<0>(c) == a){
            if(std::get<1>(c) == more_than){
                if (rating.a > std::get<2>(c)){
                    end_label = std::get<3>(c);
                    return end_label;
                }
            }
            else if(std::get<1>(c) == less_than){
                if (rating.a < std::get<2>(c)){
                    end_label = std::get<3>(c);
                    return end_label;
                }
            }
        }
        else if(std::get<0>(c) == s){
            if(std::get<1>(c) == more_than){
                if (rating.s > std::get<2>(c)){
                    end_label = std::get<3>(c);
                    return end_label;
                }
            }
            else if(std::get<1>(c) == less_than){
                if (rating.s < std::get<2>(c)){
                    end_label = std::get<3>(c);
                    return end_label;
                }
            }
        }
    }
    return condition.else_name;
}

int processRating(Line rating, std::map<string,Condition> mp){
    auto label_name = (string)"in";
    while (label_name != "A" && label_name != "R"){
        auto label = mp[label_name];
        label_name = processLabel(rating,label);
    }

    if (label_name == "A") {
        return rating.x+rating.m+rating.a+rating.s;
    }
    else if (label_name == "R") {
        return 0;
    }
    else{
        cout<<label_name<<endl;
        return 0;
    }
}

void processOneRange(std::vector<Range> &ranges, Range r,std::vector<Range> &accepted, std::vector<Range> &rejected,Condition condition){
    string end_label;
    for(int i=0;i<condition.conditions.size();i++){
        auto c = condition.conditions[i];
        // std::cout << "Label: " << std::get<3>(c) << " X: " << r.x_min << " - " << r.x_max << " M: " << r.m_min << " - " << r.m_max << " A: " << r.a_min << " - " << r.a_max << " S: " << r.s_min << " - " << r.s_max << std::endl;
        if(std::get<0>(c) == x){
            if(std::get<1>(c) == more_than){
                if(std::get<2>(c) > r.x_max){
                    continue;
                }
                else if(std::get<2>(c) < r.x_min){
                    if (std::get<3>(c)!="A" && std::get<3>(c) !="R"){
                        ranges.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,std::get<3>(c)});
                        return;
                    }
                    else if(std::get<3>(c)=="A"){
                        accepted.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"A"});
                        return;
                    }
                    else if(std::get<3>(c)=="R"){
                        rejected.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"R"});
                        return;
                    } 
                }
                else if(std::get<2>(c) > r.x_min && std::get<2>(c) < r.x_max){
                    if (std::get<3>(c)!="A" && std::get<3>(c) !="R"){
                        ranges.push_back({std::get<2>(c)+1,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,std::get<3>(c)});
                    }
                    else if(std::get<3>(c)=="A"){
                        accepted.push_back({std::get<2>(c)+1,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"A"});
                    }
                    else if(std::get<3>(c)=="R"){
                        rejected.push_back({std::get<2>(c)+1,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"R"});
                    } 
                    r.x_max = std::get<2>(c)+1;
                }
            }

            else if(std::get<1>(c) == less_than){
                if(std::get<2>(c) > r.x_max){
                    if (std::get<3>(c)!="A" && std::get<3>(c) !="R"){
                        ranges.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,std::get<3>(c)});
                        return;
                    }
                    else if(std::get<3>(c)=="A"){
                        accepted.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"A"});
                        return;
                    }
                    else if(std::get<3>(c)=="R"){
                        rejected.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"R"});
                        return;
                    } 
                }
                else if(std::get<2>(c) < r.x_min){
                    continue;
                }
                else if(std::get<2>(c) > r.x_min && std::get<2>(c) < r.x_max){
                    if (std::get<3>(c)!="A" && std::get<3>(c) !="R"){
                        ranges.push_back({r.x_min,std::get<2>(c),r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,std::get<3>(c)});
                    }
                    else if(std::get<3>(c)=="A"){
                        accepted.push_back({r.x_min,std::get<2>(c),r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"A"});
                    }
                    else if(std::get<3>(c)=="R"){
                        rejected.push_back({r.x_min,std::get<2>(c),r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"R"});
                    } 
                    r.x_min = std::get<2>(c);
                }
            }
        }
        else if(std::get<0>(c) == m){
            if(std::get<1>(c) == more_than){
                if(std::get<2>(c) > r.m_max){
                    continue;
                }
                else if(std::get<2>(c) < r.m_min){
                    if (std::get<3>(c)!="A" && std::get<3>(c) !="R"){
                        ranges.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,std::get<3>(c)});
                        return;
                    }
                    else if(std::get<3>(c)=="A"){
                        accepted.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"A"});
                        return;
                    }
                    else if(std::get<3>(c)=="R"){
                        rejected.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"R"});
                        return;
                    } 
                }
                else if(std::get<2>(c) > r.m_min && std::get<2>(c) < r.m_max){
                    if (std::get<3>(c)!="A" && std::get<3>(c) !="R"){
                        ranges.push_back({r.x_min,r.x_max,std::get<2>(c)+1,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,std::get<3>(c)});
                    }
                    else if(std::get<3>(c)=="A"){
                        accepted.push_back({r.x_min,r.x_max,std::get<2>(c)+1,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"A"});
                    }
                    else if(std::get<3>(c)=="R"){
                        rejected.push_back({r.x_min,r.x_max,std::get<2>(c)+1,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"R"});
                    } 
                    r.m_max = std::get<2>(c)+1;
                }
            }
            else if(std::get<1>(c) == less_than){
                if(std::get<2>(c) > r.m_max){
                    if (std::get<3>(c)!="A" && std::get<3>(c) !="R"){
                        ranges.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,std::get<3>(c)});
                        return;
                    }
                    else if(std::get<3>(c)=="A"){
                        accepted.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"A"});
                        return;
                    }
                    else if(std::get<3>(c)=="R"){
                        rejected.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"R"});
                        return;
                    } 
                }
                else if(std::get<2>(c) < r.m_min){
                    continue;
                }
                else if(std::get<2>(c) > r.m_min && std::get<2>(c) < r.m_max){
                    if (std::get<3>(c)!="A" && std::get<3>(c) !="R"){
                        ranges.push_back({r.x_min,r.x_max,r.m_min,std::get<2>(c),r.a_min,r.a_max,r.s_min,r.s_max,std::get<3>(c)});
                    }
                    else if(std::get<3>(c)=="A"){
                        accepted.push_back({r.x_min,r.x_max,r.m_min,std::get<2>(c),r.a_min,r.a_max,r.s_min,r.s_max,"A"});
                    }
                    else if(std::get<3>(c)=="R"){
                        rejected.push_back({r.x_min,r.x_max,r.m_min,std::get<2>(c),r.a_min,r.a_max,r.s_min,r.s_max,"R"});
                    }
                    r.m_min = std::get<2>(c); 
                }
            }
        }
        else if(std::get<0>(c) == a){
            if(std::get<1>(c) == more_than){
                if(std::get<2>(c) > r.a_max){
                    continue;
                }
                else if(std::get<2>(c) < r.a_min){
                    if (std::get<3>(c)!="A" && std::get<3>(c) !="R"){
                        ranges.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,std::get<3>(c)});
                        return;
                    }
                    else if(std::get<3>(c)=="A"){
                        accepted.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"A"});
                        return;
                    }
                    else if(std::get<3>(c)=="R"){
                        rejected.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"R"});
                        return;
                    } 
                }
                else if(std::get<2>(c) > r.a_min && std::get<2>(c) < r.a_max){
                    if (std::get<3>(c)!="A" && std::get<3>(c) !="R"){
                        ranges.push_back({r.x_min,r.x_max,r.m_min,r.m_max,std::get<2>(c)+1,r.a_max,r.s_min,r.s_max,std::get<3>(c)});
                    }
                    else if(std::get<3>(c)=="A"){
                        accepted.push_back({r.x_min,r.x_max,r.m_min,r.m_max,std::get<2>(c)+1,r.a_max,r.s_min,r.s_max,"A"});
                    }
                    else if(std::get<3>(c)=="R"){
                        rejected.push_back({r.x_min,r.x_max,r.m_min,r.m_max,std::get<2>(c)+1,r.a_max,r.s_min,r.s_max,"R"});
                    }
                    r.a_max = std::get<2>(c)+1; 
                }
            }
            else if(std::get<1>(c) == less_than){
                if(std::get<2>(c) > r.a_max){
                    if (std::get<3>(c)!="A" && std::get<3>(c) !="R"){
                        ranges.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,std::get<3>(c)});
                        return;
                    }
                    else if(std::get<3>(c)=="A"){
                        accepted.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"A"});
                        return;
                    }
                    else if(std::get<3>(c)=="R"){
                        rejected.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"R"});
                        return;
                    } 
                }
                else if(std::get<2>(c) < r.a_min){
                    continue;
                }
                else if(std::get<2>(c) > r.a_min && std::get<2>(c) < r.a_max){
                    if (std::get<3>(c)!="A" && std::get<3>(c) !="R"){
                        ranges.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,std::get<2>(c),r.s_min,r.s_max,std::get<3>(c)});
                    }
                    else if(std::get<3>(c)=="A"){
                        accepted.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,std::get<2>(c),r.s_min,r.s_max,"A"});
                    }
                    else if(std::get<3>(c)=="R"){
                        rejected.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,std::get<2>(c),r.s_min,r.s_max,"R"});
                    } 
                    r.a_min = std::get<2>(c);
                }
            }
        }
        else if(std::get<0>(c) == s){
            if(std::get<1>(c) == more_than){
                if(std::get<2>(c) > r.s_max){
                    continue;
                }
                else if(std::get<2>(c) < r.s_min){
                    if (std::get<3>(c)!="A" && std::get<3>(c) !="R"){
                        ranges.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,std::get<3>(c)});
                        return;
                    }
                    else if(std::get<3>(c)=="A"){
                        accepted.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"A"});
                        return;
                    }
                    else if(std::get<3>(c)=="R"){
                        rejected.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"R"});
                        return;
                    } 
                }
                else if(std::get<2>(c) > r.s_min && std::get<2>(c) < r.s_max){
                    if (std::get<3>(c)!="A" && std::get<3>(c) !="R"){
                        ranges.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,std::get<2>(c)+1,r.s_max,std::get<3>(c)});
                    }
                    else if(std::get<3>(c)=="A"){
                        accepted.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,std::get<2>(c)+1,r.s_max,"A"});
                    }
                    else if(std::get<3>(c)=="R"){
                        rejected.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,std::get<2>(c)+1,r.s_max,"R"});
                    } 
                    r.s_max = std::get<2>(c)+1;
                }
            }
            else if(std::get<1>(c) == less_than){
                if(std::get<2>(c) > r.s_max){
                    if (std::get<3>(c)!="A" && std::get<3>(c) !="R"){
                        ranges.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,std::get<3>(c)});
                        return;
                    }
                    else if(std::get<3>(c)=="A"){
                        accepted.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"A"});
                        return;
                    }
                    else if(std::get<3>(c)=="R"){
                        rejected.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"R"});
                        return;
                    } 
                }
                else if(std::get<2>(c) < r.s_min){
                    continue;
                }
                else if(std::get<2>(c) > r.s_min && std::get<2>(c) < r.s_max){
                    if (std::get<3>(c)!="A" && std::get<3>(c) !="R"){
                        ranges.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,std::get<2>(c),std::get<3>(c)});
                    }
                    else if(std::get<3>(c)=="A"){
                        accepted.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,std::get<2>(c),"A"});
                    }
                    else if(std::get<3>(c)=="R"){
                        rejected.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,std::get<2>(c),"R"});
                    } 
                    r.s_min = std::get<2>(c);
                }
            }
        }
    }

    if (condition.else_name != "A" && condition.else_name != "R"){
        ranges.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,condition.else_name});
    }
    else if(condition.else_name=="A"){
        accepted.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"A"});
    }
    else if(condition.else_name=="R"){
        rejected.push_back({r.x_min,r.x_max,r.m_min,r.m_max,r.a_min,r.a_max,r.s_min,r.s_max,"R"});
    } 
}

unsigned long long processRanges(std::vector<Range> &ranges, std::map<string,Condition> mp){
    std::vector<Range> accepted, rejected;
    while(ranges.size()>0){
        Range r = ranges.back();
        ranges.pop_back();
        processOneRange(ranges,r,accepted,rejected,mp[r.label]);
    }
    
    unsigned long long c = 0;
    for(int k=0;k<accepted.size();k++){
        c += (unsigned long long)(accepted[k].x_max - accepted[k].x_min)*(unsigned long long)(accepted[k].m_max - accepted[k].m_min)*(unsigned long long)(accepted[k].a_max - accepted[k].a_min)*(unsigned long long)(accepted[k].s_max - accepted[k].s_min);

    }
    return c;
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

    unsigned long long c=0;
    for(size_t i=0;i<ratings.size();i++){
        c += processRating(ratings[i],mp);
    } 

    cout << "Part 1:) " << c << endl;

    std::vector<Range> ranges;

    ranges.push_back({1,4001,1,4001,1,4001,1,4001,"in"});

    c = processRanges(ranges, mp);

    cout << "Part 2:) " << c << endl;

    /*
    cout << ratings.size() << endl;
    
    for(int k = 0;k<mp["ntv"].conditions.size();k++){
        cout << std::get<0>(mp["ntv"].conditions[k]) << " " << std::get<1>(mp["ntv"].conditions[k]) << " " << std::get<2>(mp["ntv"].conditions[k]) << " " << std::get<3>(mp["ntv"].conditions[k]) << "  " << k << endl;
    }
    */


    return 0;
}

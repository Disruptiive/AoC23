#include <iostream>
#include <map>

#include "helpers.hpp"

unsigned long long calculateHash(std::string str){
    unsigned long long h = 0;
    for (char c:str){
        h += c;
        h *= 17;
        h %= 256;
    }
    return h;
}

struct box_label{
    std::string label;
    int length;
};

void processEqual(map<int,std::vector<box_label>> &mp, box_label box){
    auto h = (int)calculateHash(box.label);
    if(mp[h].size()>0){
        std::vector<box_label>::iterator  it;
        bool found = false;
        for(auto it=mp[h].begin(); it!=mp[h].end(); it++){
            if ((*it).label == box.label){
                (*it).length = box.length;
                found = true;
                break;
            }
        }
        if(!found){
            mp[h].push_back(box);
        } 
    }
    else{
        mp[h].push_back(box);
    }


}

void processDash(map<int,std::vector<box_label>> &mp, std::string str){
    auto h = (int)calculateHash(str);
    if(mp[h].size()>0){
        std::vector<box_label>::iterator  it;
        int cnt = 0;
        for(auto it=mp[h].begin(); it!=mp[h].end(); it++){
            if ((*it).label == str){
                auto idx = mp[h].begin()+cnt;
                &mp[h].erase(idx);
                return;
            }
            cnt++;
        }
    }

}

int main(){
    std::vector<std::string> lines = fileSplitLines("day15.txt");
    std::vector<std::string> to_be_hashed = splitAtEvery(lines[0],',');
    unsigned long long sum = 0;

    for (int i=0;i<to_be_hashed.size();i++){
        sum += calculateHash(to_be_hashed[i]);
    }

    std::cout << "Part 1: " << sum << std::endl;

    map<int,std::vector<box_label>> mp;

    for(int i=0;i<256;i++){
        vector<box_label> bl;
        mp[i] = bl;
    }

    for (int i=0;i<to_be_hashed.size();i++){
        size_t eq_idx = to_be_hashed[i].find('=');
        if (to_be_hashed[i].find('=')!=std::string::npos){
            auto label = to_be_hashed[i].substr(0,eq_idx);
            auto num = std::stoi(to_be_hashed[i].substr(eq_idx+1));
            box_label box = {label,num};
            processEqual(mp,box);
        }
        else {
            size_t dash_idx = to_be_hashed[i].find('-');
            auto label = to_be_hashed[i].substr(0,dash_idx);
            processDash(mp,label);
        }
    }

    unsigned long long count = 0;
    for(int i=0;i<256;i++){
        for(int j=0;j<mp[i].size();j++){
            count += (i+1)*(j+1)*mp[i][j].length;
        }
    }

    std::cout << "Part 2: " << count << std::endl;

    return 0;
}
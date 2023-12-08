#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath> 
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include "helpers.hpp"


using namespace std;


template <typename T>
class Node{
    public:
        T data;
        Node *left;
        Node *right;

        Node(T value) : data(value),left(nullptr), right(nullptr){}

};


template <typename T>
Node<T>* findNode(Node<T>* root, T value){
    return root;
}



int main(){
    vector<string> lines = fileSplitLines("day8.txt");
    string directions = lines[0];
    stringstream ss(lines[2]);
    string root, l, r;
    ss >> root;
    ss.ignore(std::numeric_limits<std::streamsize>::max(), '(');
    ss >> l;
    l = l.substr(0,l.size()-1);
    ss >> r;
    r = r.substr(0,r.size()-1);
    
    return 0;
}
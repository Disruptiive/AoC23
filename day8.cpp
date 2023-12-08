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
    Node<T>* ptr;
    //cout << root->data << endl;
    if(root != nullptr)
    {
        if(value == root->data)
        {
            return root;
        }
        ptr = findNode(root->left,value);
        if (ptr != nullptr){
            return ptr;
        }
        else{
            return findNode(root->right, value);
        }
    }
    else
    {
        return nullptr;
    }
}



int main(){
    vector<string> lines = fileSplitLines("day8.txt");
    string directions = lines[0];
    stringstream init_ss(lines[2]);
    string root, l, r;
    init_ss >> root;
    Node<string>* rootNode = new Node<string>(root);
    cout << "root: " << root <<endl;
    for(size_t i = 2; i < lines.size();i++){
        string node;
        stringstream ss(lines[i]);
        ss >> node;
        ss.ignore(std::numeric_limits<std::streamsize>::max(), '(');
        ss >> l;
        l = l.substr(0,l.size()-1);
        ss >> r;
        r = r.substr(0,r.size()-1);

        Node<string>* found_node = findNode(rootNode,node);
        if (found_node == nullptr){
            cout << "tf" << endl;
        }
        else{
            cout << "found" <<endl;
            found_node->left = new Node<string>(l);
            found_node->right = new Node<string>(r);
        }
    }

   
    
    return 0;
}
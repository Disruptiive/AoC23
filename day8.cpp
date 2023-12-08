#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath> 
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <numeric>
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
    string node, l, r;
    Node<string>* parent_node, *left_node, *right_node;
    map<string, Node<string>*> mp;
    for(size_t i = 2; i < lines.size();i++){
        string node;
        stringstream ss(lines[i]);
        ss >> node;
        ss.ignore(std::numeric_limits<std::streamsize>::max(), '(');
        ss >> l;
        l = l.substr(0,l.size()-1);
        ss >> r;
        r = r.substr(0,r.size()-1);

        if(mp.count(node)>0){
            parent_node = mp[node];
        }
        else{
            parent_node = new Node<string>(node);
            mp[node] = parent_node;
        }

        if(mp.count(l)>0){
            left_node = mp[l];
        }
        else{
            left_node = new Node<string>(l);
            mp[l] = left_node;
        }

        if(mp.count(r)>0){
            right_node = mp[r];
        }
        else{
            right_node = new Node<string>(r);
            mp[r] = right_node;
        }

        parent_node->left = left_node;
        parent_node->right = right_node;

        //cout << node <<' ' << l << ' '<< r <<endl;
        /*
        Node<string>* found_node = findNode(rootNode,node);
        if (found_node == nullptr){
            cout << "tf" << endl;
        }
        else{
            cout << "found" <<endl;
            found_node->left = new Node<string>(l);
            found_node->right = new Node<string>(r);
        }
        */
    }
    unsigned long long steps = 0;
    auto curr_node = mp["AAA"];
    auto ending_node = mp["ZZZ"];
    bool found_solution = false;
    while(!found_solution){
        for (char c:directions){
            if (c=='R'){
                curr_node = curr_node->right;
            }
            else if(c=='L'){
                curr_node = curr_node->left;
            }
            steps++;
            if (curr_node == ending_node){
                cout << "1) Steps: " << steps << endl;
                found_solution = true;
            }
        }
    }

    vector<Node<string>*> a_nodes;

    for (auto const& x : mp){
        if (x.second->data.back() == 'A'){
            a_nodes.push_back(x.second);
        }
    }

    vector<unsigned long long> steps_array;

    for (size_t i = 0; i<a_nodes.size();i++){
        steps = 0;
        found_solution = false;
        curr_node = a_nodes[i];
        while(!found_solution){
            for (char c:directions){
                if (c=='R'){
                    curr_node = curr_node->right;
                }
                else if(c=='L'){
                    curr_node = curr_node->left;
                }
                steps++;
                if (curr_node->data.back()=='Z'){
                    steps_array.push_back(steps);
                    found_solution = true;
                }
            }
        }
    }

    auto lcm_so_far = lcm(steps_array[0],steps_array[1]);
    for (size_t i = 2; i<steps_array.size();i++){
        lcm_so_far = lcm(lcm_so_far,steps_array[i]);
    }
    cout << "2) Steps: " << lcm_so_far << endl;
    
    
    
    return 0;
}
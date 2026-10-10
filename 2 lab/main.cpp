#include "automat.h"
#include <iostream>
#include <vector>


int main(){
    NFA test("my.txt");
    DFA test1 = makeDFA(test);
    
    
    for(auto& [key, value] : test1.transitions){
        std::vector<char> v(key.first.begin(), key.first.end());
        std::vector<char> v1(value.begin(), value.end());

        std::cout << "(";
        for(size_t i = 0; i < v.size(); i++){
            std::cout << v[i] << ",";
        }
        std::cout << ')' << " " << key.second << " - " << "(";
        for(size_t i = 0; i < v1.size(); i++){
            std::cout << v1[i] << ",";
        }
        std::cout << ")" << '\n';
        
        
    }

    return 0;
}
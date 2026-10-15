#include "dfa.h"
#include <iostream>

int main(){
    dfa::DFA test("text");

    
    for(auto& [key, value] : test.transactions){
        std::cout << key.first << "," << key.second << " -> " << value << "\n";    
    }
    std::cout << "\n\n\n\n";
    dfa::destroyUnreachable(test);
    for(auto& [key, value] : test.transactions){
        std::cout << key.first << "," << key.second << " -> " << value << "\n";    
    }
    std::cout << "\n\n\n\n";

    for(auto& [key, value] : dfa::destroyEquivalent(test)){
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
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main(){
    std::vector<std::string> left_part, right_part;


    std::string left_temp, right_temp, line, separator;
    std::ifstream fin("grammr2.gr");

    while(std::getline(fin, line)){
        std::stringstream ss(line);

        ss >> left_temp >> separator;
        left_part.push_back(left_temp);
        while(ss >> right_temp >> separator){
            right_part.push_back(right_temp);
        }
        right_part.push_back(right_temp);
    }
    
    for(size_t i = 0; i < left_part.size(); i++){
        std::cout << left_part[i] << " -> ";
        for(size_t j = 0; j < right_part.size(); j++){
            std::cout << right_part[j] << " | ";
        }
        std::cout << "\n";
    }
    
    
    /*std::map<std::pair<char, char>, char> transaction;
    char junk, state1, symbol, state2;
    std::string line, separator;

    std::ifstream fin("text");
    while(std::getline(fin, line)){
        std::stringstream ss(line);
        ss >> junk >> state1 >> junk >> symbol >> junk;
        ss >> separator >> state2;
        transaction.insert({{state1, symbol}, state2});
    }

    fin.close();

    for(auto& [key, value] : transaction){
        std::cout << key.first << " " << key.second << " -> " << value;
    }

*/
    return 0;
}
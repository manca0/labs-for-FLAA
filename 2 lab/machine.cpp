#include "machine.h"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>

bool isCapital(char character){
    if(65 <= static_cast<int>(character) & static_cast<int>(character) <= 90) return true;
    else return false;
}

bool isSmall(char character){
    //97-122 its small in ascii
    if(static_cast<int>(character) == 0 || static_cast<int>(character)) return true;
    else return false;
}

bool includeCapital(std::string str){
    char current_char;
    std::stringstream ss(str);
    while(ss >> current_char){
        //65-90 its capitals in ascii
        if(65 <= static_cast<int>(current_char) & static_cast<int>(current_char) <= 90) return true;
    }
    return false;
}

bool includeEndSymbol(std::string str){
    char current_char;
    std::stringstream ss(str);
    while(ss >> current_char){
        //35 its # in ascii
        if(static_cast<int>(current_char) == 35) return true;
    }
    return false;
}

bool rightRule(std::string str){
    if(isSmall(str[0]) & isCapital(str[1])) return true;
    else return false;
}

bool leftRule(std::string str){
    if(isCapital(str[0]) & isSmall(str[1])) return true;
    else return false;
}

bool isTerminal(std::string str){
    if((str.length() == 1) & isSmall(str[0])) return true;
    else return false;
}

bool isEndSymbol(std::string str){
    if((str.length() == 1) & includeEndSymbol(str)) return true;
    else return false;
}

machine::machine(std::string filename) : file_name(filename), grammatic_type(0), start_symbol("S"), end_symbol("#"){
    std::string temp;
    std::ifstream fin(filename);
    std::getline(fin, temp, '\n');
    std::getline(fin, temp, '\n');
    std::getline(fin, temp, '\n');
    while(!fin.eof()){fin >> (*this);}
    fin.close();
    determineType();
}

bool machine::determineType1(){
    bool main_condition = false;
    for(size_t i = 0; i < left_part.size(); i++){
        if(left_part[i].length() <= right_part[i].length()) main_condition = true;
        else {main_condition = false; break;}
    }

    return main_condition;   
}

bool machine::determineType2(){
    int ter_counter = 0;
    for(size_t i = 0; i < left_part.size(); i++){
        if((left_part[i].length() == 1) & includeCapital(left_part[i])){
            ter_counter++;
        }
    }
    if(ter_counter == left_part.size()) return true;
    return false;
}

bool machine::determineType3(){
    int ter_counter = 0;
    bool first_condition = false;
    bool second_condition = false;
    
    for(size_t i = 0; i < left_part.size(); i++){
        if((left_part[i].length() == 1) & includeCapital(left_part[i])) ter_counter++;
    }
    if(ter_counter == left_part.size()) first_condition = true;

    for(size_t i = 0; i < right_part.size(); i++){
        if(isTerminal(right_part[i]) | (rightRule(right_part[i]) | leftRule(right_part[i])) | 
        isEndSymbol(right_part[i])) second_condition = true;
        else {second_condition = false; break;}
    }
    
    if(first_condition & second_condition) return true;
    else return false;
}

int machine::determineType(){
    bool type1 = determineType1();
    bool type2 = determineType2();
    bool type3 = determineType3();


    if(type2 & type3 & type1) {grammatic_type = 3; return 1;}
    if(type2 & !type3 & type1) {grammatic_type = 2; return 1;}
    if(type1) {grammatic_type = 1; return 1;}
    if(!type1 & !type2 & !type3) {grammatic_type = 0; return 1;}

    else return 0;
}

std::string machine::getGrammaticType(){
    switch(grammatic_type){
        case 0:
            return "тип 0: пустой тип";
            break;
        case 1:
            return "тип 1: контекстно-зависимый тип";
            break;        
        case 2:
            return "тип 2: контекстно-свободный тип";
            break;
        case 3:
            return "тип 3: регулярный тип";
            break;
        default:
            return "invalid syntax";
    }
}

int machine::getGrammatic(){return grammatic_type;}

std::ifstream& operator >>(std::ifstream& fin, machine& object){
    std::string left_temp, right_temp, line;
    char separator;

    std::getline(fin, left_temp, '-');
    fin >> separator;
    std::getline(fin, right_temp, '\n');

    object.left_part.push_back(left_temp);
    object.right_part.push_back(right_temp);

    return fin;
}
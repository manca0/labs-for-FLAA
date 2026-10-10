#ifndef AUTOMAT_H
#define AUTOMAT_H

#include "machine.h"
#include <set>
#include <map>
#include <utility>
#include <fstream>
#include <string>
#include <sstream>
#include <functional>
#include <stdexcept>
#include <iostream>

struct NFA{
    std::set<char> states;
    std::set<char> characters;
    std::set<char> start_state, finish_state;
    std::multimap<std::pair<char, char>, std::set<char>, std::greater<std::pair<char, char>>> rules;

    std::string filename;

    NFA(std::string u_filename) : filename(u_filename){
        try{
            machine grammar(filename);
            if(grammar.getGrammatic() != 3) throw std::runtime_error("invalid type of grammatic!");
            
            std::ifstream fin(filename);
            
            char separator = ' ', character;
            std::string line, left;
            
            // считывание первой строки, то есть нетерминальных символов
            if(std::getline(fin, line, '\n')){
                std::stringstream ss(line);
                while(ss >> character){
                    states.insert(character);
                }
                finish_state.insert('N');
            }

            separator = ' ';

            //считывание второй строки, то есть терминальных символов
            if(std::getline(fin, line, '\n')){
                std::stringstream ss(line);
                while(ss >> character){
                    characters.insert(character);
                }
            }

            //прочитали начальное состояние
            std::getline(fin, line, '\n');
            start_state.insert(line[0]);

            //считали правила в переходы нка
            while(std::getline(fin, line, '\n')){
                std::stringstream ss(line);
                ss >> character >> separator >> separator >> left;
                std::pair<char, char> transition = std::make_pair(character, left[0]);
                std::set<char> trans;
                trans.insert(left[1]);
                if(left.length() == 1){
                    rules.insert({transition, finish_state});
                } else{ 
                rules.insert({transition, trans});
                }
            }


            fin.close();
        } catch(const std::runtime_error& e){
            std::cout << e.what() << std::endl;
        }
    };
};


struct DFA{
    std::set<std::set<char>> states;
    std::set<char> characters;
    std::multimap<std::pair<std::set<char>, char>, std::set<char>, std::greater<std::pair<std::set<char>, char>>> transitions;
    std::set<char> start_state, finish_state;


    DFA(std::set<char> u_char, std::set<char> u_start_state) : characters(u_char), start_state(u_start_state){};
};


DFA makeDFA(NFA &nfa);




#endif //AUTOMAT_H
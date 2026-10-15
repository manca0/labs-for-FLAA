#include "dfa.h"
#include <fstream>
#include <iterator>
#include <sstream>
#include <queue>
#include <algorithm>
#include <utility>


std::set<char> whereIn(std::set<std::set<char>>& s, char c){
    for(const auto& c1 : s){
        if(c1.count(c)){
            return c1;
        }
    }
    return {};
}


namespace dfa{
    DFA::DFA(std::string filename){
        std::ifstream fin(filename);
        while(fin >> (*this)){}

        fin.close();
    }


    void destroyUnreachable(DFA &object){
        std::set<char> reachable_states = {'S'};
        std::set<char> unreachable_states, visited = {};
        std::queue<char> q;

        q.push('S');
        while(!q.empty()){
            if(visited.count(q.front())){q.pop(); continue;}

            for(auto& [key, value] : object.transactions){
                if(key.first == q.front()){
                    reachable_states.insert(value);
                    q.push(value);
                }
            }

            visited.insert(q.front());

            q.pop();
        }

        //здесь у нас происходит создание множества С которое явлется множеством А\В, то есть А без В
        std::set_difference(object.states.begin(), object.states.end(), reachable_states.begin(), reachable_states.end(),
    std::inserter(unreachable_states, unreachable_states.begin()));

        for(auto it = object.transactions.begin(); it != object.transactions.end();){
            for(char c : unreachable_states){
                if(it->first.first == c){
                    it = object.transactions.erase(it);
                } else{
                    ++it;
                }
            }
        }


    }
    std::map<std::pair<std::set<char>, char>, std::set<char>> destroyEquivalent(DFA &object){
        std::set<std::set<char>> fragmentations;
        std::set<char> fragmentation;
        int count = 0, states = 0;

        fragmentations.insert({'S'});
        fragmentations.insert({'G'});

        for(auto it = object.transactions.begin(); it != object.transactions.end(); ++it){
            for(auto next = object.transactions.begin(); next != object.transactions.end(); ++next){
                if(next == it) continue;
                if((it->first.second == next->first.second) && (it->first.first != next->first.first) && (it->second == next->second)){
                    fragmentation.insert(it->first.first);
                    fragmentation.insert(next->first.first);
                    fragmentations.insert(fragmentation);
                    break;
                }
                if(it->first.second != next->first.second) count++;
                if(it->first.first != next->first.first) states++;
                else continue;
            }

            if(states == object.transactions.size()-1){
                fragmentation.clear();
                fragmentation.insert(it->first.first);
                fragmentations.insert(fragmentation);
            }

            if(count == object.transactions.size()-1){
                fragmentation.clear();
                fragmentation.insert(it->first.first);
                fragmentations.insert(fragmentation);
            }
            
            states = 0;
            count = 0;
            fragmentation.clear();
        }

        std::map<std::pair<std::set<char>, char>, std::set<char>> new_transactions;


        for(const auto& element : fragmentations){
            for(auto term = object.terminals.begin(); term != object.terminals.end(); ++term){
                for(auto& [key, value] : object.transactions){
                    if(element.count(key.first)){// && (term == object.terminals.find(key.second))
                        new_transactions.insert({{element, key.second}, whereIn(fragmentations, value)});
                    }
                }
            }

        }

        
        return new_transactions;
    
    }

    std::ifstream& operator >>(std::ifstream& fin, DFA& object){
        char brace, symbol, state1, state2, junk;
        std::string separator, line;

        std::getline(fin, line);
        std::stringstream ss(line);
        ss >> brace >> state1 >> junk >> symbol >> brace >> separator >> state2;
        object.transactions.insert({{state1, symbol}, state2});
        object.states.insert(state1);
        object.states.insert(state2);
        object.terminals.insert(symbol);

        return fin;
    }
}
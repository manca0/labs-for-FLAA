#ifndef DFA_H
#define DFA_H

#include <map>
#include <functional>
#include <fstream>
#include <set>
#include <utility>
#include <string>

namespace dfa{
    struct DFA{
        std::multimap<std::pair<char, char>, char> transactions;
        std::set<char> states, terminals;

        DFA(std::string filename);
    };

    void destroyUnreachable(DFA& object);
    std::map<std::pair<std::set<char>, char>, std::set<char>> destroyEquivalent(DFA& object);

    std::ifstream& operator >>(std::ifstream& fin, DFA& object);

}



#endif // DFA_H
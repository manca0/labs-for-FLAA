#include "automat.h"
#include <queue>


DFA makeDFA(NFA &nfa){
    DFA dfa(nfa.characters, nfa.start_state);
    std::queue<std::set<char>> queue;
    dfa.finish_state = nfa.finish_state;
    dfa.states.insert(dfa.start_state);
    
    queue.push(dfa.start_state);
    std::set<std::set<char>> visited = {};

    while(!queue.empty()){
        if((queue.front().size() == 1) && queue.front().count(*dfa.finish_state.begin())) {queue.pop(); continue;}
        if(queue.front().size() == 0) {queue.pop(); continue;}
        if(visited.count(queue.front())) {queue.pop(); continue;}
        std::set<char> new_state = {};

        char symbol = '1';
        for(auto& [key, value] : nfa.rules){
            if(queue.front().count(key.first) && symbol == key.second){
                new_state.insert(*value.begin());
            }
        }
        dfa.transitions.insert({std::make_pair(queue.front(), symbol), new_state});
        dfa.states.insert(new_state);
        queue.push(new_state);
        new_state.clear();

        symbol = '0';
        for(auto& [key, value] : nfa.rules){
            if(queue.front().count(key.first) && symbol == key.second){
                new_state.insert(*value.begin());
            }
        }
        dfa.transitions.insert({std::make_pair(queue.front(), symbol), new_state});
        dfa.states.insert(new_state);
        queue.push(new_state);
        new_state.clear();

        visited.insert(queue.front());

        queue.pop();
    }

    return dfa;

}
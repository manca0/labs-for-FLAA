#include "machine.h"
#include <iostream>


int main(){
    machine mahc("grammr3.gr");

    std::cout << mahc.getGrammaticType() << "\n";


    return 0;
}
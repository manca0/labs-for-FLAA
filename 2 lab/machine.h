#ifndef MACHINE_H
#define MACHINE_H

#include <string>
#include <vector>
#include <fstream>

class machine{
public:
    machine(std::string filename);
    ~machine() = default;

    std::string getGrammaticType();
    int getGrammatic();

    int determineType();

    bool determineType2();
    bool determineType1();
    bool determineType3();

    friend std::ifstream& operator >>(std::ifstream& fin, machine& object);

private:
    std::vector<std::string> right_part;
    std::vector<std::string> left_part;
    std::string file_name;
    int grammatic_type;
    std::string start_symbol, end_symbol;
};

std::ifstream& operator >>(std::ifstream& fin, machine& object); 

#endif
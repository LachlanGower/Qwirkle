#ifndef ASSIGN2_SF_H
#define ASSIGN2_SF_H

#include <vector>
#include <string>

class SharedFunction{
public:

    //Splits the given string based on the delimiter given into a vector
    static std::vector<std::string> split(std::string stringToSplit, char delim);

};
#endif

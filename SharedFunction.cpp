#include "SharedFunction.h"

std::vector<std::string> SharedFunction::split(std::string stringToSplit, char delim){
    int startSearchLocation = 0;
    std::vector<std::string> stringSplit;

    bool cont = true;
    while (cont){
        unsigned int spaceLocation = stringToSplit.find(delim, startSearchLocation);
        if(stringToSplit.find(delim, startSearchLocation) == std::string::npos){
            cont = false;
            std::string word = stringToSplit.substr(startSearchLocation, stringToSplit.length() - spaceLocation);
            stringSplit.push_back(word);
        }
        else
        {
            unsigned int diff = spaceLocation - startSearchLocation;
            std::string word = stringToSplit.substr(startSearchLocation, diff);
            stringSplit.push_back(word);
            startSearchLocation = spaceLocation+1;
        }
    }
    return stringSplit;
}

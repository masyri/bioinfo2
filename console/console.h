#ifndef BIOINFO2_CONSOLE_H
#define BIOINFO2_CONSOLE_H

#include <string>
#include <vector>
#include <iostream>
#include "../Ramachandran.h"

/**
 * Contains output strings for console
 * */
class console {
public:

 static void ShowHeader();
 static char ShowChoices(std::string filename,std::string proteinname);
 static void Help(std::string name,std::string message);
 static void ShowAngles(std::string outputfile, std::vector<AnglePair> AP);


};

#endif //BIOINFO2_CONSOLE_H

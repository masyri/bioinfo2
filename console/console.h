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
 static char ShowChoices(std::string filename,std::string proteinname,std::string rpath );
 static void Help(std::string name,std::string message);
 static void ShowAngles(std::string outputfile, std::vector<AnglePair> AP);
 static void pressY2continue();


};

#endif //BIOINFO2_CONSOLE_H


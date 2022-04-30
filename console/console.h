#ifndef BIOINFO2_CONSOLE_H
#define BIOINFO2_CONSOLE_H

#include <string>
#include <iostream>

/**
 * Contains output strings for console
 * */
class console {
public:

 static void ShowHeader(std::string filename, std::string protein);
 static void Help(std::string name,std::string message);
 static void ShowAngles(std::string outputfile, std::vector<AnglePair> AP);


};

#endif //BIOINFO2_CONSOLE_H

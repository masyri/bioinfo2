#ifndef BIOINFO2_CONSOLE_H
#define BIOINFO2_CONSOLE_H

#include <string>
#include <iostream>

/**
 * Contains output strings for console
 * */
class console {
public:

 static void ShowHeader(std::string name);
 static void Help(std::string name,std::string message);
 static void ShowInputs(std::string file);


};

#endif //BIOINFO2_CONSOLE_H

#ifndef BIOINFO2_CONSOLE_H
#define BIOINFO2_CONSOLE_H

#include <string>
#include <iostream>

/**
 * Contains output strings for console
 * */
class console {
public:

 static void ShowHeader();
 static void Help(std::string message);
 static void ShowInputs(std::string file, int atoms, int NH, int CO, int hbonds);

};

#endif //BIOINFO2_CONSOLE_H

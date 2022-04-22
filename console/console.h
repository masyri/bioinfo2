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
 static void ShowInputs(std::string file_in, std::string file_out, int atoms, int NH, int CO, int hbonds_all, int hbonds_after_removing);

};

#endif //BIOINFO2_CONSOLE_H

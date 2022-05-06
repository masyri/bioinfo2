#ifndef BIOINFO2_CONSOLE_H
#define BIOINFO2_CONSOLE_H

#include <string>
#include <iostream>
#include <vector>

/**
 * Contains output strings for console
 * */
class console {
public:
 enum cdir { Up, Down, Left, Right };

 static void ShowHeader();
 static int ShowChoices(std::string folder, std::string script,int file_count, int prot_count) ;
 static void Help(std::string name,std::string message);

 static void move(cdir direction, int s);
 static std::vector<std::string> helpText(int index);
 static void linesClear(int i);

 static void pressY2continue();
};

#endif //BIOINFO2_CONSOLE_H

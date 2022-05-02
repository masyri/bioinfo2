//
// Created by manjaro on 02.05.22.
//

#ifndef RSCRIPT_H
#define RSCRIPT_H


#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;


/*
 * Class for R-Scripts
 *
 * */
class Rscript {

public:

    /*
     * Checks if the given [R-Script] or any other
     * file exists under this path.
     *
     * Example Rscript::Exist("../Rfiles/script.R")
     *
     * @filepath path of the [R-Script]
     * */
    static bool Exist(const string& filepath) {
        ifstream infile(filepath);
        if (infile) { return true; }
        return false;
    }


    /*
     * Starts the [R-script] via the command
     * lines with the specified [parameters/arguments]
     *
     * Example: $ Rscript ../Rfiles/script.R plot data.csv
     *
     * @filepath : path of the [R-Script]
     * @args     : List of all arguments
     *
     * */
    static void Run(const string& filepath,const vector<string>& args) {
        if (!Exist(filepath)) { return; }

        string command_string = getCommandString(filepath,args);

        system(command_string.c_str());
    }



    /*
      * Builds the string for the command line from
      * path and arguments
      *
      * Example: $ Rscript ../Rfiles/script.R plot data.csv
      *
      * @filepath : path of the [R-Script]
      * @args     : List of all arguments
      *
      * */
    static string getCommandString(const string& filepath,const vector<string>& args) {

        stringstream s("");
        s << "Rscript ";
        s << filepath;
        for (const string &arg: args) {
            s << " " << arg;
        }
        return s.str();
    }

};


#endif //RSCRIPT_H

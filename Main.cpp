//
// Created by manjaro on 29.04.22.
//


#include "console/console.h"
#include "console/Color.h"

#include <iostream>
#include <fstream>

#include <sstream>

#include <limits>
using namespace std;



int main(int argc, char* argv[])
{


/*
    console::ShowHeader();

    // ## Program variables

    bool file            = false;
    int loopcount        = 100;
    string filename = " --- ";
    string output_hin = "../result.hin";
    string output_file = "../table.csv";

    // ## The 'endless' loop
    while (true) {

        char chosen = console::ShowChoices(filename,loopcount);

        // ### Open Folder ###
        if (chosen == 0) {
            std::cout << C::BBLUE   <<    "\n" << " > Open folder ...\n";

            file = false;
            while (!file) {
                // counter reset

                // wait for filename typing in ...
                cout << C::BWHITE << "Type a file-path for a HIN-File in and press Enter: " << C::BRED << "(type ESC and Enter to abort)\n" << C::RESET;
                cin >> filename;

                // check first char ESC ... -> ABORT
                if (filename.begin().operator*() == '\033') {file = false;break;}
                std::ifstream infile(filename);

                // check file exists
                if (!infile) {
                    cout << C::BRED << "\n > Path is invalid or not exist ’" << filename << "’ \n" << C::RESET;
                    continue;
                }

                bool isHIN = filename.find(".hin") != string::npos;

                // check file is HIN
                if (!isHIN) {
                    cout << C::BRED << "\n > Path is invalid or not exist ’" << filename << "’ \n" << C::RESET;
                    continue;
                }
                if (isHIN) {
                    cout << C::BRED << "\n > Your File: ’" << filename << "’ \n" << C::RESET; file = true;
                    break;
                }

            }

            // if Abort, set file false
            if (!file) {filename     = " --- ";continue;}

            console::pressY2continue();
            continue;
        }


        // ### Set Loop count ###
        if (chosen == 1) {
            std::cout << C::BBLUE   <<    "\n" << " > Set Count of Loops for Simulated annealing.";
            std::cout << C::BBLUE   <<    "\n" << "   Example: 100 or 1000 or more";
            std::cout << C::BRED    <<    "\n" << "   (Please not to big: your Computer will explode)\n";
            while (true) {
                // input
                string inp;
                cout << C::BWHITE << " > Choose an integer [ int > 0 ] : \n" << C::RESET;
                cin >> inp;

                // check positive
                int val = atoi(inp.c_str());
                if (val < 1) {cout << C::BRED << " Your input is negative or not a valid integer : '" << val << "' \n" << C::RESET;
                    continue;}

                //
                loopcount = val;
                break;
            }

            std::cout << C::BBLUE   << " Your input : '" << loopcount << "' \n" ;
            console::pressY2continue();
            continue;
        }


        // ### Simulated Annealing ###
        if (chosen == 2) {
            if (!file) {std::cout << C::BBLUE   <<    "\n" << " > Please choose a file first.";console::pressY2continue();;continue;}
            std::cout << C::BBLUE   <<    "\n" << " > Start Simulated Annealing with " << loopcount << " loops.\n\n";


            Annealing anneal(filename);
            std::cout << C::BBLUE << "File loaded ..." << "\n";
            anneal.evaluate(loopcount);
            std::cout << C::BBLUE << "Annealing finished ..." << "\n";
            anneal.createHINFile(output_hin);

            std::cout << C::BBLUE   <<    "\n" << " > HIN File created: " << output_hin << ".\n\n";

            console::pressY2continue();
            continue;
        }


        // ### Optimum ###
        if (chosen == 3) {
            if (!file) {std::cout << C::BBLUE   <<    "\n" << " > Please choose a file first.";console::pressY2continue();;continue;}
            std::cout << C::BBLUE   <<    "\n" << " > Start Simulated Annealing " << loopcount << " loops + Optimum-Output.\n\n";

            Annealing anneal(filename);
            std::cout << C::BBLUE << "File loaded ..." << "\n";
            anneal.evaluate(loopcount);
            std::cout << C::BBLUE << "Annealing finished ..." << "\n";

            anneal.createOptimumFile(output_file);

            std::cout << C::BBLUE   <<    "\n" << " > Optimum File created: " << output_file << ".\n\n";
            console::pressY2continue();
            continue;
        }


        // ### break the loop and close the program ###
        if (chosen == '\033') {break;}

    }
*/
    std::cout << C::BRED   <<    "\n" << " > Program aborted.\n" << C::RESET;

    return 1;
}



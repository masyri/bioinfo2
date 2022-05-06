//
// Created by manjaro on 29.04.22.
//


#include "console/console.h"
#include "console/Color.h"
#include "Data.h"
#include "Predictor.h"
#include "Rscript.h"

#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/molecule.h>
#include <BALL/KERNEL/atom.h>
#include <BALL/KERNEL/bond.h>
#include <BALL/KERNEL/PTE.h>
#include <BALL/STRUCTURE/secondaryStructureProcessor.h>
#include <BALL/STRUCTURE/fragmentDB.h>
#include <BALL/STRUCTURE/peptides.h>
#include <BALL/FORMAT/PDBFile.h>

#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <sstream>

using namespace std;
using namespace BALL;


int main(int argc, char* argv[])
{

    // ## Program variables

    string pathPDB       = "---";
    bool file            = false;
    int filecount        = 0;
    int proteincount     = 0;
    vector<string> files = {};
    string R_Path        = "../R/script.R";
    string R_args        = " 10 10 20";
    string output        = "../Table/";


    // ## The 'endless' loop
    while (true) {

        char chosen = console::ShowChoices(pathPDB,R_Path,filecount,proteincount);


        // ### Open Folder ###
        if (chosen == 0) {
            std::cout << C::BBLUE   <<    "\n" << " > Open folder ...\n";

            file = false;
            while (!file) {
                // counter reset
                filecount = 0;
                proteincount  = 0;
                files = {};

                // wait for filename typing in ...
                cout << C::BWHITE << "Type a folder-path with PDB-Files in and press Enter: " << C::BRED << "(type ESC and Enter to abort)\n" << C::RESET;
                cin >> pathPDB;

                // check first char ESC ... -> ABORT
                if (pathPDB.begin().operator*() == '\033') {file = false;break;}
                std::ifstream infile(pathPDB);

                // check folder exists
                if (!std::experimental::filesystem::is_directory(pathPDB)) {
                    cout << C::BRED << "\n > Path is invalid or not exist ’" << pathPDB << "’ \n" << C::RESET;
                    continue;
                }

                // check folder is valid + count correct files ...

                for (const auto & entry : std::experimental::filesystem::directory_iterator(pathPDB))
                {
                    std::stringstream fp("");
                    std::cout << " - ";
                    fp << entry.path();
                    bool isPDB = fp.str().find(".pdb") != string::npos;
                    if (isPDB) {std::cout << C::BGREEN;filecount++;files.push_back(entry.path().string());} else {std::cout << C::BRED;}
                    std::cout << entry.path() << std::endl << C::RESET;


                }

                // files found ? -> if enough break this loop
                if (filecount < 1) {
                    cout << C::BRED << "\n > No PDB-Files found in this folder: ’" << pathPDB << "’ \n" << C::RESET;
                    filecount = 0;
                    continue;
                } else {
                    cout << C::BGREEN << "\n\n > " << filecount <<" PDB-Files found in this folder: ’" << pathPDB << "’ \n" << C::RESET;
                    file = true;
                    break;

                }
            }

            // if Abort, set file false
            if (!file) {pathPDB     = "---";continue;}

            // count proteins
            for (auto file : files) {
                PDBFile f(file, ios::in);
                System S;
                f >> S;
                proteincount += S.countProteins();
            }

            console::pressY2continue();
            continue;
        }


        // ### Create Table ###
        if (chosen == 1) {
            std::cout << C::BBLUE   <<    "\n" << " > Create CSV-Table.\n\n";

            // build filename
            std::stringstream s("");
            s << output << "table.csv";

            // table
            std::cout << C::BLUE  << " PDB-Files : " << files.size() << "\n";
            Predictor pred(files);
            std::cout << C::BLUE  << " Proteins  : " << pred.data_point_arrays.size() << "\n";
            std::cout << C::BLUE  << " DataSets  : " << pred.countdatasets() << "\n";
            pred.createTableFile(s.str());

            // end
            std::cout << C::BBLUE   <<    "\n" << " > File created: ' " << s.str() <<" '\n";
            console::pressY2continue();
            continue;
        }


        // ### Change R-Script location ###
        if (chosen == 2) {
            std::cout << C::BBLUE   <<    "\n" << " > Set R-Script Path\n";
            while (true) {
                // wait for filename typing in ...
                cout << C::BWHITE << "Type R-Script Path in and press Enter: " << C::BRED << "(type ESC and Enter to abort)\n" << C::RESET;
                cin >> R_Path;
                // check first char ESC ... -> ABORT
                if (R_Path.begin().operator*() == '\033') {string R_path = "../R/script.R";break;}

                if (Rscript::Exists(R_Path))
                {
                    break;
                }
                else
                {
                    cout << C::BRED << "\n > invalid filepath ’" << R_Path << "’ \n" << C::RESET;
                }
            }
            //
            cout << C::BBLUE   << " > You have a new R-Script path: " << R_Path << "\n";


            console::pressY2continue();
            continue;
        }



        // ### Run R-Script ###
        if (chosen == 3) {
            std::cout << C::BBLUE   <<    "\n" << " > Run R-Script :\n";
            // create commandline:
            std::stringstream call("");
            call << "Rscript " << R_Path << R_args;
            // show infos:
            std::cout << C::BWHITE   <<    "\n" << " > Script File: " << C::BGREEN << "$ " << call.str();
            std::cout << C::BWHITE   <<    "\n" << " > Continue?    \n" << C::BBLUE;
            console::pressY2continue();
            // call commandline
            std::cout << C::RESET;
            system(call.str().c_str());
            // finish
            std::cout << C::BWHITE   <<    "\n" << " > R-Script finished.\n" << C::BBLUE;
            console::pressY2continue();
            continue;
        }


        // ### break the loop and close the program ###
        if (chosen == '\033') {break;}

    }

    std::cout << C::BRED   <<    "\n" << " > Program aborted.\n" << C::RESET;

    return 1;
}


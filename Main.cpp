//
// Created by manjaro on 29.04.22.
//

/**
 *
 *  ##   R A M A C H A N D R A N - P L O T   ##
 *
 *  Start this program with ./ramachandran without arguments
 *
 *  - To use the program, load a PDB-file via the menu. 
 *
 *  - You can start the R-Script with this program.
 *
 *  - You can change the path of the R-Script (for path fix)
 *
 *  - You can manually create the csv-files for the R-Script
 *    and run the R-Script separately
 *
 *  - You can print out all assignment statistics
 *
 *
 *
 */

#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/molecule.h>
#include <BALL/KERNEL/atom.h>
#include <BALL/KERNEL/bond.h>
#include <BALL/KERNEL/PTE.h>
#include <BALL/STRUCTURE/secondaryStructureProcessor.h>
#include <BALL/STRUCTURE/fragmentDB.h>
#include <BALL/STRUCTURE/peptides.h>
#include <BALL/FORMAT/PDBFile.h>
#include "console/console.h"
#include "console/Color.h"

#include <iostream>

#include "Ramachandran.h"
#include "Rscript.h"

using namespace std;
using namespace BALL;

int main(int argc, char* argv[])
{

    // ## Program variables
    console::ShowHeader();
    string filename     = "---";
    bool file           = false;
    string proteinname  = "no_name";
    string R_path       = "../script.R";
    string output       = "../plotList.csv";


    // ## The 'endless' loop
    while (true) {

        char chosen = console::ShowChoices(filename,proteinname,R_path);

        // Load File
        if (chosen == '1') {
            file = false;
            while (!file) {
                // wait for filename typing in ...
                cout << C::BWHITE << "Type PDB-File in and press Enter: " << C::BRED << "(type ESC and Enter to abort)\n" << C::RESET;
                cin >> filename;
                // check first char ESC ... -> ABORT
                if (filename.begin().operator*() == '\033') {file = false;break;}
                std::ifstream infile(filename);
                // check file is valid ...
                if (infile) {
                    // file .pdb ?
                    if (filename.find(".pdb") == string::npos) {
                        cout << C::BRED << "\n > your file is not a  *.pdb - File  ’" << filename << "’ \n" << C::RESET;
                        continue;}
                    // file okay -> set file true and continue to program
                    file = true;
                    continue;
                    // file not exist -> return to loop
                    } else {
                    cout << C::BRED << "\n > invalid filename ’" << filename << "’ \n" << C::RESET;}
            }
            // if Abort, set file false
            if (!file) {proteinname  = "---";filename     = "---";continue;}

            // open file ...
            PDBFile f(filename, ios::in);
            System S;
            f >> S;
            Ramachandran R(S);
            proteinname = R.protein_name;
            
            continue;
            }

        // Print sequences
        if (chosen == '2') {
                if (!file) {cout << C::BRED << " > No valid PDB File loaded.\n";console::pressY2continue();continue;}
                cout << C::BBLUE   << " > Print sequences ...\n\n";
            
                PDBFile f(filename, ios::in);
                System S;
                f >> S;
                Ramachandran R(S);
            
                R.printSequences();
                cout << "\n";
                console::pressY2continue();
                continue;
            }

        // Print stats in percent
        if (chosen == '3') {
                if (!file) {cout << C::BRED << " > No valid PDB File loaded.\n";console::pressY2continue();continue;}
                cout << C::BBLUE   << " > Print stats ...";

                PDBFile f(filename, ios::in);
                System S;
                f >> S;
                Ramachandran R(S);

                R.printStats();
                console::pressY2continue();
                continue;
            }

        // Print Angles
        if (chosen == '4') {
                if (!file) {cout << C::BRED << " > No valid PDB File loaded.\n";console::pressY2continue();continue;}
                cout << C::BBLUE   << " > Print all Psi/Phi angles ...\n";

                PDBFile f(filename, ios::in);
                System S;
                f >> S;
                Ramachandran R(S);

                auto angles = R.getTorsionAngels();
                console::ShowAngles(output,angles);
                console::pressY2continue();
                continue;
            }

        // Create CSV File
        if (chosen == '5') {
                if (!file) {cout << C::BRED << " > No valid PDB File loaded.\n";console::pressY2continue();continue;}
                cout << C::BBLUE << "\n > Create CSV file ...\n";

                PDBFile f(filename, ios::in);
                System S;
                f >> S;
                Ramachandran R(S);

                auto angles = R.getTorsionAngels();
                Ramachandran::anglesToFile(output,angles);
                cout << C::BBLUE   << " > File created '" << C::BWHITE << output << "'\n" << C::RESET;
                cout << C::BWHITE  <<   "\n" << "   " << C::BMAGENTA  << "You can create a Plot with the R-File 'script.R'";
                cout << C::BWHITE  <<   "\n" << "   " << C::BMAGENTA  << "please call:\n";
                cout << C::BWHITE  <<   "\n" << "   " << C::BMAGENTA  << "$ Rscript script.R [plot_name] [inputfile]\n";
                cout << C::BWHITE  <<   "\n" << "   " << C::BMAGENTA  << "example: $ Rscript script.R xyZ72 plotList.csv\n\n" << C::RESET;

                console::pressY2continue();
                continue;
            }

        // Set R-Script-Path
        if (chosen == '6') {
            while (true) {
                // wait for filename typing in ...
                cout << C::BWHITE << "Type R-Script Path in and press Enter: " << C::BRED << "(type ESC and Enter to abort)\n" << C::RESET;
                cin >> R_path;
                // check first char ESC ... -> ABORT
                if (R_path.begin().operator*() == '\033') {string R_path = "../script.R";break;}

                if (Rscript::Exists(R_path))
                {
                    break;
                }
                else
                {
                    cout << C::BRED << "\n > invalid filepath ’" << R_path << "’ \n" << C::RESET;
                }
            }
            //
            cout << C::BBLUE   << " > You have a new R-Script path: " << R_path << "\n";
            console::pressY2continue();
            continue;
        }


        // Run R-Script
        if (chosen == '7') {
            // file validation check
            if (!file) {
                cout << C::BRED << " > No valid PDB File loaded.\n";console::pressY2continue();continue;
            }
            if (!Rscript::Exists(R_path)){
                cout << C::BRED << "\n > R-Script not found: ’" << filename << "’ \n  if path not working start the R-Script manually." << C::RESET;
                console::pressY2continue();continue;
            }

            // create System
            PDBFile f(filename, ios::in);
            System S;
            f >> S;
            Ramachandran R(S);

            // create CSV-File
            auto angles = R.getTorsionAngels();
            Ramachandran::anglesToFile(output,angles);
            cout << C::BBLUE   << " > CSV-File created '" << C::BWHITE << output << "'\n" << C::RESET;

            // build arguments for R-Script
            vector<string> _args = { proteinname , output };

            // load R-Script
            std::cout << C::BBLUE    <<   "\n" << " > Run R-Script:\n";
            std::cout << C::BWHITE   <<   "\n" << " > Run Command: " << C::BGREEN << "$ " << Rscript::getCommandString(R_path,_args);
            std::cout << C::BWHITE   <<   "\n" << " > Continue?    \n" << C::BBLUE;
            console::pressY2continue();

            // start R-Script
            Rscript::Run(R_path,_args);

            // finish
            std::cout << C::BWHITE   <<    "\n" << " > R-Script finished.\n" << C::BBLUE;

            console::pressY2continue();
            continue;
        }


        // break the loop and close the program
        if (chosen == '\033') {break;}

}

    std::cout << C::BRED   <<    "\n" << " > Program aborted.\n";

return 1;
}

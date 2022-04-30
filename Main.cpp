//
// Created by manjaro on 29.04.22.
//

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

using namespace std;
using namespace BALL;

int main(int argc, char* argv[])
{

    // ## Program variables
    console::ShowHeader();
    string filename     = "---";
    bool file           = false;
    string proteinname  = "---";
    string output       = "../plotList.csv";


    // ## The 'endless' loop
    while (true) {

        char chosen = console::ShowChoices(filename,proteinname);

        // Load File
        if (chosen == '1') {
            file = false;
            while (!file) {
                cout << C::BWHITE << "Type PDB-File in and press Enter: " << C::BRED << "(type ESC and Enter to abort)\n" << C::RESET;
                cin >> filename;
                if (filename.begin().operator*() == '\033') {file = false;break;}
                std::ifstream infile(filename);
                if (infile) {
                    file = true;
                    continue;} else {
                    cout << C::BRED << "\n > invalid filename ’" << filename << "’ \n" << C::RESET;}
            }
            if (!file) {proteinname  = "---";filename     = "---";continue;}
                        
            PDBFile f(filename, ios::in);
            System S;
            f >> S;
            Ramachandran R(S);
            proteinname = R.protein_name;
            
            continue;
            }

        // Print sequences
        if (chosen == '2') {
                if (!file) {cout << C::BRED << " > No valid PDB File loaded.\n > press Enter to continue ...";getchar();continue;}
                cout << C::BBLUE   << " > Print sequences ...\n\n";
            
                PDBFile f(filename, ios::in);
                System S;
                f >> S;
                Ramachandran R(S);
            
                R.printSequences();
                std::cout << C::BLUE   <<    "\n\n" << " > press [ENTER] to continue ... \n";
                getchar();
                continue;
            }

        // Print stats in percent
        if (chosen == '3') {
            if (!file) {cout << C::BRED << " > No valid PDB File loaded.\n > press Enter to continue ...";getchar();continue;}
            cout << C::BBLUE   << " > Print stats ...\n";
            
            PDBFile f(filename, ios::in);
            System S;
            f >> S;
            Ramachandran R(S);
            
            R.printStats();
            std::cout << C::BLUE   <<    "\n" << " > press [ENTER] to continue ... \n";
            getchar();
            continue;
            }

        // Print Angles
        if (chosen == '4') {
            if (!file) {cout << C::BRED << " > No valid PDB File loaded.\n > press Enter to continue ...";getchar();continue;}
            cout << C::BBLUE   << " > Print all Psi/Phi angles ...\n";
            
            PDBFile f(filename, ios::in);
            System S;
            f >> S;
            Ramachandran R(S);
            
            auto angles = R.getTorsionAngels();
            console::ShowAngles(output,angles);
            continue;}

        // Create CSV File
        if (chosen == '5') {
            if (!file) {cout << C::BRED << " > No valid PDB File loaded.\n > press Enter to continue ...";getchar();continue;}
            cout << C::BBLUE << " > Create CSV file ...\n";
            
            PDBFile f(filename, ios::in);
            System S;
            f >> S;
            Ramachandran R(S);
            
            auto angles = R.getTorsionAngels();
            Ramachandran::anglesToFile(output,angles);
            cout << C::BBLUE   << " > File created '" << output << "'\n";
            cout << C::BWHITE  <<   "\n" << " > " << C::BMAGENTA  << " ---> You can create a Plot with the R-File 'script.R'";
            cout << C::BWHITE  <<   "\n" << " > " << C::BMAGENTA  << "please call:";
            cout << C::BWHITE  <<   "\n" << " > " << C::BMAGENTA  << "$ Rscript test.R [plot_name] [inputfile]";
            cout << C::BWHITE  <<   "\n" << " > " << C::BMAGENTA  << "example: $ Rscript script.R xyZ72 plotList.csv\n\n" << C::RESET;
            cout << C::BLUE   <<    "\n" << " > press [ENTER] to continue ... \n";
            getchar();
            continue;
            }

        // break the loop and close the program
        if (chosen == '\033') {break;}

}

    std::cout << C::BRED   <<    "\n" << " > Program aborted.\n";

return 1;
}

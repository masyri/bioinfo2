//
// Created by manjaro on 29.04.22.
//


#include "console/console.h"
#include "console/Color.h"
#include "ccp/CCP.h"
#include "ccp/Probability.h"
#include "ccp/Scoring.h"

#include <iostream>
#include <fstream>

#include <sstream>
#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/molecule.h>
#include <BALL/KERNEL/atom.h>
#include <BALL/KERNEL/bond.h>
#include <BALL/KERNEL/PTE.h>
#include <BALL/STRUCTURE/secondaryStructureProcessor.h>
#include <BALL/STRUCTURE/fragmentDB.h>
#include <BALL/STRUCTURE/peptides.h>
#include <BALL/FORMAT/PDBFile.h>
#include <vector>
#include <string>
#include <experimental/filesystem>

using namespace std;
using namespace BALL;



int main(int argc, char* argv[])
{
    
    console::ShowHeader();

    // ## Program variables

    string pathPDB       = "---";
    bool file            = false;
    int filecount        = 0;
    int as_count        = 0;
    int proteincount     = 0;
    vector<string> files = {};



    // ## The 'endless' loop
    while (true) {

        char chosen = console::ShowChoices(pathPDB,"",filecount,proteincount,as_count);


        // ### Open Folder ###
        if (chosen == 0) {
            std::cout << C::BBLUE   <<    "\n" << " > Open folder ...\n";

            file = false;
            while (!file) {
                // counter reset
                filecount = 0;
                as_count = 0;
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
               as_count += S.countResidues();
            }

            console::pressY2continue();
            continue;
        }


        // ### Occurrence Matrix ###
        if (chosen == 1) {
            std::cout << C::BBLUE   <<    "\n" << " > Show Occurrence Matrix.\n\n";

            Occurrence O = CCP::createOccurrenceMatrixFromFiles(files);
            O.print_styled();
            string B = C::BGREEN;
            string b = C::YELLOW;

            std::cout << B << "\n" << " > Cutted after 25 columns.";
            std::cout << B << "\n" << " > [Residue count:] "      << b << O.all_residues  << B << " [ > 0 contacts:] " << b << O.near_residues << B << " [ 0 contacts:] " << b << O.zerocontact_residues;
            std::cout << B << "\n" << " > [Unknown AminoAcids:] " << b << O.amino_unknown << B << " [residues with contacts to 'Unknown':] " << b << O.contact_unknowns << B;
            std::cout << B << "\n" << " > [Maximum contact] k = " << b << (O.getColumnCount()-1) << B << "\n";
            console::pressY2continue();
            continue;
        }


        // ### Probability Matrix ###
        if (chosen == 2) {
            std::cout << C::BBLUE   <<    "\n" << " > Show Probability Matrix.\n\n";

            Occurrence O = CCP::createOccurrenceMatrixFromFiles(files);
            Probability p(O);
            p.print_styled();
            string B = C::BGREEN;
            string b = C::YELLOW;

            std::cout << B  <<    "\n" << " > Cutted after 20 columns.";
            std::cout << B << "\n" << " > [Maximum contact] k = " << b << (O.getColumnCount()-1) << B << "\n";
            console::pressY2continue();
            continue;
        }


        // ### Scoring Matrix ###
        if (chosen == 3) {
            std::cout << C::BBLUE   <<    "\n" << " > Show Scoring Matrix.\n\n";

            Occurrence O = CCP::createOccurrenceMatrixFromFiles(files);
            Probability p(O);
            Scoring s(O,p);
            s.print_styled();
            string B = C::BGREEN;
            string b = C::YELLOW;

            std::cout << B   <<    "\n" << " > Cutted after 20 columns.";
            std::cout << B << "\n" << " > Score: [500:] "      << b << s.val500  << B << " [ -500:] " << b << s.valn500 << B << " [ log(Wak):] " << b << s.vallog;

            std::cout << B << "\n" << " > [Maximum contact] k = " << b << (O.getColumnCount()-1) << B << "\n";
            console::pressY2continue();
            continue;
        }


        // ### break the loop and close the program ###
        if (chosen == '\033') {break;}

    }

    std::cout << C::BRED   <<    "\n" << " > Program aborted.\n" << C::RESET;

    return 1;
}


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
cout << "\n R A M A C H A N D R A N \n" ;

    // ## get arguments
    if (argc < 2) {cerr << "Not enough arguments" << endl; return 1; }

    // ## load file
    string file = "../PDB/1A0B.pdb";
    PDBFile f(file, ios::in);
    System S;
    f >> S;

    // ## create Ramachandran

    Ramachandran R(S);

    
    
    
    // ## calculate angles and print out to console and file

    auto angles = R.getTorsionAngels();

    console::ShowAngles(output,angles);
    Ramachandran::anglesToFile(output,angles);


}

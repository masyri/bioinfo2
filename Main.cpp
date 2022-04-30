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
    
    // ## correct arg-count?

    if (argc < 2) { console::Help("","   not enough arguments!");return 0; }
    if (argc > 2) { console::Help("","   too many arguments!");return 0; }

    // ## get arguments
    
    string file   = argv[1];
    string output = "../plotList.csv";

    // ## load file

    PDBFile f(file, ios::in);
    System S;
    f >> S;

    // ## create Ramachandran

    Ramachandran R(S);

    console::ShowHeader(file,R.protein_name);

    cout << "\n" << R << "\n";
    
    // ## calculate angles and print out to console and file

    auto angles = R.getTorsionAngels();

    console::ShowAngles(output,angles);
    
    Ramachandran::anglesToFile(output,angles);


}

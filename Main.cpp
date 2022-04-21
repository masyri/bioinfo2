#include <BALL/KERNEL/system.h>
#include<BALL/KERNEL/molecule.h>
#include<BALL/KERNEL/atom.h>
#include<BALL/KERNEL/bond.h>
#include <BALL/KERNEL/PTE.h>
#include <BALL/FORMAT/PDBFile.h>
#include "Groups.h"
#include "console/console.h"
#include "console/Color.h"
#include "DSSP.h"
#include <iostream>


using namespace std;
using namespace BALL;

int main(int argc, char* argv[])
{

    // ## correct arg-count?
    //if (argc < 2) { console::Help("   not enough arguments!");return 0; }
    //if (argc > 2) { console::Help("   too many arguments!");return 0; }
    console::ShowHeader();

    // ## import file
    std::string arg_In  = "../2x7h.pdb";
    PDBFile f(arg_In);
    System S;
    f >> S;

    // ## create DSSP

    DSSP dssp(S);

    // ## show statistics

    console::ShowInputs(arg_In,S.countAtoms(),dssp.NH_Groups.size(),dssp.CO_Groups.size(),dssp.result.size());

    // ## print all bonds to console
    cout << C::BWHITE << "press any key to print all h-bonds in format (i,j) ..." << endl;
    getchar();
    int bond_count = dssp.printResults();
    cout << C::BWHITE << "\n => " << bond_count << " bonds printed." << endl;


    /*
                 (meow!)
         /\_/\   )/
   ((   (=^.^=)
   ))    )   (
    (( /      \    ' '
     (   ) || ||     ' '
     '----''-''-'  >+++°>

    */

    return 0;
}

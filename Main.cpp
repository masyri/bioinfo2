#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/molecule.h>
#include <BALL/KERNEL/atom.h>
#include <BALL/KERNEL/bond.h>
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

    std::string arg_In    = "../2x7h.pdb";
    std::string file_out  = "../AminoSecondary.txt";
    PDBFile f(arg_In);
    System S;
    f >> S;

    // ## >> 1a) << create DSSP and create a list of H-Bonds

    DSSP dssp(S);
    dssp.getGroups();
    cout << "bla " << endl;
    int count_hbonds_before = dssp.result.size();
    int count_atoms = S.countAtoms();
    int count_NH    = dssp.NH_Groups.size();
    int count_CO    = dssp.NH_Groups.size();
    

    // ## >> 1b) << delete all != ( i , i+3 4 5 ) from the list of H-Bonds

    dssp.removeHBonds();
    int count_hbonds_after = dssp.result.size();

    // ## >> 1c) << compute helices and create file

    dssp.computeHelices(file_out);

    // ## show statistics

    console::ShowInputs(arg_In,file_out,count_atoms,count_NH,count_CO,count_hbonds_before,count_hbonds_after);

    // ## print all bonds to console 'result from exercise b)'

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

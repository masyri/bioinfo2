#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/molecule.h>
#include <BALL/KERNEL/atom.h>
#include <BALL/KERNEL/bond.h>
#include <BALL/KERNEL/PTE.h>
#include <BALL/STRUCTURE/secondaryStructureProcessor.h>
#include <BALL/STRUCTURE/fragmentDB.h>
#include <BALL/STRUCTURE/peptides.h>
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
    
    //if (argc < 3) { console::Help("   not enough arguments!");return 0; }
    //if (argc > 2) { console::Help("   too many arguments!");return 0; }
    console::ShowHeader();

    // ## import file

    std::string arg_In    = "../2x7h.pdb";
    std::string file_out  = "../AminoSecondary.txt";
    PDBFile f(arg_In);
    System S;
    f >> S;

    // ## add hydrogens

    //FragmentDB fragdb("");
    //FragmentDB fragdb("../Fragments.db");
    //set(BALL_DIR "/opt/BALL/install/lib/cmake/BALL/")
    //FragmentDB fragdb("/opt/BALL/install/share/BALL/data/fragments/Fragments.db");
    //S.apply(fragdb.normalize_names);
    //S.apply(fragdb.add_hydrogens);
    //S.apply(fragdb.build_bonds);

    // ## >> 1a) << create DSSP and create a list of H-Bonds

    DSSP dssp(S);
    dssp.getGroups();
    int count_hbonds_before = dssp.result.size();
    int count_atoms = S.countAtoms();
    int count_prot  = S.countProteins();
    int res         = S.countResidues();
    std::string name = dssp.names;
    int count_NH    = dssp.NH_Groups.size();
    int count_CO    = dssp.NH_Groups.size();
    dssp.startAlgorithm();

    // ## >> 1b) << delete all != ( i , i+3 4 5 ) from the list of H-Bonds

    dssp.removeHBonds();
    int count_hbonds_after = dssp.result.size();

    // ## >> 1c) << compute helices and create file

    dssp.computeHelices(file_out);

    // ## show statistics

    console::ShowInputs(arg_In,file_out,count_atoms,count_NH,count_CO,count_hbonds_before,count_hbonds_after,name,count_prot,res);

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

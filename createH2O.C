#include <BALL/KERNEL/system.h>
#include<BALL/KERNEL/molecule.h>
#include<BALL/KERNEL/atom.h>
#include<BALL/KERNEL/bond.h>
#include <BALL/KERNEL/PTE.h>
#include <BALL/FORMAT/PDBFile.h>


using namespace std;
using namespace BALL;

int main(int argc, char* argv[])
{

    // ## show help

    const char* RESET   = "\033[0m";
    const char* BBLUE    = "\033[1;34m";
    const char* BWHITE  = "\033[1;37m";
    const char* BRED    = "\033[1;31m";
    cout  <<  BBLUE <<  "\n  Help:    " << BBLUE << " $ ./createH2O [angle] [filename] " ;
    cout  <<  "\n  Example: " << BBLUE  << " $ ./createH2O 90.0 ../your_amazing_molecule.pdb" ;
    cout  <<  "\n  ";
    cout  <<  BWHITE << "\n  [angle]    | " << BWHITE  << " angle in degree " ;
    cout  <<  "\n  [file]     | " << BWHITE  << " output-file " << BRED << " !!! File path realitive !!!\n\n " << RESET;

    // ## correct arg-count?

    if (argc < 2) { cout  <<  BRED  <<  "\n   ==> Not enough arguments!   \n" << RESET; return 0; }
    if (argc > 2) { cout  <<  BRED  <<  "\n   ==> Too many arguments!     \n" << RESET; return 0; }

    // ## Create System and Molecule ...

    // B)
    System s;
    BALL::Molecule m;

    // C)
    BALL::Atom Ox;
    BALL::Atom H1;
    BALL::Atom H2;
    auto oxy = PTE[Element::O];
    auto hyd = PTE[Element::H];
    Ox.setElement(oxy);
    H1.setElement(hyd);
    H2.setElement(hyd);

    BALL::Bond* a = Ox.createBond(H1);
    BALL::Bond* b = Ox.createBond(H2);

    Ox.setPosition(Vector3(0,0,0));
    H1.setPosition(Vector3(0,1.42,0));
    H2.setPosition(Vector3(1,1.42,0));

    m.insert(Ox);
    m.insert(H1);
    m.insert(H2);


    // ## Set angle

    double angle_input  = atof(argv[1]);
    Angle angle(angle_input, false);
    Vector3 rotationaxis(1., 0., 0.);

    Matrix4x4 mat;
    mat.setRotation(angle, rotationaxis);

    // ## Insert finished molecule in System

    s.insert(m);


    // ## ... and write in the file
    std::string arg_out  = argv[2];
    PDBFile outfile(arg_out, ios::out);
    outfile << s;
    outfile.close();
    
    cout <<  BWHITE <<  "\n   ==> File created:  " << BBLUE << arg_out << "\n" << RESET ;

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

#include <sstream>
#include <iomanip>
#include "console.h"
#include "Color.h"


/*
* sends a big-font Ascii-Art-Header to std::cout
* */
void console::ShowHeader(std::string name) {
    std::cout << "\n";
    std::string r  = C::RED;
    std::string R  = C::BRED;
    std::string Y  = C::BYELLOW;
    std::string G  = C::BGREEN;
    std::string B  = C::BBLUE;
    std::string b  = C::BLUE;

    std::cout << b << "\n     ___                                   ";
    std::cout << b << "\n    /   \\___     ___     ___               ";
    std::cout << b << "\n    \\___/   \\___/   \\___/   \\___           ";
    std::cout << b << "\n    /   \\   /   \\   /   \\                  ";
    std::cout << B << "\n         D S     S P     Protein Structure ";
    std::cout << B << "\n                         Assignment        ";
    std::cout << B << "\n";


}


/*
 *
 * send the help-message to std::cout -createH2O-
 **/
void console::Help(std::string name,std::string message) {
    console::ShowHeader(name);
    std::cout << C::BRED  << message <<  "\n\n" ;
    std::cout << C::BWHITE  <<  "";
    std::cout << C::BWHITE  <<  "  Help:    " << C::BYELLOW << " $ ./deepBlackCoffee [PDB-File] \n" ;
    std::cout << C::BWHITE  <<  "  Example: " << C::BGREEN  << " $ ./deepBlackCoffee ../your_amazing_molecule.pdb \n" ;
    std::cout << C::BWHITE  <<  "\n" ;
    std::cout << C::BGREEN  <<  " [FILE]   PDB-File   " << C::BWHITE << "| " << C::BYELLOW << " File with your molecule\n" ;
    std::cout << C::BWHITE  <<  "\n" ;
}



/*
 *
 * send inputs and outputs to std::cout
 **/
void console::ShowAngles(std::string outputfile, std::vector<AnglePair> AP) {

    std::cout << C::BWHITE  <<    "\n" << " | press [ENTER] to print out all angles ... ";
    getchar();
    std::cout << C::BWHITE  <<    "\n";
    for(auto ap : AP) {
        cout << ap << endl;
    }
    std::cout << C::BWHITE  <<    "\n" << " | " << C::BLUE   << AP.size() << " tuples printed ... ";
    std::cout << C::BWHITE  <<    "\n" << " | " << C::BBLUE  << "output-file : " << outputfile;
    std::cout << C::BWHITE  <<    "\n" << " | ";
    std::cout << C::BWHITE  <<    "\n" << " | " << C::BGREEN  << "You can create a Plot with the R-File 'script.R'";
    std::cout << C::BWHITE  <<    "\n" << " | " << C::BGREEN  << "please call:";
    std::cout << C::BWHITE  <<    "\n" << " | " << C::GREEN   << "$ Rscript script.R [plot_name] [inputfile]";
    std::cout << C::BWHITE  <<    "\n" << " | " << C::RED     << "example: $ Rscript test.R xyZ72 plotList.csv\n\n" << C::RESET;

}


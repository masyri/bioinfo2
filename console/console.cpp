#include <sstream>
#include <iomanip>
#include "console.h"
#include "Color.h"


/*
* sends a big-font Ascii-Art-Header to std::cout
* */
void console::ShowHeader() {
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
    std::cout << B << "\n\n";


}


/*
 *
 * send the help-message to std::cout
 **/
void console::Help(std::string message) {
    console::ShowHeader();
    std::cout << C::BRED  << message <<  "\n\n" ;
    std::cout << C::BWHITE  <<  "";
    std::cout << C::BWHITE  <<  "  Help:    " << C::BYELLOW << " $ ./dssp [input]  \n" ;
    std::cout << C::BWHITE  <<  "  Example: " << C::BGREEN  << " $ ./dssp ../file.pdb \n" ;
    std::cout << C::BWHITE  <<  "\n" ;
    std::cout << C::BGREEN  <<  " [FILE]   input   " << C::BWHITE << "| " << C::BYELLOW << " File with your molecule\n" ;
    std::cout << C::BWHITE  <<  "\n" ;
}



/*
 *
 * statistics
 **/
void console::ShowInputs(std::string file, int atoms, int NH, int CO, int hbonds) {

    std::cout << C::BWHITE  <<    "";
    std::cout << C::BWHITE  <<            "\n  | file:               "<< C::BCYAN  << file ;
    std::cout << C::BWHITE  <<            "\n  | count all atoms:    "<< C::BMAGENTA  << atoms ;
    std::cout << C::BWHITE  <<            "\n  | count NH-Groups:    "<< C::BBLUE  << NH ;
    std::cout << C::BWHITE  <<            "\n  | count CO-Groups:    "<< C::BBLUE  << CO ;
    std::cout << C::BWHITE  <<            "\n  | -> H-Bonds     :    "<< C::BCYAN  << hbonds ;
    std::cout << C::BWHITE  <<    "\n\n";

}


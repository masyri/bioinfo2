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
    std::cout << B << "\n";


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
void console::ShowInputs(std::string file_in, std::string file_out, int atoms, int NH, int CO, int hbonds_all, int hbonds_after_removing) {

    std::cout << C::BRED    <<    "\n  | PDB file in            ->  " << C::BCYAN  << file_in ;
    std::cout << C::BRED    <<    "\n  | created File helices   ->  " << C::BCYAN  << file_out ;

    std::cout << C::BGREEN   << "\n\n   count all atoms   " << C::BWHITE << " :   " << C::GREEN    << atoms ;
    std::cout << C::BYELLOW  <<   "\n   count NH-Groups   " << C::BWHITE << " :   " << C::YELLOW   << NH ;
    std::cout << C::BYELLOW  <<   "\n   count CO-Groups   " << C::BWHITE << " :   " << C::YELLOW   << CO ;
    std::cout << C::BBLUE    <<   "\n   count H-Bonds     " << C::BWHITE << " :   " << C::BLUE     << hbonds_all ;
    std::cout << C::BMAGENTA <<   "\n   -> after deleting " << C::BWHITE << " :   " << C::BMAGENTA << hbonds_after_removing ;
    std::cout << C::RESET    << "\n\n";

}


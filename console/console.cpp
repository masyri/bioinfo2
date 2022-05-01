#include <sstream>
#include <iomanip>
#include "console.h"
#include "Color.h"

/*
 * sends a big-font Ascii-Art-Header to std::cout
 *
* */
void console::ShowHeader() {
    std::cout << "\n";
    std::string r  = C::RED;
    std::string R  = C::BRED;
    std::string Y  = C::BYELLOW;
    std::string y  = C::YELLOW;
    std::string G  = C::BGREEN;
    std::string g  = C::GREEN;
    std::string B  = C::BBLUE;
    std::string b  = C::BLUE;

    std::cout << b << "\n__________                              .__                      ";
    std::cout << b << "\n\\______   \\_____    _____ _____    ____ |  |__ _____    ____     ";
    std::cout << b << "\n |       _/\\__  \\  /     \\__  \\ _/ ___\\|  |  \\__  \\  /    \\    ";
    std::cout << b << "\n |    |   \\ / __ \\|  Y Y  \\/ __ \\  \\___|   Y  \\/ __ \\|   |  \\   ";
    std::cout << b << "\n |____|_  /(____  /__|_|  (____  /\\___  >___|  (____  /___|  /   ";
    std::cout << b << "\n        \\/      \\/      \\/     \\/     \\/     \\/     \\/     \\/    ";

    std::cout << b << "\n    .___                   "   << B << "__________.____    ___________________";
    std::cout << b << "\n  __| _/___________    ____"   << B << "\\______   \\    |   \\_____  \\__    ___/";
    std::cout << b << "\n / __ |\\_  __ \\__  \\  /    \\"  << B <<  "|     ___/    |    /   |   \\|    |   ";
    std::cout << b << "\n/ /_/ | |  | \\// __ \\|   |  \\" << B <<   "    |   |    |___/    |    \\    |   ";
    std::cout << b << "\n\\____ | |__|  (____  /___|  /" << B <<   "____|   |_______ \\_______  /____|   ";
    std::cout << b << "\n     \\/            \\/     \\/"  << B <<  "                 \\/       \\/         ";

    std::cout << B << "\n\n";

}


/*
 * Send the help-message to std::cout
 *
 **/
void console::Help(std::string name,std::string message) {

    std::cout << C::BRED  << message <<  "\n\n" ;
    std::cout << C::BWHITE  <<  "";
    std::cout << C::BWHITE  <<  "  Help:    " << C::BYELLOW << " $ ./deepBlackCoffee \n" ;
    std::cout << C::BWHITE  <<  "  Example: " << C::BGREEN  << " $ ./deepBlackCoffee \n" ;
    std::cout << C::BWHITE  <<  "\n" ;
    std::cout << C::BGREEN  <<  " " << C::BWHITE << "| " << C::BYELLOW << " \n" ;
    std::cout << C::BWHITE  <<  "\n" ;
}



/*
 * Show list of angles from the protein
 * and send to std::cout
 **/
void console::ShowAngles(std::string outputfile, std::vector<AnglePair> AP) {
    std::cout << C::BWHITE  <<    "\n";
    for(auto ap : AP) {
        std::cout << ap << "\n";
    }
    std::cout << C::BBLUE <<    "\n" << " > " << C::BBLUE << AP.size() << " tuples printed. ";

}



/*
 * Show "Menu-Items"
 * and wait for User input (Keypress [choice-chars] + [Enter] )
 *
 **/
char console::ShowChoices(std::string filename,std::string proteinname) {

    std::cout << C::BWHITE  <<    "\n" << " | Choose an option and press Enter: " << C::BGREEN << "| Protein: " << proteinname << C::YELLOW << " file: " << filename;
    std::cout << C::BWHITE  <<    "\n" << " | ";
    std::cout << C::BWHITE  <<    "\n" << " | " << C::BYELLOW << "1"   << "   Open PDB File";
    std::cout << C::BWHITE  <<    "\n" << " | " << C::BGREEN  << "2"   << "   Print Sequence with secondary structure assignment";
    std::cout << C::BWHITE  <<    "\n" << " | " << C::GREEN   << "3"   << "   Print structure assignments in percent";
    std::cout << C::BWHITE  <<    "\n" << " | " << C::RED     << "4"   << "   Print phi/psi angles";
    std::cout << C::BWHITE  <<    "\n" << " | " << C::RED     << "5"   << "   Create CSV File for Plot";
    std::cout << C::BWHITE  <<    "\n" << " | " << C::RED     << "ESC" << " Quit program";
    std::cout << C::RESET  <<     "\n\n > ";

    while (true) {
        std::string inp;
        std::cin >> inp;
        char i = inp.begin().operator*();
        if ( i == '1' || i == '2' || i == '3' || i == '4' || i == '5' || i == '\033' ) {return i;break;}
    }

}



/*
 *
 * Wait for User input (Keypress [y] + [Enter] )
 *
 **/
void console::pressY2continue() {
    std::cout << C::BBLUE   << "\n > press [y] + [ENTER] to continue ... ";
    while (true) {
        std::string inp;
        std::cin >> inp;
        if (inp.begin().operator*() == 'y' || inp.begin().operator*() == 'Y') {break;}
    }

}

#include <sstream>
#include <iomanip>
#include <vector>
#include "console.h"
#include "Color.h"

#define KB_UP 38
#define KB_DOWN 40
#define KB_LEFT 37
#define KB_RIGHT 38
#define KB_ESCAPE 27

#include <unistd.h>
#include <termios.h>

char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
    return (buf);
}


/*
* sends a big-font Ascii-Art-Header to std::cout
* */
void console::ShowHeader() {

    std::string H = C::BYELLOW;
    std::string C = C::YELLOW;
    std::string W = C::BWHITE;
    std::cout << "\n";
    std::cout << "\n" << H << "  _________.__              .__          __             .___  ";
    std::cout << "\n" << H << " /   _____/|__| _____  __ __|  | _____ _/  |_  ____   __| _/  ";
    std::cout << "\n" << H << " \\_____  \\ |  |/     \\|  |  \\  | \\__  \\   __\\/ __ \\ / __ |   ";
    std::cout << "\n" << H << " /        \\|  |  Y Y  \\  |  /  |__/ __ \\|  | \\  ___// /_/ |   ";
    std::cout << "\n" << H << "/_______  /|__|__|_|  /____/|____(____  /__|  \\___  >____ |   ";
    std::cout << "\n" << H << "        \\/          \\/                \\/          \\/     \\/   ";
    std::cout << "\n" << H << "   _____                              .__  .__                ";
    std::cout << "\n" << H << "  /  _  \\   ____   ____   ____ _____  |  | |__| ____    ____  ";
    std::cout << "\n" << H << " /  /_\\  \\ /    \\ /    \\_/ __ \\__  \\ |  | |  |/    \\  / ___\\ ";
    std::cout << "\n" << H << "/    |    \\   |  \\   |  \\  ___/ / __ \\|  |_|  |   |  \\/ /_/  >";
    std::cout << "\n" << H << "\\____|__  /___|  /___|  /\\___  >____  /____/__|___|  /\\___  / ";
    std::cout << "\n" << H << "        \\/     \\/     \\/     \\/     \\/             \\//_____/  ";
    std::cout << "\n";
    std::cout << "\n" << W << "          [ -- Please press ENTER to dive in -- ]  \n\n";

    while (true) {
        char a = getch();
        if (a == 10) { break; }
    }

}


/*
 *
 * send the help-message to std::cout
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








std::vector<std::string> console::helpText(int index) {

    std::vector<std::string> lines;

    switch (index) {
        case 0 : lines.push_back("\033[1;32m - Translation -                 ");
                 lines.push_back("                                           ");
                 lines.push_back(" a) translate Q and P to their             ");
                 lines.push_back("    center -> Qc,Pc                        ");
                 lines.push_back("                                           ");
            break;

        case 1 : lines.push_back("\033[1;32m - Matrix A, U and V -           ");
                 lines.push_back("                                           ");
                 lines.push_back(" b) calc Matrix A with translated Qc       ");
                 lines.push_back("    -> and Pc                              ");
                 lines.push_back(" c) calc JacobiSVD for Matrix U and V      ");
            break;

        case 2 : lines.push_back("\033[1;32m - Rotate Matrix R -             ");
                 lines.push_back("                                           ");
                 lines.push_back(" d) calc determinant for sign(x)           ");
                 lines.push_back(" e) compute rotate Matrix R                ");
                 lines.push_back("                                           ");
            break;

        case 3 : lines.push_back("\033[1;32m - RMSD -                        ");
                 lines.push_back("                                           ");
                 lines.push_back(" f) calc determinant for sign(x)           ");
                 lines.push_back(" e) compute rotate Matrix R                ");
                 lines.push_back("                                           ");
            break;

        case 4 : lines.push_back("\033[1;32m - Exit -                        ");
                 lines.push_back("                                           ");
                 lines.push_back("Are you finish an happy with               ");
                 lines.push_back("the results, close this program.           ");
                 lines.push_back("                                           ");
            break;

       default : lines.push_back("\033[1;32m -  -                            ");
                 lines.push_back("                                           ");
                 lines.push_back("                                           ");
                 lines.push_back("                                           ");
                 lines.push_back("                                           ");
            break;
    }

    return lines;

}








int console::ShowChoices(std::string file, int loop_count) {

    int cursor = 0;

    std::string border = " || ";
    // 0: no arrow ; 1: with arrow
    std::string arrow[2] = {"    " , " -> "};
    // 0: not marked bg-color ; 1: marked bg-color
    std::string marked[2] = {"\033[40m" , "\033[44m"};

    std::vector<std::string> choice_text = {
            " Translation                  ",
            " Matrices A, U and V          ",
            " Rotate Matrix R              ",
            " RMSD                         ",
            " Exit Program                 "};

    std::cout << C::BWHITE << " \033[41m" << "\033[33m" << "  Navigate: Arrow Keys [UP/DOWN] " << C::RESET << C::GREEN << " Proteins      : " << C::YELLOW << file << "\n";
    std::cout << C::BWHITE << " \033[41m" << "\033[33m" << "                    or [+] [-]   " << C::RESET << C::GREEN << " Residue count : " << C::BYELLOW << loop_count << "\n";
    std::cout << C::BWHITE << " \033[41m" << "\033[33m" << "  [Enter] Execute Item           " << C::RESET << C::GREEN << "   " << "\n";

    while (true) {

        // Show UI
        std::cout << "\n";
        /*line 1*/ std::cout << arrow[cursor == 0 ? 1 : 0] << marked[cursor == 0 ? 1 : 0] << choice_text[0] << C::RESET << border << helpText(cursor)[0] << "\n" << C::RESET;
        /*line 2*/ std::cout << arrow[cursor == 1 ? 1 : 0] << marked[cursor == 1 ? 1 : 0] << choice_text[1] << C::RESET << border << helpText(cursor)[1] << "\n" << C::RESET;
        /*line 3*/ std::cout << arrow[cursor == 2 ? 1 : 0] << marked[cursor == 2 ? 1 : 0] << choice_text[2] << C::RESET << border << helpText(cursor)[2] << "\n" << C::RESET;
        /*line 4*/ std::cout << arrow[cursor == 3 ? 1 : 0] << marked[cursor == 3 ? 1 : 0] << choice_text[3] << C::RESET << border << helpText(cursor)[3] << "\n" << C::RESET;
        /*line 5*/ std::cout << arrow[cursor == 4 ? 1 : 0] << marked[cursor == 4 ? 1 : 0] << choice_text[4] << C::RESET << border << helpText(cursor)[4] << "\n" << C::RESET;

        // Input Loop : Wait for [Arrow Keys] or [ESC]
        int mc = 0;
        char c[] = {0,0,0};
        while (true) {
            // input:
            char a = getch();
            // list multichars
            if (a == 27 || a == 91 || a == 65 || a == 66 || a == 10 || a == '+' || a == '-') {} else {mc = 0; c[0] = 0;c[1] = 0;c[2] = 0;continue;}
            if (mc > 2) {mc = 0;c[0] = 0;c[1] = 0;c[2] = 0;}
            c[mc] = a;mc++;

            // press '-' / '+'
            if ( a == '+' ) {
                cursor = abs((cursor + 1) % (int) choice_text.size());
                break;                 }
            if (a == '-') {
                cursor = abs((cursor - 1) % (int) choice_text.size());
                break;                 }

            // return Key
            if (a == 10) {
                if (cursor == (int)choice_text.size()-1) {return '\033';} else {
                return cursor; }}

            // check multichar
            if (c[0] == 27 && c[1] == 91 && c[2] == 65 ) {
                cursor = abs((cursor - 1) % (int) choice_text.size());
                break;                 }
            if (c[0] == 27 && c[1] == 91 && c[2] == 66 ) {
                cursor = abs((cursor + 1) % (int) choice_text.size());
                break;                 }

            //
        }

        // clear
        move(Left,100); std::cout << "                                                                          ";move(Left,100);move(Up,1);
        move(Left,100); std::cout << "                                                                          ";move(Left,100);move(Up,1);
        move(Left,100); std::cout << "                                                                          ";move(Left,100);move(Up,1);
        move(Left,100); std::cout << "                                                                          ";move(Left,100);

        // Return input key



    }

}

// move the Cursor in console s characters in the given direction. ( for overwrite console text )
void console::move(cdir direction,int s) {

    if (direction == Left)  { for (int i = 0 ; i <= s ; i++) { std::cout << "\033[1D"; } return; }
    if (direction == Right) { for (int i = 0 ; i <= s ; i++) { std::cout << "\033[1C"; } return; }
    if (direction == Up)    { for (int i = 0 ; i <= s ; i++) { std::cout << "\033[1A"; } return; }
    if (direction == Down)  { for (int i = 0 ; i <= s ; i++) { std::cout << "\033[1B"; } return; }
    return;

}


/*
 *
 * Wait for User input (Keypress [Enter] )
 *
 **/
void console::pressY2continue() {
    std::cout << C::BBLUE   << "\n > press [ENTER] to continue ... \n";
    while (true) {
        char a = getch();
        if (a == 10) { break; }
    }
    std::cout << C::RESET << "\n";
}

void console::linesClear(int i) {
    for (int n = 0 ; n < i ; n++) { move(Left,100); std::cout << "                                                                          ";move(Left,100);move(Up,1); }
    move(Left,100); std::cout << "                                                                          ";move(Left,100);
}


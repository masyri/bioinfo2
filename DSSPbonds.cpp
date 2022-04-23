//
// Created by manjaro on 22.04.22.
//

#include "DSSP.h"


/*
  Exercise b)

  Remove all H-Bonds != (i,i+3) , (i,i+4) , (i,i+5)

*/
void DSSP::removeHBonds() {
    
//  !!! noch nicht getestet ob es baut und funktioniert!!!

    IJ_Tuple bond = std::begin(result);

    while (bond != std::end(result)) { // iterate over the H-Bond-List 'result'

        // (i,j) = (NH-Groud.indicy = i , CO-Group.indicy = j)   <- Welche Gruppe ist i und welche j? ist das egal und es muss nur der Abstand stimmen?

        int i = bond.NH->indices;
        int j = bond.CO->indices;
        // würde diese Art von überprüfung nicht auch die Fälle (i,i+1)(i,i+2) akzeptieren?
        // zb. (1,3) -> abs(3-1)-3 = 2-3 = -1 < 3 --> wahr obwohl removed werden sollte
        bool distance = abs(j - i) - 3 < 3; 
        // 
        int abstand = abs(j - i);
        bool distance = abstand == 3 ||abstand == 4||abstand == 5;
        if (!distance) { 
                // delete this bond from result if j not i + 3 , i + 4 , i + 5
                bond = result.erase(bond);}
            else { ++bond;}
        }

}





/*
  Exercise c)

  compute Helices and send this to a file in Format:

  1   FAGIFKEIDHFLVAYILGPALIRHGTAITFIAEIFILASEACFIEADLF   <- result_AS;
    -----HHHHHHHH-------HHHHHHH---------HHHHHHHHHHHHH     <- result_Type;


*/
void DSSP::computeHelices(std::string file_out) {

std::vector<char> result_AS    = {'B','I','O','I','N','F','O'};
std::vector<char> result_Type  = {'-','-','H','H','-','H','-'};

// IMPLEMENT THIS



createAS_File(result_AS,result_Type,file_out);

}



/*
  Exercise c)

  create a file in Format:

  1   FAGIFKEIDHFLVAYILGPALIRHGTAITFIAEIFILASEACFIEADLF   <- result_AS;
    -----HHHHHHHH-------HHHHHHH---------HHHHHHHHHHHHH     <- result_Type;

*/
void DSSP::createAS_File(std::vector<char> AS, std::vector<char> TY,std::string file_out) {

    // bereits Getestet , Dateiausgabe funktioniert im richtigen Format

     if (TY.size() < AS.size()) {std::cout << "\nError createAS_File : TY smaller AS\n";return;}
    int counter50 = 0;
    int idx = 0;
    int step = 0;
    std::stringstream line1("");
    std::stringstream line2("");

    std::ofstream out;
    out.open (file_out);

    line1 << " " << "    1" << " ";
    line2 << " " << "     " << " ";

    for(char as : AS) {
        // Line Break:
        if (counter50 > 48) {
            out << line1.str() << "\n";
            out << line2.str() << "\n\n";
            std::stringstream number("");
            step += 50;
            number << std::setfill(' ') << std::setw(5) << step;
            line1.str("");
            line2.str("");
            line1 << " " << number.str()  << " ";
            line2 << " " << "     " << " ";

            counter50 = 0;

        }

        line1 << as;
        line2 << TY[idx];
        counter50++;
        idx++;
    }

    if (counter50 < 51) {
        out << line1.str() << "\n";
        out << line2.str() << "\n\n";}

    out.close();


}
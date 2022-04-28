//
// Created by manjaro on 22.04.22.
//

#include <BALL/STRUCTURE/peptides.h>
#include "DSSP.h"


/*
  Exercise b)

  Remove all H-Bonds != (i,i+3) , (i,i+4) , (i,i+5)

*/
void DSSP::removeHBonds() {

    int position = 0;

    for(IJ_Tuple bond : result){ // iterate over the H-Bond-List 'result'

        int i = bond.i;
        int j = bond.j;

        int abstand = abs(j - i);
        bool distance = abstand == 3 ||abstand == 4||abstand == 5;

        if (!distance) { 
                // delete this bond from result if j not i + 3 , i + 4 , i + 5
                result.erase(result.begin() + position);
        } else

            { position++;}

        }

}





/*
  Exercise c)

    Checks if the WSBB are 5,4,3 AS away from each other
    and checks if the NH and OH Groups from the H-bonds are 5,4,3 length away
    3-Helix(i, i + 2) := HBond(i − 1, i + 2) ∧ HBond(i, i + 3)
    4-Helix(i, i + 3) := HBond(i − 1, i + 3) ∧ HBond(i, i + 4)
    5-Helix(i, i + 4) := HBond(i − 1, i + 4) ∧ HBond(i, i + 5)

  compute Helices and send this to a file in Format:

  1   FAGIFKEIDHFLVAYILGPALIRHGTAITFIAEIFILASEACFIEADLF   <- result_AS;
    -----HHHHHHHH-------HHHHHHH---------HHHHHHHHHHHHH     <- result_Type;


*/
void DSSP::computeHelices(std::string file_out) {

    std::vector<char> result_AS;
    std::vector<char> result_Type;

    // Create List of
    BALL::ResidueIterator resit = S.beginResidue();
    for (; +resit ; ++resit) {
            result_AS.push_back(Peptides::OneLetterCode(resit->getName()));
            result_Type.push_back('-');
    }


    //iteration over bonds
    for(IJ_Tuple bond : result){

        int i = bond.NH->index;
        int j = bond.CO->index;
        // check the indieces from the other bonds
        for(IJ_Tuple bond2 : result){

            int i2 = bond2.NH->index;
            int j2 = bond2.CO->index;

            // schauen ob die Amonisäuren nachbarn sind
            if(i2-i == 1){
            
            // falls ja check ob die WSBB auch jeweils 5,4or3 auseinander liegen
            // Helix check
            if (j-i == 4 && j2-i2 == 4){
                // füg H zu beiden Aminosäuren hinzu     
                result_Type[i]  = 'H';
                result_Type[i2]  = 'H';

            } else if (j-i == 3 && j2-i2 == 3){
                // füg H zu beiden Aminosäuren hinzu
                result_Type[i]  = 'H';
                result_Type[i2]  = 'H';

            } else if (j-i == 2 && j2-i2 == 2){
                // füg H zu beiden Aminosäuren hinzu 
                result_Type[i]  = 'H';
                result_Type[i2]  = 'H';

            }
            }
        }
        
    }

    // Write results to file:
    createAS_File(result_AS,result_Type,file_out);

}








/*
  Exercise c)

  create a file in Format:

  1   FAGIFKEIDHFLVAYILGPALIRHGTAITFIAEIFILASEACFIEADLF   <- result_AS;
    -----HHHHHHHH-------HHHHHHH---------HHHHHHHHHHHHH     <- result_Type;

*/
void DSSP::createAS_File(std::vector<char> AS, std::vector<char> TY,std::string file_out) {

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

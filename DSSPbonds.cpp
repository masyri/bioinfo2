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
    int position = 0;
    for(IJ_Tuple bond :result){ // iterate over the H-Bond-List 'result'

        // (i,j) = (NH-Groud.indicy = i , CO-Group.indicy = j)   <- Welche Gruppe ist i und welche j? ist das egal und es muss nur der Abstand stimmen?

        int i = bond.NH->indices;
        int j = bond.CO->indices;
        // würde diese Art von überprüfung nicht auch die Fälle (i,i+1)(i,i+2) akzeptieren?
        // zb. (1,3) -> abs(3-1)-3 = 2-3 = -1 < 3 --> wahr obwohl removed werden sollte
        
        //bool distance = abs(j - i) - 3 < 3; 
        
        int abstand = abs(j - i);
        bool distance = abstand == 3 ||abstand == 4||abstand == 5;
        if (!distance) { 
                // delete this bond from result if j not i + 3 , i + 4 , i + 5
                result.erase(result.begin() + position);}
        }
    position++;

/*
int position = 0;
for(WSBB_Tuple bond : wsbb){
   
    int i = atoi(bond.i->getID().c_str());
    int j = atoi(bond.j->getID().c_str());

    int abstand = abs(j - i);
    cout << abstand << endl;
    bool distance = abstand == 3 ||abstand == 4||abstand == 5;
    if (!distance) { 
        // delete this bond from wsbb if j not i + 3 , i + 4 , i + 5
        wsbb.erase(wsbb.begin() + position);
    }
    position++;
}*/
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


// Initialisieren der beiden Listen damit alle Indexe der Liste schonmal existieren und 
// die '-' nur noch durch 'H' ersetzt werden müssen, falls eine WSBB existiert 
//
//
/*
foreach(AminoAcid AS : where_ever_molecules) { // <- wie kommt man an die Liste der AS? Eventuell über Residien? Residue sind die Aminosäuren

    result_AS.push_back(AS.toChar); // Hier ist eine Methode gesucht die die AS in einen Char umwandelt

    result_Type.push_back('-');

}
*/


// Checks if the WSBB are 5,4,3 AS away from eachother 
// and checks if the NH and OH Groups from the H-bonds are 5,4,3 lenght away
// 3-Helix(i, i + 2) := HBond(i − 1, i + 2) ∧ HBond(i, i + 3)
// 4-Helix(i, i + 3) := HBond(i − 1, i + 3) ∧ HBond(i, i + 4)
// 5-Helix(i, i + 4) := HBond(i − 1, i + 4) ∧ HBond(i, i + 5)

//iteration over bonds
for(IJ_Tuple bond : result){

    int i = bond.NH->indices;
    int j = bond.CO->indices;
    // check the indieces from the other bonds
    for(IJ_Tuple bond2 : result){

        int i2 = bond2.NH->indices;
        int j2 = bond2.CO->indices;

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

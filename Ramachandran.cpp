//
// Created by manjaro on 29.04.22.
//

#include "Ramachandran.h"
#include <BALL/KERNEL/system.h>
#include <BALL/FORMAT/PDBFile.h>
#include <BALL/STRUCTURE/secondaryStructureProcessor.h>
#include <BALL/STRUCTURE/fragmentDB.h>
#include <BALL/KERNEL/residueIterator.h>
#include <BALL/STRUCTURE/peptides.h>


/**
 *  R A M A C H A N D R A N - C O N S T R U C T O R
 *
 *  Builds a vector of aminoacids and this structure
 *
 * */
Ramachandran::Ramachandran(System Sys) {

    this->S = Sys;

    // iterate over proteins (getName)

    for (ProteinIterator Piter = S.beginProtein(); +Piter; ++Piter) {
        std::stringstream s("");
        s << S.getProtein(0)->getName();
        this->protein_name = s.str();
    }

    // iterate over residues for assigned secondary structures

    for (auto &iter: S.residues()){
        if (iter.isAminoAcid()){
            // Get Aminoacid Char
             auto code = Peptides::OneLetterCode(iter.getName());
            // Get assigned structure
             auto SecStruct = iter.getSecondaryStructure()->getType();
            // Decision SS Type
             switch (SecStruct) {
               case SecondaryStructure::HELIX:             structures.push_back(StructPair(&code,'H')); helices++;  break;
               case SecondaryStructure::COIL:              structures.push_back(StructPair(&code,'-'));             break;
               case SecondaryStructure::TURN:              structures.push_back(StructPair(&code,'L')); loops++;    break;
               case SecondaryStructure::STRAND:            structures.push_back(StructPair(&code,'S')); sheets++;   break;
               case SecondaryStructure::UNKNOWN:           structures.push_back(StructPair(&code,'U'));             break;
               default:                                    structures.push_back(StructPair(&code,'-'));             break;
             }
             // count of all residues
             aminoacids++;
        }
    }
    // end

}




/**
 *  R A M A C H A N D R A N - A N G L E S
 *
 *  Returns a vector of many vectors of Phi and Psy-Angels between
 *  residues from the protein.
 *
 *  @return angle-vector
 *
 * */
vector <AnglePair> Ramachandran::getTorsionAngels() {

    vector<AnglePair> collection = {};

    for (ResidueIterator iter = S.beginResidue() ; +iter ; ++iter) {
        if(iter->getTorsionPhi() != 0 && iter->getTorsionPsi() != 0) {
            double psi = iter->getTorsionPsi().toDegree();
            double phi = iter->getTorsionPhi().toDegree();
            collection.emplace_back(phi,psi);
        }

    }
    return collection;
}




/**
 *  R A M A C H A N D R A N - S E Q U E N C E S
 *
 *  Create a double-lined string of AminoAcid-Name and their secondary structure and statistics
 *
 *  @return formatted string
 *
 * */
void Ramachandran::printSequences() const {

    int counter50 = 0;
    int idx = 0;
    int step = 0;
    std::stringstream line1("");
    std::stringstream line2("");

    line1 << C::BBLUE << " " << "   1" << "| "<< C::RESET;
    line2 << C::BBLUE << " " << "    " << "| "<< C::RESET;

    for(const auto& tuple : structures) {
        // Line Break:
        if (counter50 > 48) {
            std::cout  << line1.str() << "\n";
            std::cout  << line2.str() << "\n\n";
            std::stringstream number("");
            step += 50;
            number << std::setfill(' ') << std::setw(4) << step;
            line1.str("");
            line2.str("");
            line1 << C::BBLUE << " " << number.str()  << "| "<< C::RESET;
            line2 << C::BBLUE << " " << "    " << "| "<< C::RESET;

            counter50 = 0;

        }

        line1 << C::BWHITE << tuple.name << C::RESET;

        if (tuple.type == 'H') {line2 << C::BBLUE;} else if (tuple.type == 'S') {line2 << C::BGREEN;} else if (tuple.type == 'L') {line2 << C::BYELLOW;} else {line2 << C::BRED;}
        line2 << tuple.type << C::RESET;
        counter50++;
        idx++;
    }

    if (counter50 < 51) {
        std::cout  << line1.str() << "\n";
        std::cout  << line2.str() << "\n\n";}


}





/**
 *  R A M A C H A N D R A N - S T A T I S T I C S
 *
 *  Print statistics in percent about their secondary structure
 *
 *  @return formatted string
 *
 * */
void Ramachandran::printStats() const {

    std::cout << C::RESET    << "\n";
    std::cout << C::BGREEN   << "\n   Sequence length " << C::BWHITE << " :   " << C::GREEN    << aminoacids ;
    std::cout << C::BYELLOW  << "\n   Loops           " << C::BWHITE << " :   " << C::YELLOW   << 100.0 * (double)loops   / (double)aminoacids << " %";
    std::cout << C::BBLUE    << "\n   Helices         " << C::BWHITE << " :   " << C::BLUE     << 100.0 * (double)helices / (double)aminoacids << " %";
    std::cout << C::BMAGENTA << "\n   Sheets          " << C::BWHITE << " :   " << C::BMAGENTA << 100.0 * (double)sheets  / (double)aminoacids << " %";
    std::cout << C::RESET    << "\n";

}





/**
 *  R A M A C H A N D R A N - F I L E
 *
 *  Create a CSV FIle with the phi and psi angles
 *
 *  @filename filename for output
 *  @AP       vector of angles
 *  @return   a file in *.csv - format
 *
 * */
void Ramachandran::anglesToFile(const string& filename, std::vector<AnglePair> AP) {

    ofstream file;
    file.open (filename);
    file << "\"phi\";\"psi\"";

    for(auto ap : AP) {
        file << "\n" << ap.phi << ";" << ap.psi;
    }

    file.close();
}



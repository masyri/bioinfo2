//
// Created by manjaro on 29.04.22.
//

#include "Ramachandran.h"
#include <BALL/STRUCTURE/peptides.h>


/**
 *  R A M A C H A N D R A N - C O N S T R U C T O R
 *
 *  Builds a vector of aminoacids and this structure
 *
 * */
Ramachandran::Ramachandran(System Sys) {

    this->S = S;

    // iterate over proteins

    for (ProteinIterator Piter = S.beginProtein(); +Piter; ++Piter) {

        protein_name = Piter->getID(); // store the name of this protein

        // iterate over secondary structures

        for (SecondaryStructureIterator SSiter = Piter->beginSecondaryStructure(); +SSiter; ++SSiter) {

            // ## search for AminoAcid-Letter

            Peptides::OneLetterAASequence oneLetter = getCodeAA(SSiter);

            string code = oneLetter.c_str();

            // if the founded AS == ? -> continue
            if (code.empty()) { continue; }

            // ## search for AminoAcid-Structure

            switch (SSiter->getType()) {
                case SecondaryStructure::HELIX:   structures.push_back(StructPair(code,'H')); helices++;  break;
                case SecondaryStructure::COIL:
                case SecondaryStructure::TURN:    structures.push_back(StructPair(code,'L')); loops++;    break;
                case SecondaryStructure::STRAND:  structures.push_back(StructPair(code,'S')); sheets++;   break;
                case SecondaryStructure::UNKNOWN: structures.push_back(StructPair(code,'U'));             break;
                default:
                    break;
            }
            ++aminoacids;
        }
    }
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

    collection.push_back(AnglePair(0.23,1));
    collection.push_back(AnglePair(3.23,2));
    collection.push_back(AnglePair(10.23,3));
/*
    for (ResidueIterator iter = S.beginResidue() ; +res ; ++res) {
        if(res->getTorsionPhi() != 0 && res->getTorsionPsi() != 0) {
            double psi = iter->getTorsionPsi().toDegree();
            double phi = iter->getTorsionPhi().toDegree();
            collection.emplace_back(phi,psi);
        }

    }

*/


    return collection;
}



/**
 *  R A M A C H A N D R A N - O U T P U T
 *
 *  Create a double-lined string of AminoAcid-Name and their secondary structure and statistics
 *
 *  @return formatted string
 *
 * */
ostream &operator<<(ostream &os, const Ramachandran &SC) {

    os << C::BWHITE;
    for (auto &aa : SC.structures) {
      os << aa.name;
    }

    os << C::RESET << "\n";
    for (auto &ty : SC.structures) {
        if (ty.type == 'H') {os << C::BBLUE;} else if (ty.type == 'S') {os << C::BGREEN;} else if (ty.type == 'L') {os << C::BYELLOW;} else {os << C::BRED;}
        os << ty.type;
    }

    os << C::RESET    << "\n";
    os << C::BGREEN   << "\n   Sequence length " << C::BWHITE << " :   " << C::GREEN    << SC.aminoacids ;
    os << C::BYELLOW  << "\n   Loops           " << C::BWHITE << " :   " << C::YELLOW   << 100.0 * (double)SC.loops   / (double)SC.aminoacids << " %";
    os << C::BBLUE    << "\n   Helices         " << C::BWHITE << " :   " << C::BLUE     << 100.0 * (double)SC.helices / (double)SC.aminoacids << " %";
    os << C::BMAGENTA << "\n   Loops           " << C::BWHITE << " :   " << C::BMAGENTA << 100.0 * (double)SC.loops   / (double)SC.aminoacids << " %";
    os << C::RESET    << "\n";

    return os;
}






/**
 *  R A M A C H A N D R A N - C O D E
 *
 *  Create a string of one-letter-codes
 *
 *  @return one letter code
 *
 * */
Peptides::OneLetterAASequence Ramachandran::getCodeAA(SecondaryStructureIterator &begin) {

    Residue *f(begin->getResidue(0));
    Peptides::OneLetterAASequence aa_seq;
    /*
    int c = 1;
    while (fst_res != nullptr) {
        if(Peptides::OneLetterCode(f->getName())!='?') {
            aa_seq += Peptides::OneLetterCode(f->getName());

        }
        fst_res = (begin->getResidue(c)); ++c;
    }*/
    return aa_seq;

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
void Ramachandran::anglesToFile(string filename, std::vector<AnglePair> AP) {

    ofstream file;
    file.open (filename);
    file << "\"phi\";\"psi\"";

    for(auto ap : AP) {
        file << "\n" << ap.phi << ";" << ap.psi;
    }

    file.close();
}



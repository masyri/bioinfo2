//
// Created by manjaro on 12.05.22.
//

#include "CCP.h"


/*
   
   There are no bugs, only features ;-)
   Otherwise, these are digital life forms with family and children, 
   who also have a right to live their beautiful life in this beautiful code. ;-) 
                     
     \ o/\o /
   --- |  | ---         
       /\/\                
      /    \


*/


Occurrence CCP::createOccurrenceMatrixFromFiles(vector<string> files) {

    Occurrence O;

    int all_amino_count = 0;
    int unknowns = 0;

    // Store all Amino from all files

    for (string file : files) {

        int id = 0;
        

        vector<AminoTuple> aminos;

        vector<AminoTuple> compare;

        // == open file

        PDBFile meop(file, ios::in);
        System S;
        meop >> S;
        int index = 0;

        // == iterate over all proteins of the system
        for(ProteinIterator p_iter = S.beginProtein(); +p_iter; ++p_iter) {

            // ## get protein
            Protein *protein = (S.getProtein(index));
            index++;

            // ## iterate over proteins

            for (ResidueIterator iter = protein->beginResidue(); +iter; ++iter) {

                if(iter->isAminoAcid()){ 

                    // get AminoAcid Type

                    auto code = Peptides::OneLetterCode(iter->getName());
                    AA amino = char2Amino(code);
                    if (amino == Unknown) {unknowns++;}

                    // get position

                    Atom  *  CA       = iter->getAtom("CA");
                    if (CA == nullptr) {cout << "null";id++;continue;}
                    Vector3 position  = CA->getPosition();


                    // insert in List (int id , AA amino , Vector3 position )
                    AminoTuple a(id,amino,position);
                    AminoTuple b(id,amino,position);
                    aminos.push_back(a);
                    compare.push_back(b);
                    id++;all_amino_count++;



                }
            }
        }
    

    // Check all stored aminos

    for (AminoTuple as : aminos) {

        // -- counter for contacts
        int contacts = 0;

        // compare with all atoms
        for (AminoTuple comp : compare) {
            // get distance
            double dist = abs(as.position.getDistance(comp.position));
            // if not same atom
            if (as.id != comp.id && dist <= 7 ) {
                contacts++;
                if (comp.amino == Unknown) {O.contact_unknowns++;}

            } 

        }

        // statistics

        if (contacts == 0) {O.zerocontact_residues++;} else {O.near_residues++;}

        // insert occurrence

        O.insert(as.amino,contacts);

    } 

    // end file loop

    }

    // Store Statistics

    O.all_residues = all_amino_count;
    O.amino_unknown = unknowns;

    // Return

    return O;
}





















bool CCP::distance(Atom A, Atom B, double max) {

double dist = A.getDistance(B);
if (dist <= max) return true;
return false;

}
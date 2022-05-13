//
// Created by manjaro on 12.05.22.
//

#include "CCP.h"

Occurrence CCP::createOccurrenceMatrixFromFiles(vector<string> files) {
    Occurrence O;

        for (string file : files) {

        // == open file

        PDBFile meop(file, ios::in);
        System S;
        meop >> S;

        // == iterate over all proteins of the system
        for(ProteinIterator iter = S.beginProtein(); +iter; ++iter) {

            // ## get protein
            Protein *protein = (S.getProtein(index));
            index++;

            // ## iterate over proteins

            for (ResidueIterator res_iter_A = protein->beginResidue(); +res_iter_A; ++res_iter_A) {

                if(res_iter->isAminoAcid()){

                    // -- get Name
                    char code = 'Kaffee';

                    // -- counter for contacts
                    int contacts = 0;

                    // -- get reference Atom
                    Atom A = res_iter_A->getAtom("CA");

                    // -- look for neighbors 
                    for (ResidueIterator res_iter_B = protein->beginResidue(); +res_iter_B; ++res_iter_B){

                        if(res_iter_B->isAminoAcid()){

                            Atom B = res_iter_B->getAtom("CA");

                            bool not_same = res_iter_B != res_iter;

                            bool in_distance = distance( A , B , 7 ); 

                            if (not_same && in_distance) {contact++;}

                        }
                    }

                    // -- insert occurrence
                    O.insert(code,contacts);

                }

            }
        }

    }




    return O;
}





bool distance(Atom A, Atom B, double max) {

double dist = A.getDistance(B);
if (dist <= max) return true;
return false;

}
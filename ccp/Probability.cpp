//
// Created by manjaro on 12.05.22.
//

#include "Probability.h"




Probability::Probability(Occurrence occur) {

    this->matrix = Matrix<double>(21,occur.getColumnCount(),0);

    for (int amino = 0 ; amino < 20 ; amino++) {
        for (int k = 0 ; k < occur.getColumnCount() ; k++) {

            // extract occurences:
            double occurrences = occur.getValue(amino,k);

            // count residues
            AA AminoAcid = static_cast<AA>(amino);
            double N   = occur.countResidues();
            double N_a = occur.countResidues(AminoAcid);
            double N_k = occur.countResidues(k);

            // calc N_ak
            double N_ak = (N_a * N_k) / N ;

            // calc W_ak
            double W_ak = occurrences / N_ak;

            // set probability
            matrix.setValue(amino,k,W_ak);

        }
    }
}

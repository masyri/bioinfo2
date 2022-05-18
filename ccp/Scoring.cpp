//
// Created by manjaro on 12.05.22.
//

#include <valarray>
#include "Scoring.h"



double Scoring::Sak(double Wak, double Nak) {

    double val = Wak;

    if (Wak != 0) {val = -log(Wak);  this->vallog++;return val;}
    if (Nak == 0) {val = -500; this->valn500++; return val;}
    this->val500++;
    return 500;

}




Scoring::Scoring(Occurrence occur, Probability prob) {

    this->matrix = Matrix<double>(21,occur.getColumnCount(),0);

    for (int amino = 0 ; amino < 20 ; amino++) {
        for (int k = 0 ; k < occur.getColumnCount() ; k++) {

            // count residues
            AA AminoAcid = static_cast<AA>(amino);

            double N_a = occur.countResidues(AminoAcid);
            double N_k = occur.countResidues(k);

            // div
            double N_ak = (N_a * N_k) ;

            // get
            double W_ak = prob.getValue(amino,k);

            // Sak
            double S_ak = Sak(W_ak,N_ak);

            // set score
            matrix.setValue(amino,k,S_ak);

        }
    }





}

//
// Created by manjaro on 02.06.22.
//

#ifndef RMSD_H
#define RMSD_H


#include "Space.h"
#include "../matrix/Matrix.h"

class RMSD {

public:

    RMSD() = default;

    Matrix<double> calcMatrix();

    double formula();
    double formulaR(MatrixXf xf);

    Space P;  // Original P
    Space Q;  // Original Q
    Space Pc; // Centered P
    Space Qc; // Centered Q

    static Space getTestSetP();
    static Space getTestSetQ();

};


#endif //RMSD_H

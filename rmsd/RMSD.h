//
// Created by manjaro on 02.06.22.
//

#ifndef RMSD_H
#define RMSD_H


#include "Space.h"
#include "../matrix/Matrix.h"
#include <limits>
#include <Eigen/Core>
#include "Eigen/Jacobi"

class RMSD {

public:

    RMSD() = default;

    // a)

    /*Translation Methods in Space.h*/

    // b)

    Matrix<double> calcMatrix();

    // c)

    void JacobiUSV();

    // d)

    double signDet();

    int sign(double determinant);

    // e)

    void rotateR(int sign);

    // f)

    double formula();
    double formulaR(MatrixXf xf);

    // Matrices

    MatrixXf A = MatrixXf::Identity(3,3);
    MatrixXf U = MatrixXf::Identity(3,3);
    MatrixXf V = MatrixXf::Identity(3,3);
    MatrixXf R = MatrixXf::Identity(3,3);

    // Coordinate Spaces

    Space P;  // Original P
    Space Q;  // Original Q
    Space Pc; // Centered P
    Space Qc; // Centered Q

    // Tests Sets

    static Space getTestSetP();
    static Space getTestSetQ();

};


#endif //RMSD_H

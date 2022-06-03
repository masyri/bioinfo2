//
// Created by manjaro on 02.06.22.
//

#include "RMSD.h"








// Spaltenvektor mal Zeilenvektor
Matrix<double> matrixmultiplication(double x1, double x2 ,double x3, double y1 , double y2 ,double y3) {

    Matrix<double> M(3,3,0);
    M.setValue(0,0,x1*y1);  M.setValue(0,1,x1*y2);   M.setValue(0,2,x1*y3);
    M.setValue(1,0,x2*y1);  M.setValue(1,1,x2*y2);   M.setValue(1,2,x2*y3);
    M.setValue(2,0,x3*y1);  M.setValue(2,1,x3*y2);   M.setValue(2,2,x3*y3);
    return M;

}





double determinante3x3(Matrix<double> M) {

double a = M.getValue(0,0) * M.getValue(0,0) * M.getValue(0,0);
double b = M.getValue(0,0) * M.getValue(0,0) * M.getValue(0,0);
double c = M.getValue(0,0) * M.getValue(0,0) * M.getValue(0,0);

double d = M.getValue(0,0) * M.getValue(0,0) * M.getValue(0,0);
double e = M.getValue(0,0) * M.getValue(0,0) * M.getValue(0,0);
double f = M.getValue(0,0) * M.getValue(0,0) * M.getValue(0,0);

}







Matrix<Matrix<double>> RMSD::calcMatrix() {

    int cols = this->Pc.positions.size();
    int rows = this->Qc.positions.size();
    int row = 0;
    double frac = 1.0 / cols;

    Matrix<Matrix<double>> M( rows , cols , Matrix<double>(3,3,0) );

    for (Position pc : this->Pc.positions) {
    int col = 0;
    for (Position qc : this->Qc.positions) {
        M.setValue(row,col,matrixmultiplication(frac * pc.x, frac * pc.y, frac * pc.z, frac * qc.x, frac * qc.y, frac * qc.z));
        col++;
    }
    row++;
    }
    return M;

}





Space RMSD::getTestSetP() {
    Space S;
    S.addPosition("P.01",-4,-1,7);
    S.addPosition("P.02",-1,-2,7);
    S.addPosition("P.03",-8,4,7);
    S.addPosition("P.04",-5,4,5);
    S.addPosition("P.05",-1,-2,11);
    S.addPosition("P.06",-3,2,6);
    return S;
}

Space RMSD::getTestSetQ() {
    Space S;
    S.addPosition("Q.01",1,2,3);
    S.addPosition("Q.02",1,1,6);
    S.addPosition("Q.03",1,9,-1);
    S.addPosition("Q.04",3,7,2);
    S.addPosition("Q.05",-3,1,6);
    S.addPosition("Q.06",2,5,1);
    return S;
}

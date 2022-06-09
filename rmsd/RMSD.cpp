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

// Spaltenvektor mal Zeilenvektor
Matrix<double> matrixaddition3x3(Matrix<double> mat1, Matrix<double> mat2) {

    Matrix<double> M(3,3,0);
    M.setValue(0,0,mat1.getValue(0,0)+mat2.getValue(0,0));
    M.setValue(0,1,mat1.getValue(0,1)+mat2.getValue(0,1));
    M.setValue(0,2,mat1.getValue(0,2)+mat2.getValue(0,2));
    M.setValue(1,0,mat1.getValue(1,0)+mat2.getValue(1,0));
    M.setValue(1,1,mat1.getValue(1,1)+mat2.getValue(1,1));
    M.setValue(1,2,mat1.getValue(1,2)+mat2.getValue(1,2));
    M.setValue(2,0,mat1.getValue(2,0)+mat2.getValue(2,0));
    M.setValue(2,1,mat1.getValue(2,1)+mat2.getValue(2,1));
    M.setValue(2,2,mat1.getValue(2,2)+mat2.getValue(2,2));
   return M;

}











Matrix<double> RMSD::calcMatrix() {

    int cols = this->Pc.positions.size();
    int rows = this->Qc.positions.size();
    int row = 0;
    double frac = 1.0 / cols;

    Matrix<double> M( rows , cols , 0 );

    for (Pos pc : this->Pc.positions) {
    int col = 0;
    for (Pos qc : this->Qc.positions) {
        Matrix<double> m( rows , cols , 0 );
        m = matrixmultiplication(frac * pc.x, frac * pc.y, frac * pc.z, frac * qc.x, frac * qc.y, frac * qc.z);
        M = matrixaddition3x3(M,m);
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

double RMSD::formula() {

    int l = Pc.positions.size();
    double sum = 0;

    for (Pos pc : Pc.positions) {
        for (Pos qc : Qc.positions) {
            double a = (qc.x - pc.x) * (qc.x - pc.x);
            double b = (qc.y - pc.y) * (qc.y - pc.y);
            double c = (qc.z - pc.z) * (qc.z - pc.z);
            double res = a + b + c;
            sum +=res * (1/l);
        }

    }
    return sqrt(sum);
}

double RMSD::formulaR(MatrixXf xf) {

    int l = Pc.positions.size();
    double sum = 0;
    Matrix<double> mat(3,3,0);
    mat = mat.convert_back(xf);
    this->Qc.matrixvector(mat);

    for (Pos pc : Pc.positions) {
        for (Pos qc : Qc.positions) {
            double a = (qc.x - pc.x) * (qc.x - pc.x);
            double b = (qc.y - pc.y) * (qc.y - pc.y);
            double c = (qc.z - pc.z) * (qc.z - pc.z);
            double res = a + b + c;
        }
    }
    return sum;
}
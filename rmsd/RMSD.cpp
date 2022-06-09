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



/**
 * @brief Adds two matrices of dimension 3x3
 * 
 * @param mat1 
 * @param mat2 
 * @return Matrix<double> 3x3
 */
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













/**
 * @brief Exercise b)
 * 
 * calc Matrix A
 * 
 * @return Matrix<double> 
 */
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




/**
 * @brief Exercise c)
 * 
 * calc Matrix U and V
 * 
 */
void RMSD::JacobiUSV() {

    Matrix<double> mat_A = calcMatrix();
    this->A = mat_A.convert();

    //  Eigen::JacobiSVD<Eigen::MatrixXf /*Eigen::ComputeFullU | Eigen::ComputeFullV*/> svd(this->A);
    //  this->U = svd.matrixU();
    //  this->V = svd.matrixV();

}





/**
 * @brief Exercise d)
 * 
 * calc determinant of U and V for sign-value
 * 
 * @return double determinant
 */
double RMSD::signDet() {
    return (this->V * this->U.transpose()).determinant();
}



/**
 * @brief Exercise d)
 * 
 * calc rotate matrix value sign(x)
 * 
 * @param determinant set value with method "signDet()"
 * @return int value for rotate matrix
 */
int RMSD::sign(double determinant) {
    int sign = 99;
    if (determinant > 0) {sign = 1;}
    if (determinant < 0) {sign = -1;}
    if (determinant == 0) {sign = 0;}
    return sign;
}




/**
 * @brief Exercise e)
 * 
 * Calc rotate matrix from the matrices V U and the identity matrix with the sign value
 *  
 * @param sign set value with method "sign(double determinant)"
 */
void RMSD::rotateR(int sign) {
        this->R(2,2) = sign;
        this->R = this->V * this->R * this->U.transpose();
}




/**
 * @brief Exercise f)
 * 
 * Formula for RMSD
 * 
 * @return double 
 */
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




/**
 * @brief Exercise f)
 * 
 * Formula for RMSD with rotate matrix
 * 
 * @return double 
 */
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
            sum += a + b + c;
        }
    }
    return sum;
}









/**
 * @brief Test Set P
 * 
 * @return Space P
 */
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


/**
 * @brief Test Set Q
 * 
 * @return Space Q
 */
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
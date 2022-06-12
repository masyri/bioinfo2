//
// Created by manjaro on 29.04.22.
//


#include "console/console.h"
#include "console/Color.h"
#include "matrix/Matrix.h"
#include "rmsd/RMSD.h"
#include "Eigen/Jacobi"
#include "BALL/MATHS/vector3.h"

#include <iostream>
#include <fstream>

#include <sstream>

#include <limits>
#include <Eigen/Core>

using namespace std;



int main(int argc, char* argv[])
{
    
    // ## Program variables

    RMSD rmsd;
    Space P = RMSD::getTestSetP();
    Space Q = RMSD::getTestSetQ();
    rmsd.P = P;
    rmsd.Q = Q;
    rmsd.Pc = P;
    rmsd.Qc = Q;


    // ## The 'endless' loop
    while (true) {

        char chosen = console::ShowChoices("2",6);


        // ### Translation###
        if (chosen == 0) {
            std::cout << C::BBLUE   <<    "\n" << " > Translation ...\n";

            Vector3 midP = rmsd.Pc.calcCenterCoordinate();
            Vector3 midQ = rmsd.Pc.calcCenterCoordinate();

            std::cout << C::BBLUE   <<    "\n Protein P input : \n";rmsd.P.print();
            std::cout << C::BBLUE   <<    "\n Protein Q input : \n";rmsd.Q.print();

            std::cout << C::BBLUE   <<    "\n\n Center P : " << midP;
            std::cout << C::BBLUE   <<      "\n Center Q : " << midQ << "\n";

            rmsd.Pc.moveCenterCoordinate(midP);
            rmsd.Qc.moveCenterCoordinate(midQ);

            std::cout << C::BBLUE   <<    "\n Protein P centered : \n"; rmsd.Pc.print();
            std::cout << C::BBLUE   <<    "\n Protein Q centered : \n";rmsd.Qc.print();

            std::cout << C::BBLUE   <<    "\n";

            console::pressY2continue();
            continue;
        }


        // ### Matrix A ###
        if (chosen == 1) {
            std::cout << C::BBLUE   <<    "\n" << " > Matrix A, U, V ...\n";

            Vector3 midP = rmsd.Pc.calcCenterCoordinate();
            Vector3 midQ = rmsd.Pc.calcCenterCoordinate();

            rmsd.Pc.moveCenterCoordinate(midP);
            rmsd.Qc.moveCenterCoordinate(midQ);

            Matrix<double> mat = rmsd.calcMatrix();

            std::cout << C::BBLUE << "\n";

            rmsd.JacobiUSV();

            std::cout << C::BWHITE << "\n\n Matrix A: \n" << C::BBLUE << rmsd.A;
            std::cout << C::BWHITE << "\n\n Matrix U: \n" << C::BBLUE << rmsd.U;
            std::cout << C::BWHITE << "\n\n Matrix V: \n" << C::BBLUE << rmsd.V;


            console::pressY2continue();
            continue;
        }


        // ### sign(x) and rotate Matrix ###
        if (chosen == 2) {
            std::cout << C::BBLUE   <<    "\n" << " > sign(x) and rotate Matrix ...\n";

            Vector3 midP = rmsd.Pc.calcCenterCoordinate();
            Vector3 midQ = rmsd.Pc.calcCenterCoordinate();

            rmsd.Pc.moveCenterCoordinate(midP);
            rmsd.Qc.moveCenterCoordinate(midQ);

            Matrix<double> mat = rmsd.calcMatrix();

            std::cout << C::BBLUE << "\n";

            rmsd.JacobiUSV();

            std::cout << C::BWHITE << "\n\n Matrix A: \n" << C::BBLUE << rmsd.A;
            std::cout << C::BWHITE << "\n\n Matrix U: \n" << C::BBLUE << rmsd.U;
            std::cout << C::BWHITE << "\n\n Matrix V: \n" << C::BBLUE << rmsd.V;

            double det = rmsd.signDet();

            int sign = rmsd.sign(det);

            rmsd.rotateR(sign);

            std::cout << C::BWHITE << "\nDeterminant :" << C::BBLUE << det << " -> sign :" << sign;

            std::cout << C::BWHITE << "\n\n Matrix R: \n" << C::BBLUE << rmsd.R;

            console::pressY2continue();
            continue;
        }


        // ### RMSD ###
        if (chosen == 3) {
            std::cout << C::BBLUE   <<    "\n" << " > RMSD ...\n";

            Vector3 midP = rmsd.Pc.calcCenterCoordinate();
            Vector3 midQ = rmsd.Pc.calcCenterCoordinate();

            rmsd.Pc.moveCenterCoordinate(midP);
            rmsd.Qc.moveCenterCoordinate(midQ);

            Matrix<double> mat = rmsd.calcMatrix();

            std::cout << C::BBLUE << "\n";

            rmsd.JacobiUSV();

            double det = rmsd.signDet();

            int sign = rmsd.sign(det);

            rmsd.rotateR(sign);

            rmsd.formula();
            rmsd.formulaR(rmsd.R);

            std::cout << C::BBLUE   <<    "\n Protein P optimum : \n"; rmsd.Pc.print();
            std::cout << C::BBLUE   <<    "\n Protein Q optimum : \n"; rmsd.Qc.print();

            console::pressY2continue();
            continue;
        }


        // ### break the loop and close the program ###
        if (chosen == '\033') {break;}

    }

    std::cout << C::BRED   <<    "\n" << " > Program aborted.\n" << C::RESET;

    return 1;
}



#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/molecule.h>
#include <BALL/KERNEL/atom.h>
#include <BALL/KERNEL/bond.h>
#include <BALL/KERNEL/PTE.h>
#include <BALL/STRUCTURE/secondaryStructureProcessor.h>
#include <BALL/STRUCTURE/fragmentDB.h>
#include <BALL/STRUCTURE/peptides.h>
#include <BALL/FORMAT/PDBFile.h>
#include <string>
#include <experimental/filesystem>
#include "../rmsd/Space.h"
#include "../rmsd/RMSD.h"

TEST(SPACE,getCenter) {
    
    Space d;
    
    d.addPosition("a",4,0,0);
    d.addPosition("a",8,0,0);
    d.addPosition("a",-4,0,0);
    d.addPosition("a",-8,0,0);

    d.addPosition("a",0,4,0);
    d.addPosition("a",0,8,0);
    d.addPosition("a",0,-4,0);
    d.addPosition("a",0,-8,0);

    d.addPosition("a",0,0,4);
    d.addPosition("a",0,0,8);
    d.addPosition("a",0,0,-4);
    d.addPosition("a",0,0,-8);

BALL::Vector3 center = d.calcCenterCoordinate(); // -> (0,0,0)
    
EXPECT_TRUE(false);

}





TEST(SPACE,MoveCenter) {
/*
    Space S;

    S.addPosition("O",3,3,2);   // -> (0,0,0)
    S.addPosition("a",3,5,-3);  // -> (0,2,-5)
    S.addPosition("b",3,2,4);   // -> (0,-1,2)
    S.addPosition("c",-2,-2,2); // -> (-5,-5,0)
    S.addPosition("z",0,0,0);   // -> (-3,-3,-2)
    
    Vector3 newCenter(3,3,2);
       
    S.moveCenterCoordinate(newCenter);

    Pos p_1 = S.positions[0];
    Pos p_2 = S.positions[1];
    Pos p_3 = S.positions[2];
    Pos p_4 = S.positions[3];
    Pos p_5 = S.positions[4];

EXPECT_TRUE(p_1.index == "0" && p_1.x == 0 && p_1.y == 0 && p_1.z == 0 );
*/
EXPECT_TRUE(false);

}

TEST(RMSD,calcMatrix) {
    RMSD rmsd;
    Space P = RMSD::getTestSetP();
    Space Q = RMSD::getTestSetQ();
    rmsd.P = P;
    rmsd.Q = Q;
    rmsd.Pc = P;
    rmsd.Qc = Q;

    Matrix<double> M( 3 , 3 , 0 );
    M.setValue(0,0,-3.05556);
    M.setValue(0,1,-15.2778);
    M.setValue(0,2,-10.3889);
    M.setValue(1,0,0.694444);
    M.setValue(1,1,3.47222);
    M.setValue(1,2,2.36111);
    M.setValue(2,0,5.97222);
    M.setValue(2,1,29.8611);
    M.setValue(2,2,20.3056);

    EXPECT_EQ(M.getValue(0,0), rmsd.calcMatrix().getValue(0,0));
    EXPECT_EQ(M.getValue(0,1), rmsd.calcMatrix().getValue(0,1));
    EXPECT_EQ(M.getValue(0,2), rmsd.calcMatrix().getValue(0,2));
    EXPECT_EQ(M.getValue(1,0), rmsd.calcMatrix().getValue(1,0));
    EXPECT_EQ(M.getValue(1,1), rmsd.calcMatrix().getValue(1,1));
    EXPECT_EQ(M.getValue(1,2), rmsd.calcMatrix().getValue(1,2));
    EXPECT_EQ(M.getValue(2,0), rmsd.calcMatrix().getValue(2,0));
    EXPECT_EQ(M.getValue(2,1), rmsd.calcMatrix().getValue(2,1));
    EXPECT_EQ(M.getValue(2,2), rmsd.calcMatrix().getValue(2,2));
}

TEST(RMSD,JacobiUSV) {

}

TEST(RMSD,signDet) {
    RMSD rmsd;
    Space P = RMSD::getTestSetP();
    Space Q = RMSD::getTestSetQ();
    rmsd.P = P;
    rmsd.Q = Q;
    rmsd.Pc = P;
    rmsd.Qc = Q;

    MatrixXf U = MatrixXf::Identity(3,3);
    MatrixXf V = MatrixXf::Identity(3,3);
    V(1,0)= 2;
    V(2,0)= 3;

    U(0,1)= 2;
    U(0,2)= 3;
    rmsd.V = V;
    rmsd.U = U;

    EXPECT_EQ(1, rmsd.signDet());
}

TEST(RMSD,sign) {
    RMSD rmsd;
    Space P = RMSD::getTestSetP();
    Space Q = RMSD::getTestSetQ();
    rmsd.P = P;
    rmsd.Q = Q;
    rmsd.Pc = P;
    rmsd.Qc = Q;

    EXPECT_EQ(1, rmsd.sign(2.0));
    EXPECT_EQ(-1, rmsd.sign(-2.0));
    EXPECT_EQ(0, rmsd.sign(0.0));

}

TEST(RMSD,rotateR) {
    RMSD rmsd;
    Space P = RMSD::getTestSetP();
    Space Q = RMSD::getTestSetQ();
    rmsd.P = P;
    rmsd.Q = Q;
    rmsd.Pc = P;
    rmsd.Qc = Q;

    MatrixXf U = MatrixXf::Identity(3,3);
    MatrixXf V = MatrixXf::Identity(3,3);
    V(1,0)= 2;
    V(2,0)= 3;

    U(0,1)= 2;
    U(0,2)= 3;
    rmsd.V = V;
    rmsd.U = U;

    MatrixXf R = MatrixXf::Identity(3,3);
    R(0,0) = 1;
    R(0,1) = 0;
    R(0,2) = 0;
    R(1,0) = 4;
    R(1,1) = 1;
    R(1,2) = 0;
    R(2,0) = 12;
    R(2,1) = 0;
    R(2,2) = 3;

    rmsd.rotateR(3);

    EXPECT_EQ(R, rmsd.R);
}
TEST(RMSD,formula) {

}

TEST(RMSD,formulaR) {

}
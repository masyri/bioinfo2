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

#include "../matrix/Matrix.h"
#include "../ccp/Amino.h"
#include "../ccp/Occurrence.h"

/*

     Alanin          //	Ala	A  0
    ,Arginin         //	Arg	R  1
    ,Asparagin       //	Asn	N  2
    ,Asparaginacid   //	Asp	D  3
    ,Cystein         // Cys	C  4

    ,Glutamin        //	Gln	Q  5
    ,Glutaminacid    //	Glu	E  6
    ,Glycin          //	Gly	G  7
    ,Histidin        //	His	H  8
    ,Isoleucin       //	Ile	I  9

    ,Leucin          //	Leu	L 10
    ,Lysin           //	Lys	K 11
    ,Methionin       //	Met	M 12
    ,Phenylalanin    //	Phe	F 13
    ,Prolin          //	Pro	P 14

    ,Serin           //	Ser	S 15
    ,Threonin        //	Thr	T 16
    ,Tryptophan      //	Trp	W 17
    ,Tyrosin         //	Tyr	Y 18
    ,Valin	         // Val	V 19

*/










//
// important for the dynamic size change for the k-columns-count of the occurrence-matrix
//
// Are the old values correct after resize?
//
TEST(Matrix,Resize_Test) { 

Matrix<int> Ma(2,2,-1);

Matrix<float> Mb(2,2,1.0f);

Matrix<double> Mc(2,2,0.0);

Matrix<bool> Md(2,2,false);

// correct initial values?

EXPECT_EQ(-1,Ma.getValue(1,1));
EXPECT_EQ(1.0f,Mb.getValue(1,1));
EXPECT_EQ(0,Mc.getValue(1,1));
EXPECT_EQ(false,Md.getValue(1,1));

// set Values
Ma.setValue(0,0,19);
Ma.setValue(0,1,29);
Ma.setValue(1,0,39);
Ma.setValue(1,1,49);

// Matrix re-Size (make it bigger)
Ma.reSize(3,3,1000);

EXPECT_EQ(19,Ma.getValue(0,0));
EXPECT_EQ(29,Ma.getValue(0,1));
EXPECT_EQ(1000,Ma.getValue(0,2));
EXPECT_EQ(39,Ma.getValue(1,0));
EXPECT_EQ(49,Ma.getValue(1,1));
EXPECT_EQ(1000,Ma.getValue(1,2));

EXPECT_EQ(1000,Ma.getValue(2,0));
EXPECT_EQ(1000,Ma.getValue(2,1));
EXPECT_EQ(1000,Ma.getValue(2,2));

// Matrix re-Size (make it smaller)
Mb.setValue(0,0,19.0f);
Mc.setValue(0,0,59.0);
Md.setValue(0,0,true);

Mb.reSize(1,1,0.f);
Mc.reSize(1,1,0);
Md.reSize(1,1,false);

EXPECT_EQ(19.f,Mb.getValue(0,0));
EXPECT_EQ(59.0,Mc.getValue(0,0));
EXPECT_EQ(true,Md.getValue(0,0));

}







//
// Test for matrix-resize k-columns with insert
//
TEST(Occurence,Resize_Test) { // 

Occurrence O;

vector<AA> a = { Valin , Alanin , Serin , Glutamin , Prolin }; //   { 19 , 0 , 15 , 5 , 14 }

// > insert

O.insert( a[0] , 0 );O.insert( a[0] , 0 );  // k = 0 , 2 occurrences for row 19

// check

EXPECT_EQ( 2 , O.getValue(19,0));
EXPECT_EQ( 1 , O.getColumnCount());

// > insert

O.insert( a[1] , 3 );   // k = 3 , 1 occurrence for row 0

// check

EXPECT_EQ( 1 , O.getValue(0,3));
EXPECT_EQ( 4 , O.getColumnCount());

// > insert

O.insert( a[1] , 1 );   // k = 1 , 1 occurrence for row 0

// check

EXPECT_EQ( 1 , O.getValue(0,1));
EXPECT_EQ( 4 , O.getColumnCount());

// > insert

O.insert( a[2] , 10 );O.insert( a[2] , 10 );O.insert( a[2] , 10 ); // k = 10 , 3 occurrences for row 15

// check

EXPECT_EQ( 3 ,  O.getValue(15,10));
EXPECT_EQ( 11 , O.getColumnCount());

// > insert

O.insert( a[3] , 8 );  // k = 8 , 1 occurrence for row 5

// check

EXPECT_EQ( 1 , O.getValue(5,8));
EXPECT_EQ( 11 , O.getColumnCount());

// > insert

O.insert( a[4] , 8 );  // k = 8 , 1 occurrence for row 14

// check

EXPECT_EQ( 1 , O.getValue(14,8));
EXPECT_EQ( 11 , O.getColumnCount());

}








//
// Test for correct values with insert
//
TEST(Occurence,Test) { // 

Occurrence O;

EXPECT_EQ(0,6);
}



//
// Test correctness of count method
//
TEST(Occurence,CountResiduesTest) { // 

Occurrence O;

  //  int countResidues() 

  //  int countResidues(AA amino) 
  
  //  int countResidues(int k) 


     
EXPECT_EQ(0,6);
}






//
// Test Probability Matrix
//
TEST(Probability,Values_Test) { // 

Occurrence O;

EXPECT_EQ(0,9);
}





//
// Test Scoring Matrix
//
TEST(Scoring,Values_Test) { // 

Occurrence O;

EXPECT_EQ(0,9);
}

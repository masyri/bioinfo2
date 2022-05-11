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

#include "../Data.h"
#include "../Predictor.h"
// DATA TESTS

TEST(Data, Amino) {
    Amino a(1,'H','R',"test");

    EXPECT_EQ(1, a.getID());
    EXPECT_EQ('H', a.getStructure());
    EXPECT_EQ('R', a.getName());
    EXPECT_EQ("test", a.getProteinName());
}

TEST(Data, DataPoint) {
    Amino a(1,'H','R',"test");
    DataPoint point(a);

    EXPECT_EQ(a.getID(), point.Ref.getID());
    EXPECT_EQ(a.getName(), point.Ref.getName());
    EXPECT_EQ(a.getProteinName(), point.Ref.getProteinName());
    EXPECT_EQ(a.getStructure(), point.Ref.getStructure());
}

TEST(Data, DataPointArray) {
    Amino a(1,'H','R',"test");
    DataPoint point(a);
    DataPointArray ar(1);
    ar.array.push_back(point);
    
    EXPECT_EQ("test", ar.getProteinName());
    EXPECT_EQ(1, ar.getCountAllAmino());
    EXPECT_EQ(1, ar.getCountInDataSetAmino());
}


// PREDICTOR TESTS

TEST(PredictorTEST, Constructor) {
   vector<string> filelist = {"1A0B.pdb"};
    //Predictor pred(filelist);
}

TEST(PredictorTEST, getAminosFromMultipleProteins) {
    // get reference value
/*
    // get system
    PDBFile f("../PDB/1QJP.pdb", ios::in);
    System S;
    f >> S;

    vector<string> filelist;
    Predictor p(filelist);
    p.*/
}
TEST(PredictorTEST, createDatasetArrayFromProtein) {
    // get reference value
}
TEST(PredictorTEST, createTableFile) {
    // get reference value
}

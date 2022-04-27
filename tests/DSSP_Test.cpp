#include <gtest/gtest.h>

#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/molecule.h>
#include <BALL/KERNEL/atom.h>
#include <BALL/KERNEL/bond.h>
#include <BALL/KERNEL/PTE.h>
#include <BALL/FORMAT/PDBFile.h>
#include <BALL/STRUCTURE/fragmentDB.h>
#include <BALL/KERNEL/residueIterator.h>
#include <vector>
#include <sstream>
#include <Test.hpp>
#include "../DSSP.h"
#include "../Groups.h"

TEST(DSSP_Test, findWSSB)
{
    
}

TEST(DSSP_Test, removeWSSB)
{
    
}

TEST(DSSP_Test, computeHelix)
{
    
}

TEST(DSSP_Test, calculate_H_position)
{
    Vector3 v1(1.0,1.0,1.0);
    Vector3 v2(1.0,1.0,1.0);
    Vector3 v3(1.0,1.0,1.0);

    Vector3 result(1.0,1.0,1.0);
    EXPECT_EQ(result , calculate_H_position(v1,v2,v3));
}

TEST(DSSP_Test, checkDistance)
{
    /*
    Atom* H;
    Atom* N;
    H->setPosition(Vector3(1.0,2.0,3.0));
    N->setPosition(Vector3(1.0,2.0,5.0));
    int ID = 10;

    NH_Group NH(H,N,ID);

    EXPECT_TRUE(checkDistance(NH, 5.0));
    EXPECT_FALSE(checkDistance(NH, 1.0));
    EXPECT_FALSE(checkDistance(NH, 2.0));*/
}

TEST(DSSP_Test, checkEnergy)
{
    Atom* H;
    Atom* N;
    H->setPosition(Vector3(1.0,2.0,3.0));
    N->setPosition(Vector3(1.0,2.0,5.0));
    int ID = 10;

    NH_Group NH(H,N,ID);
    EXPECT_EQ(10 , checkEngergy(NH, -0,5));
}

TEST(DSSP_Test, checkAngle)
{
    Atom* H;
    Atom* N;
    H->setPosition(Vector3(1.0,2.0,3.0));
    N->setPosition(Vector3(1.0,2.0,5.0));
    int ID = 10;

    NH_Group NH(H,N,ID);
    EXPECT_EQ(10 , checkAngle(NH, 120));

}

TEST(DSSP_Test, initNHGroup)
{
    Atom* H;
    Atom* N;
    H->setPosition(Vector3(1.0,2.0,3.0));
    N->setPosition(Vector3(4.0,5.0,6.0));
    int ID = 10;

    NH_Group NH(H,N,ID);
    EXPECT_EQ(H->getPosition(), NH.H->getPosition());
    EXPECT_EQ(N->getPosition(), NH.N->getPosition());
    EXPECT_EQ(ID , NH.index);

    
}

TEST(DSSP_Test, initCOGroup)
{
    Atom* C;
    Atom* O;
    C->setPosition(Vector3(1.0,2.0,3.0));
    O->setPosition(Vector3(4.0,5.0,6.0));
    int ID = 10;

    CO_Group CO(C,O,ID);
    EXPECT_EQ(C->getPosition(), CO.C->getPosition());
    EXPECT_EQ(O->getPosition(), CO.O->getPosition());
    EXPECT_EQ(ID , CO.index);

    
}
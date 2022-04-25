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


TEST(DSSP_Test, findWSSB)
{
    
}

TEST(DSSP_Test, removeWSSB)
{
    
}

TEST(DSSP_Test, computeHelix)
{
    
}

TEST(DSSP_Test, checkDistance)
{
    BALL::ATOM atomH;
    BALL::ATOM atomO;

    atomH.setPosition(Vector3(0.0,0.0,0.0));
    atomO.setPosition(Vector3(0.0,0.0,0.0));

    checkDistance(atomH, atomO);
}

TEST(DSSP_Test, checkEnergy)
{
    
}

TEST(DSSP_Test, checkAngle)
{
    
}
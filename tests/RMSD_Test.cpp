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

    Vector3 center = d.calcCenterCoordinate(); // -> (0,0,0)
    
EXPECT_TRUE(false);

}





TEST(SPACE,MoveCenter) {

    Space S;

    S.addPosition("O",3,3,2);   // -> (0,0,0)
    S.addPosition("a",3,5,-3);  // -> (0,2,-5)
    S.addPosition("b",3,2,4);   // -> (0,-1,2)
    S.addPosition("c",-2,-2,2); // -> (-5,-5,0)
    S.addPosition("z",0,0,0);   // -> (-3,-3,-2)
    
    Vector3 newCenter(3,3,2);
       
    S.moveCenterCoordinate(newCenter);

    Position _1 = S.positions[0];
    Position _2 = S.positions[1];
    Position _3 = S.positions[2];
    Position _4 = S.positions[3];
    Position _5 = S.positions[4];

EXPECT_TRUE(_1.index == "0" && _1.x == 0 && _1.y == 0 && _1.z == 0 );
EXPECT_TRUE(false);

}

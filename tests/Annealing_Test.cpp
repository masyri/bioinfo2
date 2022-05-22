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


#include "../annealing/Annealing.h"




TEST(SimAnnealing,Bond_Test) { 

  long double value = Annealing::calc_single_E_bond(99.0,12.0,8.0);

  EXPECT_EQ(value,792.0);

}



TEST(SimAnnealing,Angle_Test) { 

  long double value = Annealing::calc_single_E_angle(99.0,12.0,8.0);

  EXPECT_EQ(value,792.0);

}


TEST(SimAnnealing,Probability_Test) { 

  long double value = Annealing::probability(2.5,3.5,100);

  EXPECT_EQ(1.001243008,value);

}




TEST(SimAnnealing,assignRandomConformation_Test) { 

  EXPECT_EQ(8,9);

}


TEST(SimAnnealing,Eval_Test) { 

  int loops = 10;

  EXPECT_EQ(8,9);

}



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
#include "../annealing/Water.h"



TEST(SimAnnealing,Bond_Test) { 

  long double value = Annealing::calc_single_E_bond(99.0,12.0,8.0);

  EXPECT_EQ(value,792.0);

}



TEST(SimAnnealing,Angle_Test) { 

  long double value = Annealing::calc_single_E_angle(99.0,12.0,8.0);

  EXPECT_EQ(value,792.0);

}


TEST(SimAnnealing,Probability_Test) { 

  long double value = Annealing::probability_formula(2.5,3.5,100);
  long double res = 1.0012;
  EXPECT_EQ(res,value);

}




TEST(SimAnnealing,assignRandomConformation_Test) { 

  EXPECT_EQ(8,9);

}


TEST(SimAnnealing,Eval_Test) { 

  int loops = 10;

  EXPECT_EQ(8,9);

}


TEST(SimAnnealing,calc_energy_Test) { 
/*
    BALL::Molecule* m;
    BALL::Atom Ox;
    BALL::Atom H1;
    BALL::Atom H2;
    auto oxy = PTE[Element::O];
    auto hyd = PTE[Element::H];
    Ox.setElement(oxy);
    H1.setElement(hyd);
    H2.setElement(hyd);

    BALL::Bond* a = Ox.createBond(H1);
    BALL::Bond* b = Ox.createBond(H2);

    Ox.setPosition(Vector3(0,0,0));
    H1.setPosition(Vector3(0,1,0));
    H2.setPosition(Vector3(1,1,0));

    m->insert(Ox);
    m->insert(H1);
    m->insert(H2);

    Water wat(m,300);

    //auto res = Annealing::calc_energy(&wat);


  
    EXPECT_EQ(0,4);*/
}

TEST(Water_TEST, createMoleculeFromTempStats) { 

    BALL::Molecule* m;
    BALL::Atom Ox;
    BALL::Atom H1;
    BALL::Atom H2;
    auto oxy = PTE[Element::O];
    auto hyd = PTE[Element::H];
    Ox.setElement(oxy);
    H1.setElement(hyd);
    H2.setElement(hyd);
  
    BALL::Bond* a = Ox.createBond(H1);
    BALL::Bond* b = Ox.createBond(H2);

    Ox.setPosition(Vector3(0,0,0));
    H1.setPosition(Vector3(0,1,0));
    H2.setPosition(Vector3(1,1,0));
/*
    m->insert(Ox);
    m->insert(H1);
    m->insert(H2);

    Water wat(m,300);

    wat.angle = 90;
    wat.length1 = 2;
    wat.length2 = 3;

    System s = wat.createMoleculeFromTempStats();

    Molecule mol = *(s.beginMolecule());

        Atom* O = mol.getAtom(0);
        Atom* H_1 = mol.getAtom(1);
        Atom* H_2 = mol.getAtom(2);

        BALL::Vector3 pos_O = O->getPosition();
        BALL::Vector3 pos_H1 = H_1->getPosition();
        BALL::Vector3 pos_H2 = H_2->getPosition();

        Vector3 vector_OH1 = pos_H1 - pos_O;
        Vector3 vector_OH2 = pos_H2 - pos_O;

        auto length1 = vector_OH1.getLength();
        auto length2 = vector_OH2.getLength();

        auto angle = vector_OH1.getAngle(vector_OH2).toDegree();

  
  EXPECT_EQ(length1,2);
  EXPECT_EQ(length2,3);
  EXPECT_EQ(angle,90);*/

  EXPECT_EQ(0,4);
}
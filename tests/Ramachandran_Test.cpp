#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "../Ramachandran.h"

TEST(Ramachandran, Initiation) {
    // get reference values
    PDBFile f("../PDB/1QJP.pdb", ios::in);
    System S;
    f >> S;
    Ramachandran R(S);

    vector<StructPair> reference;
    int refaminoacids = 0;
    int refhelices = 0;
    int refloops = 0;
    int refsheets = 0;

    for (auto &iter: S.residues()){
        if (iter.isAminoAcid()){
             auto code = Peptides::OneLetterCode(iter.getName());
             auto SecStruct = iter.getSecondaryStructure()->getType();
             switch (SecStruct) {
               case SecondaryStructure::HELIX:             reference.push_back(StructPair(&code,'H')); refhelices++;  break;
               case SecondaryStructure::COIL:              reference.push_back(StructPair(&code,'-'));             break;
               case SecondaryStructure::TURN:              reference.push_back(StructPair(&code,'L')); refloops++;    break;
               case SecondaryStructure::STRAND:            reference.push_back(StructPair(&code,'S')); refsheets++;   break;
               case SecondaryStructure::UNKNOWN:           reference.push_back(StructPair(&code,'U'));             break;
               default:                                    reference.push_back(StructPair(&code,'-'));             break;
             }
             refaminoacids++;
        }
    }

// check protein name
    EXPECT_EQ(S.getProtein(0)->getName(), R.protein_name);

// check structur
    vector<StructPair> structures = R.getStructures();
    auto ref = reference.begin();
    for(const auto& tuple : structures) {
        EXPECT_EQ(ref->name, tuple.name);
        EXPECT_EQ(ref->type, tuple.type);
        ref++;
    }
    
//check statistic
    EXPECT_EQ(refaminoacids, R.getAminoacids());
    EXPECT_EQ(refhelices, R.getHelices());
    EXPECT_EQ(refsheets, R.getSheets());
    EXPECT_EQ(refloops, R.getLoops());
}

TEST(Ramachandran, getTorsionAngels) {
    //get ramachandran
    PDBFile f("../PDB/1QJP.pdb", ios::in);
    System S;
    f >> S;
    Ramachandran R(S);
    vector<AnglePair> angles = R.getTorsionAngels();

    //get reference values
    vector<AnglePair> ref = {};
    for (ResidueIterator iter = S.beginResidue() ; +iter ; ++iter) {
        if(iter->getTorsionPhi() != 0 && iter->getTorsionPsi() != 0) {
            double refpsi = iter->getTorsionPsi().toDegree();
            double refphi = iter->getTorsionPhi().toDegree();
            ref.emplace_back(refphi,refpsi);
        }

    }
    auto refi = ref.begin();
    for(auto tuple : angles) {
        EXPECT_EQ(refi->phi, tuple.phi);
        EXPECT_EQ(refi->psi, tuple.psi);
        refi++;
    }

}

TEST(DOG,WOUF) {


    ASSERT_EQ("wouf","wouf");
}
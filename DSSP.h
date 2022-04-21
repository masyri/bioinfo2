//
// Created by manjaro on 21.04.22.
//

#ifndef DSSP_H
#define DSSP_H

#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/molecule.h>
#include <BALL/KERNEL/atom.h>
#include <BALL/KERNEL/bond.h>
#include <BALL/KERNEL/PTE.h>
#include <BALL/FORMAT/PDBFile.h>
#include "Groups.h"



class IJ_Tuple { // H-Bond in (i,j) - Format
public:
    IJ_Tuple(NH_Group NH,CO_Group CO) {this->NH = &NH;this->CO = &CO;}
    NH_Group *NH;
    CO_Group *CO;
    std::string toString() { 
        std::stringstream s("");
        s << "\n ( " << NH->indices << " , " << CO->indices << " )";
        return s.str();
    }

};



class DSSP {
public:

    DSSP(BALL::System S);

    BALL::Atom* returnCNeighbor(Atom* Source);

    void startAlgorithm();

    int printResults() {int i = 0; for(IJ_Tuple T : result) {cout << "\n" << T.toString();i++;} return i;};

    BALL::System S;
    
    std::vector<NH_Group> NH_Groups;
    std::vector<CO_Group> CO_Groups;
    std::vector<IJ_Tuple> result;

};








#endif //DSSP_H

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
#include <sstream>


/*

    This Class is a H-Bond and 
    contains the NH and CO Group and their indices

*/
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




/*

    This Class reads all NH/CO Groups from a given System 
    and create a List of H-Bonds 'results'

*/
class DSSP {
public:

    DSSP(BALL::System S);

    void startAlgorithm();

    int printResults() {int i = 0; for(IJ_Tuple T : result) {cout << "\n" << T.toString();i++;} return i;};

    void removeHBonds();

    void computeHelices(std::string file_out);

    static void createAS_File(std::vector<char> AS, std::vector<char> TY,std::string file_out);

    BALL::System S;
    
    Space3D Space; // Coordinate-Space with all Groups
    std::vector<NH_Group> NH_Groups;
    std::vector<CO_Group> CO_Groups;
    std::vector<IJ_Tuple> result;    // List of H-Bonds

};








#endif //DSSP_H

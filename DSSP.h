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
#include <BALL/STRUCTURE/fragmentDB.h>
#include <BALL/KERNEL/residueIterator.h>
#include <vector>
#include "Groups.h"
#include "Space3D.h"
#include <sstream>


/*

    This Class is a H-Bond and 
    contains the NH and CO Group and their indices

*/
class IJ_Tuple { // H-Bond in (i,j) - Format
public:
    IJ_Tuple(NH_Group NH,CO_Group CO, int i, int j) {this->NH = &NH;this->CO = &CO;
        this->i = i; this-> j = j;}
    NH_Group *NH;
    CO_Group *CO;
    int i = -1;
    int j = -1;
    std::string toString() { 
        std::stringstream s("");
        s << "\n ( " << NH->index << " , " << CO->index << " )";
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

    void getGroups();

    Vector3 calculate_H_position(Vector3 C_start, Vector3 C_end, Vector3 N_Atom);

    void startAlgorithm();

    int printResults() {int i = 0; for(IJ_Tuple T : result) {cout << "\n" << T.toString();i++;} return i;};

    void removeHBonds();

    void computeHelices(std::string file_out);

    static void createAS_File(std::vector<char> AS, std::vector<char> TY,std::string file_out);

    BALL::System S;
    
    Space3D space = Space3D(100,100,100,100); // Coordinate-Space with all Groups
    std::vector<NH_Group> NH_Groups;
    std::vector<CO_Group> CO_Groups;
    std::string names;
    std::vector<IJ_Tuple> result;    // List of H-Bonds
};








#endif //DSSP_H

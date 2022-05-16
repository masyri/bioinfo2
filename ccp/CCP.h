//
// Created by manjaro on 12.05.22.
//

#ifndef CCP_CCP_H
#define CCP_CCP_H


#include "Occurrence.h"
#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/molecule.h>
#include <BALL/KERNEL/atom.h>
#include <BALL/KERNEL/bond.h>
#include <BALL/KERNEL/PTE.h>
#include <BALL/STRUCTURE/secondaryStructureProcessor.h>
#include <BALL/STRUCTURE/fragmentDB.h>
#include <BALL/STRUCTURE/peptides.h>
#include <BALL/FORMAT/PDBFile.h>


#include <vector>
#include <string>

using namespace std;
using namespace BALL;


/**
 * @brief Set of Amino-Acid and Position 
 * 
 */
class AminoTuple {
public:
AminoTuple(int id , AA amino , Vector3 position ) {
    this->id = id;
    this->amino = amino;
    this->position = position;
}
int id;
AA amino;
Vector3 position;
};



/**
 * @brief Build an Occurence-Matrix from files
 * 
 */
class CCP {
public:


/**
 * @brief Reads all proteins from all given PDB-files to build an occurence matrix
 * 
 * 
 * @param files 
 * @return Occurrence-Matrix
 */
    static Occurrence createOccurrenceMatrixFromFiles(vector<string> files);

};



#endif //CCP_CCP_H

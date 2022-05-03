//
// Created by manjaro on 29.04.22.
//

#ifndef RAMACHANDRAN_H
#define RAMACHANDRAN_H


#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include "console/Color.h"
#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/molecule.h>
#include <BALL/KERNEL/atom.h>
#include <BALL/KERNEL/bond.h>
#include <BALL/KERNEL/PTE.h>
#include <BALL/FORMAT/PDBFile.h>
#include <BALL/STRUCTURE/fragmentDB.h>
#include <BALL/KERNEL/residueIterator.h>
#include <BALL/STRUCTURE/peptides.h>
#include <vector>

using namespace std;
using namespace BALL;



/**
 *  A tuple of Phi and Psi angles
 *
 * */
class AnglePair {
public:
    AnglePair(double phi,double psi) {this->phi = phi;this->psi = psi;}
    double phi;
    double psi;
    friend ostream& operator<<(ostream& os, const AnglePair& ap)
        {
        os << C::BGREEN  << "phi: "   << C::GREEN  << ap.phi
           << C::BYELLOW << "  psi: " << C::YELLOW << ap.psi
           << C::RESET;
        return os;}
};




/**
 *  A tuple of name of aminoacid and this structure.
 *
 * */
class StructPair {
public:
    StructPair(string name,char type) {this->name = std::move(name); this->type = type;}
    string name;
    char type;
};





/**
 *  Main Class of Ramachandran for print statistics and create CSV-Files
 *
 * */
class Ramachandran {

public:

    explicit Ramachandran(System Sys);

    vector<AnglePair> getTorsionAngels();

    Peptides::OneLetterAASequence getCodeAA(SecondaryStructureIterator &begin);
    
    static void anglesToFile(const string& filename, std::vector<AnglePair> AP);

    void printStats() const;

    void printSequences() const;

    string protein_name;

private:
    System S;

    int helices    = 0; // count of helices in this protein
    int loops      = 0; // count of loops in this protein
    int sheets     = 0; // count of sheets in this protein
    int aminoacids = 0; // count of aminoacids in this protein

    vector<StructPair> structures; // vector of structures in this protein


};


#endif //RAMACHANDRAN_H

//
// Created by manjaro on 24.05.22.
//

#ifndef ANNEALING_WATER_H
#define ANNEALING_WATER_H

#include <BALL/KERNEL/molecule.h>
#include <BALL/FORMAT/HINFile.h>
#include <BALL/KERNEL/atom.h>
#include <BALL/KERNEL/PTE.h>
#include <BALL/KERNEL/system.h>
#include <BALL/FORMAT/PDBFile.h>
#include<BALL/KERNEL/bond.h>


using namespace std;
using namespace BALL;

/*
 * Water Molecule for annealing statistics
 * */
class Water {

public:

    /*
     * Create Water-Molecule-Stats and initialize all temporary stats (without energy)
     *
     * */
    Water(Molecule* mol, int startTemperature) {

        this->O = mol->getAtom(0);
        this->H1 = mol->getAtom(1);
        this->H2 = mol->getAtom(2);
        if (this->O == nullptr   ) {std::cout << "Molecule : No O-Atom found\n"; }
        if (this->H1 == nullptr  ) {std::cout << "Molecule : No H1-Atom found\n"; }
        if (this->H2 == nullptr  ) {std::cout << "Molecule : No H2-Atom found\n"; }
        this->temperature = startTemperature;

        BALL::Vector3 pos_O = O->getPosition();
        BALL::Vector3 pos_H1 = H1->getPosition();
        BALL::Vector3 pos_H2 = H2->getPosition();

        Vector3 vector_OH1 = pos_H1 - pos_O;
        Vector3 vector_OH2 = pos_H2 - pos_O;

        this->length1 = vector_OH1.getLength();
        this->length2 = vector_OH2.getLength();

        this->angle = vector_OH1.getAngle(vector_OH2).toDegree();

        std::cout << "Molecule OK ...\n";

    }

    // Molecule

        Molecule* molecule;
        Atom* O;
        Atom* H1;
        Atom* H2;


    // temporary stats ( not actually in molecule )

        int temperature = 300;  // Temperature of this conformation

        long double energy = 0;  // Energy of this conformation

        long double angle = 0;   // HOH molecule angle

        long double length1 = 0; // Bond length H1

        long double length2 = 0; // Bond length H2


    // create line for CSV File

    std::string CSV_line(){ 

        std::stringstream s(""); 
        s << energy << ";" << temperature << ";" << angle << ";" << length1 << ";" << length2; 
        return s.str();

        }

};


#endif //ANNEALING_WATER_H

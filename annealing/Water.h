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
        this->temperature = startTemperature;

        BALL::Vector3 pos_O = O->getPosition();
        BALL::Vector3 pos_H1 = H1->getPosition();
        BALL::Vector3 pos_H2 = H2->getPosition();

        Vector3 vector_OH1 = pos_H1 - pos_O;
        Vector3 vector_OH2 = pos_H2 - pos_O;

        this->length1 = vector_OH1.getLength();
        this->length2 = vector_OH2.getLength();

        this->angle = vector_OH1.getAngle(vector_OH2).toDegree();

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

    // create Molecule from temporary stats

    System createMoleculeFromTempStats() {

    System s;

    BALL::Molecule m;

    BALL::Atom Ox;
    BALL::Atom H1;
    BALL::Atom H2;

    auto oxy = PTE[Element::O];
    auto hyd = PTE[Element::H];

    Ox.setElement(oxy);
    H1.setElement(hyd);
    H2.setElement(hyd);

    Ox.createBond(H1);
    Ox.createBond(H2);
    H1.createBond(Ox);
    H2.createBond(Ox);

    Ox.setPosition(Vector3(0,0,0));
    H1.setPosition(Vector3(0,length1,0));
    H2.setPosition(Vector3(length2,0,0));

    m.insert(Ox);
    m.insert(H1);
    m.insert(H2);

    double angle_i  = angle;
    Angle angle(angle_i, false);
    Vector3 rotationaxis(1., 0., 0.);

    Matrix4x4 mat;
    mat.setRotation(angle, rotationaxis);

    s.insert(m);

    return s;

/*
        BALL::AtomIterator ait = molecule->beginAtom();

        BALL::Atom O , H1 , H2 ;
        O = ait.operator*();        ait++;
        H1 = ait.operator*();        ait++;
        H2 = ait.operator*();

        BALL::Vector3 pos_O = O.getPosition();
        BALL::Vector3 pos_H1 = H1.getPosition();
        BALL::Vector3 pos_H2 = H2.getPosition();

        double length1 = (pos_O - pos_H1).getLength();
        double length2 = (pos_O - pos_H2).getLength();

        // Länge
        double randomlength = random(0.7,1.3);

        // Mittelpunkt H1 - H2
        Vector3 M_Point = pos_H1 + ((pos_H2 - pos_H1) / 2.0);
        Vector3 direction = (pos_O - M_Point).normalize() * randomlength;

        // Winkel:
        double randomangle = random(100,120) / 2.0;


    */
    System S;
    return S;

    }




    // create line for CSV File

    std::string CSV_line(){ 
        std::stringstream s(""); 
        s << energy << ";" << temperature << ";" << angle << ";" << length1 << ";" << length2; 
        return s.str();}

};







#endif //ANNEALING_WATER_H

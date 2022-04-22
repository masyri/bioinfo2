//
// Created by manjaro on 21.04.22.
//

#ifndef GROUPS_H
#define GROUPS_H

#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/molecule.h>
#include <BALL/KERNEL/atom.h>
#include <BALL/KERNEL/bond.h>
#include <BALL/KERNEL/PTE.h>
#include <BALL/FORMAT/PDBFile.h>


/*
 * the class NH_Group contains only the N and H Atoms (their references)
 *
 * the class CO_Group contains only the C and O Atoms (their references)
 * You can calculate with a CO_Group Object the distance and the angle to a NH-Group
 * Object.
 *
 * have much fun !!
 *
 * */


using namespace std;
using namespace BALL;




/*
 *
 *   C                 C
 *    \               /       Contains the Atoms (references) from a
 *     C = O  ?  H - N        NH-Group.
 *    /               \
 *   C                 C
 *
 *
 * */
class NH_Group {
public:

    NH_Group(Atom *H, Atom *N) {
        this->H = H;
        this->N = N;
        this->indices = 123456; // Wie bekommt man den Indices aus dem Atom bzw. Molekül heraus? Hä ?

    }

    Atom *H;
    Atom *N;
    int indices = -1;

    std::string Group2String() {
        std::stringstream s("");

        s << "\n [NH-Group] " <<"indices = " << this->indices
              << "\n (N pos) : " << this->N->getPosition()
              << "\n (H pos) : " << this->H->getPosition();

        return s.str();

    }

};






/*
 *
 *   C                 C
 *    \               /       Contains the Atoms (references) from a
 *     C = O  ?  H - N        CO-Group.
 *    /               \
 *   C                 C
 *
 *
 * */
class CO_Group {
public:



    CO_Group(Atom *C, Atom *O) {
        this->O = O;
        this->C = C;
        this->indices = 123456; // Wie bekommt man den Indices aus dem Atom bzw. Molekül heraus? Hä ?
    }



    /*
     * Returns the distance between the O-Atom from this Group
     * and the H-Atom from the chosen NH_Group 'NH'
     *
     * */
    double getDistance(NH_Group NH) {
        return NH.N->getPosition().getDistance(O->getPosition());
    }


    /*
     * Returns if the distance between the O-Atom from this Group
     * and the H-Atom from the chosen NH_Group 'NH' in the given max range
     * (Example max_distance = 2.5 for a valid "Wasserstoffbrückenbindung")
     *
     * */
    bool checkDistance(NH_Group NH,double max_distance) {
        double dist = abs(getDistance(NH));
        return dist < max_distance;
    }



    /*
     * Returns if the distance between the O-Atom from this Group
     * and the H-Atom from the chosen NH_Group 'NH' in the given max range
     * (Example min_angle = 120 ( in degree :) ) for a valid "Wasserstoffbrückenbindung")
     *
     * */
    bool checkAngle(NH_Group NH,double min_angle) {

        // get position of 3 points
        Vector3 position_H = NH.H->getPosition();
        Vector3 position_N = NH.N->getPosition();
        Vector3 position_O = O->getPosition();
        
        // make 2 vectors which starts at the H-Atom in the direction to the N-Atom and the O-Atom
        Vector3 vector_H_N = position_N - position_H;
        Vector3 vector_H_O = position_N - position_H; // Hab ich die beiden Vektoren jetzt richtig erstellt?

        double angle = vector_H_N.getAngle(vector_H_O); // ist der Return dieser Methode in Grad oder im Whatever-Maß ? Ist wichtig wegen dem vergleichen mit dem min_angle von 120°

        return angle >= min_angle;

    }


    /*
     * calculate the energy from this group and your chosen NH-Group.
     *
     * E = f * delta1 * delta2 * ( 1/r_NO + 1/r_HC + 1/r_HO + 1/r_NC )
     *
     * */
    double getEnergy(NH_Group NH) {

        double f_d1_d2 = 27.888; // Hat so auf dem Übungsblatt gestanden

        double dist_NO =  NH.N->getPosition().getDistance(O->getPosition());
        double dist_HC =  NH.H->getPosition().getDistance(C->getPosition());
        double dist_HO =  NH.H->getPosition().getDistance(O->getPosition());
        double dist_NC =  NH.N->getPosition().getDistance(C->getPosition());

        return f_d1_d2 * ( 1 / dist_NO + 1 / dist_HC - 1 / dist_HO - 1 / dist_NC );

    }

    /*
     * calculate the energy from this group and your chosen NH-Group.
     * It will return true if the calculated energy less than 'max_energy'
     * Example -0.5
     *
     * E = f * delta1 * delta2 * ( 1/r_NO + 1/r_HC + 1/r_HO + 1/r_NC )
     *
     * */
    bool checkEnergy(NH_Group NH,double max_energy) {
    double E = getEnergy(NH);
    return E < max_energy;
    }




    std::string Group2String() {
        std::stringstream s("");

        s << "\n [CO-Group] " << "indices = " << this->indices
          << "\n (C pos) : " << this->C->getPosition()
          << "\n (O pos) : " << this->O->getPosition();

        return s.str();
    }

    Atom *O;
    Atom *C;
    int indices = -1;

};







#endif //GROUPS_H

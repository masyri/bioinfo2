//
// Created by manjaro on 19.05.22.
//

#include <X11/X.h>
#include <BALL/KERNEL/bond.h>
#include "Annealing.h"

long double Annealing::evaluate(int loops) {

        // reset Values
        this->Temperature = 300;
        this->loop_results = {};

        // loop variables
        long double E_new = 0;
        long double E_accepted = calc_energy();

        // loop start

        while(Temperature >= 10) {

            E_new = 0;

            for (int step = 0; step < loops ; step++) {

                // change Konformation
                assignRandomConformation();

                // Compute E_i

                E_new += calc_energy();

                // 

                if ( E_new < E_accepted ) {

                    E_accepted = E_new; 
                    
                }

                else {

                    long double p = probability(E_new,E_accepted,this->Temperature);
                    if (true) {
                        E_accepted = E_new;

                    }

                }

            }

        this->Temperature -= 10;

        }

    return 0;
}



long double Annealing::calc_energy() const{


    auto O = molecule->getAtom(0);
    auto H1 = molecule->getAtom(1);
    auto H2 = molecule->getAtom(2);

    BALL::Vector3 pos_O = O->getPosition();
    BALL::Vector3 pos_H1 = H1->getPosition();
    BALL::Vector3 pos_H2 = H2->getPosition();

    Vector3 vector_OH1 = pos_H1 - pos_O;
    Vector3 vector_OH2 = pos_H2 - pos_O;

    double length1 = vector_OH1.getLength();
    double length2 = vector_OH2.getLength();

    double angle = vector_OH1.getAngle(vector_OH2).toDegree();

    long double res = 0;
    res += calc_single_E_bond(k_s,length1,r_0);
    res += calc_single_E_bond(k_s,length2,r_0);
    res += calc_single_E_angle(k_a,angle,psi_0);

    return res;

}
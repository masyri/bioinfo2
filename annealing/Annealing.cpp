//
// Created by manjaro on 19.05.22.
//


#include "Annealing.h"

long double Annealing::evaluate(int loops) {

    // ## Init

            Water Accepted(this->molecule,300);
            Water New(this->molecule,300);

    // ## Calculate start Energy Level and
    // ## add to Optima-List

            Accepted.energy = calc_energy(&Accepted);
            this->optima.push_back(Accepted);

    // ## loop start

            while(Accepted.temperature >= 10) {

                for (int step = 0; step < loops ; step++) {

                    // load last Optimum
                    New = Accepted;

                    // Set Energy to zero for re-calc
                    New.energy = 0;

                    // change Conformation
                    assignRandomConformation(&New);

                    // Compute E_i
                    New.energy += calc_energy(&New);

                    // -- Decision: If Energy less than last accepted:

                    bool less = New.energy < Accepted.energy;
                    if (less) { Accepted = New; continue; }

                    // -- Decision: Energy is same or bigger

                    long double P = probability_formula(New.energy,Accepted.energy,Accepted.temperature);

                    if (probability(P)) { Accepted = New; continue; }

                    // -- no Decision

                    }

                // Add best Optimum to Array
                this->optima.push_back(Accepted);

                // Decrease temperature
                Accepted.temperature -= 10;
                }

        // return best energy
        return Accepted.energy;

        }



long double Annealing::calc_energy(Water* mol) const{

            long double res = 0;
            res += calc_single_E_bond(k_s,mol->length1,r_0);
            res += calc_single_E_bond(k_s,mol->length2,r_0);
            res += calc_single_E_angle(k_a,mol->angle,psi_0);

            return res;

        }
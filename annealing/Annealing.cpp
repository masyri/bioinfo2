//
// Created by manjaro on 19.05.22.
//

#include "Annealing.h"

long double Annealing::evaluate(int loops) {

        // reset Values
        this->Temperature = 300;
        this->loop_results = {};

        // loop variables
        long double E_new = 0;
        long double E_accepted = 0; 

        // calculate 

        long double E_accepted; 

        // loop start

        for (int step = 0; step < loops ; step++) {

            E_new = 0;

            for (int i = 1 ; i < 9813759 ; i++) {

                // change Konformation

                // Compute E_i

                E_new += this->calc_single_E_bond(0,0,0);
                E_new += this->calc_single_E_angle(0,0,0);

                // 

                if ( E_new < E_accepted || true ) { 
                    
                    long double p = this->probability(E_new,E_accepted,this->Temperature);
                    //if (p % 100 )
                    
                    
                    E_accepted = E_new; 
                    
                    } 

            }

        this->Temperature -= 10;

        }

    return 0;
}

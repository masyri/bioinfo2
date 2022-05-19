//
// Created by manjaro on 19.05.22.
//

#ifndef ANNEALING_H
#define ANNEALING_H

#include <complex>
#include <vector>

using namespace std;


#define AvocadoConst 2.3    // Avocado Contant
#define BoltzConst 3.5      // Boltzmann Constant
#define r_0 0.970           // r_0 0,970 Angström
#define k_s 1930.0          // k_s 1930 J mol
#define psi_0 104.5         // psi 104.5 Degree
#define k_a 196.8           // k_a 196,8 mol^-1 degree^-2

class Annealing {

public:


    /**
     * Load a Molecule from a HIN File
     * for Simulated Annealing
     *
     * @param filename input file path
     * */
    Annealing(string filename) {


    }



    /**
     * Create an HIN File with the actual
     * Molecule informations
     *
     * @param filename output file path
     * */
    void createHINFile(string filename) {


    }


    /**
     * Create an optimum file with optimum informations
     * after each loop step
     *
     * @param filename output file path
     * */
    void createOptimumFile(string filename) {



    }





    /**
     * create random double value
     *
     * @param min,max Range
     * */
    static double random(double min, double max)
    {
        double f = (double)rand() / RAND_MAX;
        return min + f * (max - min);
    }




    /**
     * Take the difference in energies.
     * Then a value will spit out under using the Avocado constant, Temperature
     * and Boltzmann.
     * With this you can decide to accept a conformation.
     *
     * @param E_new : Energy new
     * @param E_old : Energy old
     * @param T     : Temperature
     * */
    static long double probability (long double E_new,long double E_old, long double T) {

        long double diff = (E_new - E_old);
        long double div = AvocadoConst * BoltzConst * T;
        long double res = std::pow(2.71828182845904523536,- diff / div);
        return res;

    }




    /**
     * Change Molecule conformations as the name implies :D
     * */
    void assignRandomConformation() {

        double randomlength = random(0.7,1.3);
        // Mol.set OH Bond

        double randomangel = random(100,120);
        // Mol.set angle

    }




    /**
     * möp as the name implies :D
     * 
     * @param ks 
     * @param r_actual       
     * @param r_const       
     * 
     * */
    static long double calc_single_E_bond(double ks, double r_actual, double r_const) {

        return (ks / 2.0) * (r_actual - r_const) * (r_actual - r_const) ;

    }

    /**
     * möp as the name implies :D
     * 
     * @param ka 
     * @param psi_actual       
     * @param psi_const       
     * 
     * */
    static long double calc_single_E_angle(double ks, double psi_actual, double psi_const) {

        return (ks / 2.0) * (psi_actual - psi_const) * (psi_actual - psi_const) ;

    }








    /**
     * Simulated Annealing Evaluation:
     * A long long loop if you chose the value too high.
     * ( -> you have time for a coffee or two or more in this case)
     * Otherwise, an energetic simulated annealing will quickly spit out,
     * which you can use to build a nice HIN file.
     *
     * @param loops loop count for this annealing
     * */
    long double evaluate(int loops);



    int Temperature = 300; // 300K
    vector<long double> loop_results;
    
    //Molecule Mol;

};


#endif //ANNEALING_H

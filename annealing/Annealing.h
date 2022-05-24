//
// Created by manjaro on 19.05.22.
//

#ifndef ANNEALING_H
#define ANNEALING_H

#include <complex>
#include <vector>
#include <BALL/KERNEL/molecule.h>
#include <BALL/FORMAT/HINFile.h>
#include <BALL/KERNEL/atom.h>
#include <BALL/KERNEL/PTE.h>
#include <BALL/KERNEL/system.h>


using namespace std;
using namespace BALL;

#define AvocadoConst 6.02214086e+23  // Avocado Contant
#define BoltzConst 1.38064852e-23    // Boltzmann Constant
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

            BALL::HINFile HF("../H2O.hin");

            this->molecule = HF.read();


    }



    /**
     * Create an HIN File with the actual
     * Molecule informations
     *
     * @param filename output file path
     * */
    void createHINFile(string filename) {
        BALL::HINFile out("../out.hin",std::ios::out);
        System S;
        S.append(*molecule);
        out.write(S);
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

    long double calc_energy() const;

    int Temperature = 300; // 300K
    vector<long double> loop_results;
    Molecule* molecule; // Molekül der Hin-Datei
    
    //Molecule Mol;

};


#endif //ANNEALING_H

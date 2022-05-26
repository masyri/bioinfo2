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
#include <BALL/KERNEL/bond.h>
#include "Water.h"

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

        if (optima.size() < 1) {std::cout << "Error, no annealing started "; return;}

        BALL::HINFile out(filename,std::ios::out);

        Water best = optima.back();

        System S("jep");

        Molecule mol("Your temperature stressed and freezed water molecule :D");

        //

        BALL::Atom Ox;
        BALL::Atom H1;
        BALL::Atom H2;

        auto oxy = PTE[Element::O];
        auto hyd = PTE[Element::H];

        Ox.setElement(oxy);
        H1.setElement(hyd);
        H2.setElement(hyd);

        Ox.setName("Oxy");
        H1.setName("Hydro");
        H2.setName("Hydro");

        Ox.createBond(H1);
        Ox.createBond(H2);
        H1.createBond(Ox);
        H2.createBond(Ox);
        
        Ox.setPosition(Vector3(0,0,0));
        H1.setPosition(Vector3(0,best.length1,0));
        H2.setPosition(Vector3(best.length2,0,0));

        mol.insert(Ox);
        mol.insert(H1);
        mol.insert(H2);

        double angle_i  = best.angle;
        Angle angle(angle_i, false);
        Vector3 rotationaxis(1., 0., 0.);

        Matrix4x4 mat;
        mat.setRotation(angle, rotationaxis);

        //

        S.insert(mol);

        cout << "Atom-Count in Molecule: " << S.countAtoms() <<" \n";

        out.write(S);
    }





    /**
     * Create an optimum file with optimum informations
     * after each loop step
     *
     * @param filename output file path
     * */
    void createOptimumFile(string filename) {

        std::ofstream out(filename);

        // energy | temperature | angle | length1 | length2
        out << "\"Energy\";" << "\"temperature\";" << "\"angle\";" << "\"length1\";" << "\"length2\"" << "\n";

        // lines:
        for (Water mol : this->optima) {
           out << "\n" << mol.CSV_line();
        }

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
    static long double probability_formula (long double E_new,long double E_old, long double T) {

        long double diff = (E_new - E_old);
        long double div = AvocadoConst * BoltzConst * T;
        long double res = std::pow(2.71828182845904523536,- diff / div);
        return res;

    }




    /**
     * Returns with probability of bigP true otherwise false
     *
     * @param bigPee : your probability
     * */
     static bool probability(long double bigPee)
    {
         if (bigPee <= 0) {return false;}
         if (bigPee >= 1) {return true;}

         long double smallPee = random(0,1000000000);

         smallPee /= 1000000000;

         return smallPee < bigPee;

    }





    /**
     * Change Molecule conformations as the name implies :D
     * */
    void assignRandomConformation(Water* mol) {

        // sollen beide Bonds dieselbe oder unterschiedliche Längen bekommen?
        mol->length1 = random(0.7,1.3);
        mol->length2 = random(0.7,1.3);

        // angle
        mol->angle = random(100,120);


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




    /**
     * calc energy of a molecule
     * 
     * @param mol 
     * 
     * */
    long double calc_energy(Water* mol) const;


    vector<Water> optima;
    Molecule* molecule; // Molekül der Hin-Datei

};




#endif //ANNEALING_H

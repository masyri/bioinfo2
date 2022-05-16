//
// Created by manjaro on 12.05.22.
//

#ifndef CCP_SCORING_H
#define CCP_SCORING_H


#include "Amino.h"
#include "Probability.h"


class Scoring {

    public:


    /**
     * create a Scoring matrix from probability and occurence-matrix
     *
     * @param occur  an occurence-matrix
     * @param prob   a probability matrix 
     */
    explicit Scoring(Occurrence occur, Probability prob);




    /**
     * returns value from matrix
     *
     * @param row,column  position
     */
    double getValue(int row, int column) {
        return this->matrix.getValue(row,column);
    }




    /**
     * returns a Scoring value
     *
     * @param Wak     : if Wak !=  then returns -ln(Wak)
     * @param Nak     : if Nak = 0 then returns -500
     * @return double : calculated Score
     */
    double Sak(double Wak, double Nak);




    /** 
     * Print matrix to console without amino-acid names
     **/
    void print() { matrix.print(3); }




    /** 
     * Print matrix to console with amino-acid names
     **/
    void print_styled() {

        // column size fix:
        int num = (int)to_string(matrix.getBiggest()).size();
        int knum = (int)to_string(matrix.countColumns()).size();
        if (knum > num) {num = knum;}

        // print title line
        int cut = 0;
        std::cout << "\n" <<  C::BWHITE << "                | ";
        for (int k = 0; k < matrix.countColumns(); k++) {
            if (cut > 20) {break;}cut++;
            std::cout << setw(5) << k << " ";
        }

        // print matrix
        for (int i = 0; i < 20; i++) {
            // show name
            std::cout << "\n" << C::BWHITE << lines(i) ;
            // print columns
            cut = 0;
            for (int k = 0; k < matrix.countColumns(); k++ ) {
                if (cut > 20) {break;}cut++;
                double value = matrix.getValue(i,k);
                 string v = to_string(value).substr( 0,5 );
                if (value == 500.0)  {std::cout << C::BYELLOW;} else if (value == -500.0) {std::cout << C::BRED;} else {std::cout << C::BMAGENTA;}
                std::cout << setw(5) << v << " " << C::RESET;
            }
        }
        std::cout << "\n";
    }



    // statistics
    int val500 = 0;
    int valn500 = 0;
    int vallog = 0;


private:

    Matrix<double> matrix = Matrix<double>(21,1,0);

};


#endif //CCP_SCORING_H

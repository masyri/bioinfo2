//
// Created by manjaro on 12.05.22.
//

#ifndef CCP_PROBABILITY_H
#define CCP_PROBABILITY_H


#include "Occurrence.h"


class Probability {

public:


    /** 
     * Create a probability matrix from a occurrence-matrix
     *
     * @param occur  an occurence-matrix
     */
    explicit Probability(Occurrence occur);




    /**
     * returns value from matrix
     *
     * @param row,column  position
     */
    double getValue(int row, int column) {
        return this->matrix.getValue(row,column);
    }




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
                if (value > 0)  {std::cout << C::BYELLOW;} else {std::cout << C::BRED;}
                std::cout << setw(5) << v << " " << C::RESET;
            }
        }
        std::cout << "\n";
    }




private:

    Matrix<double> matrix = Matrix<double>(21,1,0);


};


#endif //CCP_PROBABILITY_H

//
// Created by manjaro on 12.05.22.
//

#ifndef CCP_SCORING_H
#define CCP_SCORING_H


#include "Amino.h"
#include "Probability.h"


class Scoring {

    public:

    explicit Scoring(Occurrence occur, Probability prob);

    double getValue(int row, int column) {
        return this->matrix.getValue(row,column);
    }

    /**
     * returns a Scoring value
     *
     * @param Wak     : if Wak !=  then returns -ln(Wak)
     * @param Nak     : if Nak = 0 then returns -500
     * @return double :
     */
        static double Sak(double Wak, double Nak);

    /** Print matrix to console without amino-acid names
     *
     **/
    void print() { matrix.print(3); }



    /** Print matrix to console with amino-acid names
     *
     **/
    void print_styled() {

        // column size fix:
        int num = (int)to_string(matrix.getBiggest()).size();
        int knum = (int)to_string(matrix.countColumns()).size();
        if (knum > num) {num = knum;}

        // print title line
        std::cout << "\n" <<  C::BWHITE << "                | ";
        for (int k = 0; k < matrix.countColumns(); k++) {
            std::cout << setw(num) << k << " ";
        }

        // print matrix
        for (int i = 0; i < 20; i++) {
            // show name
            std::cout << "\n" << C::BWHITE << lines(i) ;
            // print columns
            for (int k = 0; k < matrix.countColumns(); k++) {
                double value = matrix.getValue(i,k);
                if (value > 0)  {std::cout << C::BYELLOW;} else {std::cout << C::BRED;}
                std::cout << setw(num) << value << " " << C::RESET;
            }
        }
        std::cout << "\n";
    }

private:

    Matrix<double> matrix = Matrix<double>(21,1,0);



};


#endif //CCP_SCORING_H

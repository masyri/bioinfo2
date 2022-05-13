//
// Created by manjaro on 12.05.22.
//

#ifndef CCP_OCCURRENCE_H
#define CCP_OCCURRENCE_H

#include "../matrix/Matrix.h"
#include "Amino.h"
#include "../console/Color.h"

/*

  O C C U R R E N C E  -  M A T R I X


 __a__|_0_|_1_|_2_|_k_ <- contact count k
  "A" | 0 | 0 | ...
  "M" | 0 | 0 | ...
  "I" | 0 | 2 | 4  <- occurrence of an amino 'a' with 'k' contacts
  "N" | 0 | 1 | ...
  "O" | ...
  "S" | ...
  ... | ...

 Example: AminoAcid 'N' occurs 4 times with
 2 contacts to another amino-acid and 2 times with 1 contact to
 another amino acid

 **/





// Soll das Auftreten 'Kontakte k = 0' auch gezählt werden? macht doch eigentlich keinen Sinn ???

// Was ist mit den 'Unknown' Aminosäuren ? ignorieren ?




class Occurrence {

public:

    Occurrence()= default;


    /**
     * Add a new occurrence to the matrix.
     *
     * @param amino         : Type of the Aminoacid
     * @param contact_count : the count of contacts to another amino acids
     **/
    void insert(AA amino, int contact_count) {

        // row of the matrix = Amino
        int AA_index = static_cast<int>(amino);

        // if the matrix too small, make it bigger
        bool oo_bounds = contact_count >= matrix.countColumns();
        if (oo_bounds) {
            matrix.reSize(21,contact_count + 1,0);
        }

        // old value -> new value (raise by one)
        int old_value = this->matrix.getValue(AA_index,contact_count);
        old_value++;
        this->matrix.setValue(AA_index, contact_count, old_value);

    }



    int getOccurrences(AA amino,int contact_count) {
        int AA_index = static_cast<int>(amino);
        return this->matrix.getValue(AA_index,contact_count);
        }

    int getValue(int row, int column) {
        return this->matrix.getValue(row,column);
    }



    /**
     * returns the count of Columns
     *
    */
    int getColumnCount() {
         return this->matrix.countColumns();
    }




    /**
     * count all Residues in this matrix
     *
    */
    int countResidues() {
        int count = 0;
        for (int as = 0 ; as < 20 ; as++) {
            for (int k = 0 ; k < getColumnCount() ; k++) {
                count += this->matrix.getValue(as,k);
            }
        }
        return count;
    }



    /**
     * count all Residues of a amino type in this matrix
     *
     * @param amino : type of amino
    */
    int countResidues(AA amino) {
        int AA_index = static_cast<int>(amino);
        int count = 0;
        for (int k = 0 ; k < getColumnCount() ; k++) {
            count += this->matrix.getValue(AA_index,k);
        }
        return count;
    }


    /**
     * count all Residues with k contacts in this matrix
     *
     * @param k : count of contacts
    */
    int countResidues(int k) {
        int count = 0;
        for (int as = 0 ; as < 20 ; as++) {
                count += this->matrix.getValue(as,k);
        }
        return count;
    }




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
        int cut = 0;
        std::cout << "\n" <<  C::BWHITE << "                | ";
        for (int k = 0; k < matrix.countColumns(); k++) {
            if (cut > 25) {break;}cut++;
            std::cout << setw(num) << k << " ";
        }

        // print matrix
        for (int i = 0; i < 20; i++) {
            // show name
            std::cout << "\n" << C::BWHITE << lines(i);
            cut = 0;
            // print columns
            for (int k = 0; k < matrix.countColumns(); k++) {
                if (cut > 25) {break;}cut++;
                int value = matrix.getValue(i,k);
                if (value < 1) {std::cout << C::BRED;} else {std::cout << C::BYELLOW;}
                std::cout << setw(num) << value << " " << C::RESET;
            }
        }
        std::cout << "\n";
    }

int all_residues  = 0;
int near_residues = 0;
int zerocontact_residues = 0;
int contact_unknowns      = 0;
int amino_unknown = 0;

private:

    Matrix<int> matrix = Matrix<int>(21,1,0);

};


#endif //CCP_OCCURRENCE_H


#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;



/**
 * Type-templated and resizable Matrix.
 * Min size is: 1 row + 1 column.
 *
 */
template <typename MatType>
class Matrix {

public:

    

    /**
     * Create a Matrix.
     * Example 'Matrix<int> values(4,5,-1);'
     *
     * @param rows          : count of rows. Min >=1
     * @param columns       : count of columns. Min >=1
     * @param initial_value : start values in the fields after creating
     * */
    Matrix(int rows, int columns, MatType initial_value) {
        //std::cout << "\n Matrix created: r: " << rows << " c: " << columns << " init: " << initial_value;

        for (int r = 0 ; r < rows ; r++){
            vector<MatType> col;
            for (int c = 0 ; c < columns ; c++){
                col.template emplace_back(initial_value);
            }
            this->_rows.template emplace_back(col);
        }
    }





    /**
     * Change the Size of this  Matrix.
     * All old values (which inbound for the new matrix-size) will copy
     *
     * @param rows          : count of rows. Min >=1
     * @param columns       : count of columns. Min >=1
     * @param initial_value : start values in the fields after creating
    * */
    void reSize(int rows, int columns, MatType initial_value) {

        vector<vector<MatType>> _new_rows;

        for (int r = 0 ; r < rows ; r++){
            vector<MatType> col;
            for (int c = 0 ; c < columns ; c++){

                MatType val = initial_value;

                // copy old values
                bool inbound_row = r < _rows.size();
                bool inbound_col = c < _rows[0].size();
                if (inbound_row && inbound_col) { val = this->getValue(r,c); }

                col.template emplace_back(val);

            }
            _new_rows.template emplace_back(col);
        }
        this->_rows = _new_rows;
    }





    /**
     * Get row size from this matrix
     *
     * */
    int countRows()    { return this->_rows.size();}





    /**
     * Get column size from this matrix
     *
     * */
    int countColumns() { return this->_rows[0].size();}





    /**
     * Get a value from this matrix
     * 
     * @param row,column position
     *
     * */
    MatType getValue(int row, int column)             { return this->_rows[row][column]; }





    /**
     * returns the biggest element of this matrix
     *
     * */
    MatType getBiggest() {

        MatType comp = _rows[0][0];

        for(vector<MatType> r : _rows ) {
            for (MatType c : r) {
                if (c > comp) {comp = c;}
            }
        }
        return comp;
    }




    /**
     * Set a value in this matrix
     * 
     * @param rot,column position
     * @param value new value
     *
     * */
    void setValue(int row, int column, MatType value) { this->_rows[row][column] = value;}




    /**
     * Print the matrix to console (for testing)
     *
     * @param column_text_width : Console print-width for every column (fix different value-text-length for better readability)
     * */
    void print(int column_text_width) {
        cout << BBLUE << "\n[MATRIX] rows: " << BLUE << countRows() << BBLUE << " cols: " << BLUE << countColumns();
        int row = 0;int col = 0;
        cout << BWHITE << "\n" << "   " << "   ";
        for ( auto c : _rows[0]) { cout << BWHITE << setw(column_text_width) << col << " " << GREEN;col++;(void)c; }

        for (auto r : _rows) {
            cout << "\n" << BWHITE << setw(3) << row << " | " << GREEN;row++;
            for (auto c_val : r) { cout << setw(column_text_width) << c_val << " "; }
        }
        cout << RESET << "\n";
    }




private:

    // value-stack
    vector<vector<MatType>> _rows;

    // for console print
    const char* RESET   = "\033[0m";
    const char* BLUE    = "\033[0;34m";
    const char* BBLUE   = "\033[1;34m";
    const char* BWHITE  = "\033[1;37m";
    const char* GREEN   = "\033[0;32m";

};

#endif //MATRIX_H

//
// Created by manjaro on 02.06.22.
//

#ifndef RMSD_H
#define RMSD_H


#include "Space.h"

class RMSD {

public:

    RMSD() = default;

    Space P;  // Original P
    Space Q;  // Original Q
    Space Pc; // Centered P
    Space Qc; // Centered Q

    static Space getTestSetP();
    static Space getTestSetQ();

};


#endif //RMSD_H

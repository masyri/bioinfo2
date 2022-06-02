//
// Created by manjaro on 02.06.22.
//

#include "RMSD.h"






Space RMSD::getTestSetP() {
    Space S;
    S.addPosition("P.01",-4,-1,7);
    S.addPosition("P.02",-1,-2,7);
    S.addPosition("P.03",-8,4,7);
    S.addPosition("P.04",-5,4,5);
    S.addPosition("P.05",-1,-2,11);
    S.addPosition("P.06",-3,2,6);
    return S;
}

Space RMSD::getTestSetQ() {
    Space S;
    S.addPosition("Q.01",1,2,3);
    S.addPosition("Q.02",1,1,6);
    S.addPosition("Q.03",1,9,-1);
    S.addPosition("Q.04",3,7,2);
    S.addPosition("Q.05",-3,1,6);
    S.addPosition("Q.06",2,5,1);
    return S;
}

//
// Created by manjaro on 12.05.22.
//

#include <vector>
#include "Amino.h"

AA char2Amino(char c) {
    switch (c) {

        case 'A' : return  Alanin;        // Ala	A
        case 'R' : return  Arginin;       // Arg	R
        case 'N' : return  Asparagin;     // Asn	N
        case 'D' : return  Asparaginacid; // Asp	D
        case 'C' : return  Cystein;       // Cys	C

        case 'Q' : return  Glutamin;      // Gln	Q
        case 'E' : return  Glutaminacid;  // Glu	E
        case 'G' : return  Glycin;        // Gly	G
        case 'H' : return  Histidin;      // His	H
        case 'I' : return  Isoleucin;     // Ile	I

        case 'L' : return  Leucin;        // Leu	L
        case 'K' : return  Lysin;         // Lys	K
        case 'M' : return  Methionin;     // Met	M
        case 'F' : return  Phenylalanin;  // Phe	F
        case 'P' : return  Prolin;        // Pro	P

        case 'S' : return  Serin;         // Ser	S
        case 'T' : return  Threonin;      // Thr	T
        case 'W' : return  Tryptophan;    // Trp	W
        case 'Y' : return  Tyrosin;       // Tyr	Y
        case 'V' : return  Valin;         // Val	V

        default:
            break;

    };

    return Unknown;
}

// Text lines for print
string lines(int i) {

    vector<string> _lines = {
            "Alanin        A | ", "Arginin       R | ", "Asparagin     N | ", "Asparaginacid D | ",
            "Cystein       C | ", "Glutamin      Q | ", "Glutaminacid  E | ", "Glycin        G | ",
            "Histidin      H | ", "Isoleucin     I | ", "Leucin        L | ", "Lysin         K | ",
            "Methionin     M | ", "Phenylalanin  F | ", "Prolin        P | ", "Serin         S | ",
            "Threonin      T | ", "Tryptophan    W | ", "Tyrosin       Y | ", "Valium        V | ",
            "Unknown       ? | "

    };

    return _lines[i];

};
//
// Created by manjaro on 12.05.22.
//

#ifndef CCP_AMINO_H
#define CCP_AMINO_H

#include <string>

using namespace std;

enum AA {

     Alanin          //	Ala	A
    ,Arginin         //	Arg	R
    ,Asparagin       //	Asn	N
    ,Asparaginacid   //	Asp	D
    ,Cystein         // Cys	C

    ,Glutamin        //	Gln	Q
    ,Glutaminacid    //	Glu	E
    ,Glycin          //	Gly	G
    ,Histidin        //	His	H
    ,Isoleucin       //	Ile	I

    ,Leucin          //	Leu	L
    ,Lysin           //	Lys	K
    ,Methionin       //	Met	M
    ,Phenylalanin    //	Phe	F
    ,Prolin          //	Pro	P

    ,Serin           //	Ser	S
    ,Threonin        //	Thr	T
    ,Tryptophan      //	Trp	W
    ,Tyrosin         //	Tyr	Y
    ,Valin	         // Val	V

    ,Unknown

};


AA char2Amino(char c);

string lines(int i);

#endif //CCP_AMINO_H

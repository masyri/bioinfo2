//
// Created by manjaro on 21.04.22.
//

#include "DSSP.h"



/**
 * Calculates the position from the H-Atom
 * @C_start The first C-Atom
 * @C_end   The second C-Atom
 * @N_Mid   The N-Atom
 * @return  H-Atom position in N-Direction
 */
Vector3 DSSP::calculate_H_position(Vector3 C_start, Vector3 C_end, Vector3 N_Atom ) {
    Vector3 M_Point = (C_end - C_start) / 2.0;
    Vector3 direction = N_Atom - M_Point;
    return direction.normalize() * 1.02;

}






void DSSP::getGroups(){

    // Iteration over Resiudes

    BALL::ResidueIterator resit = S.beginResidue();
    for (; +resit ; ++resit)
    {

        // Read index from this residue
        int ID = atoi(resit->getID().c_str());
       
        AtomIterator a_it = resit->beginAtom();

        if(a_it->getElement() == PTE[Element::N]) {

            // get N Atom
            Atom* atomN = &*a_it;
            
            // get C Atom from NH
            a_it++;
            Atom* atomC_N = &*a_it; 

            // get C Atom from CO
            a_it++;
            Atom* atomC_O = &*a_it;

            // get O Atom
            a_it++;
            Atom* atomO = &*a_it;

            // Get H Atom
            Atom* atomH;
            //auto hyd = PTE[Element::H];
            //atomH->setElement(hyd);

            Vector3 position_C_N = atomC_N->getPosition();
            Vector3 position_N   = atomN->getPosition();
            Vector3 position_C_O = atomC_O->getPosition();
            Vector3 position_H   = calculate_H_position(position_C_N, position_N, position_C_O);


            atomH->setPosition(position_H);


            // indieces in gruppen speichern

            // create NH Group

            NH_Group nh(atomH,atomN,ID);
            this->NH_Groups.push_back(nh);
            
            // create CO Group

            CO_Group co(atomC_O,atomO,ID);
            this->CO_Groups.push_back(co);

            // push NH to Space

            space.pushToSpace(position_H.x , position_H.y , position_H.z , nh);

        }

    }
}





DSSP::DSSP(BALL::System S) {

    this->S = S;

    // open a fragment database
        FragmentDB fragment_db("");

    // add hydrogens
        //S.apply(fragment_db.add_hydrogens);

    // Create Coordinate Space
      
        this->space =   Space3D( S , 8.0 );

    // iterate over all atoms to find NH- and CO-Groups

/*

    for(auto iter=S.atoms().begin();iter!=S.atoms().end();iter++) // Hoffe der Iterator wird so initialisiert und funktioniert so
        {
        Atom A = iter.operator*();

        // Which element?
        Element el = A.getElement();

        // if N-Atom:
        if (el.getSymbol() == Element::N) { // hoffe der Vergleich funktioniert
            // Hier noch nicht fertig, es muss das H-Atom gefunden werden per Bond und dann
            // In die Atom *H-Variable gesteckt werden (dabei checken ob das H überhaupt erzeugt wurde)
            Atom *N = &A;
            Atom *H;

            // Add found Atoms to Group and add to List
            NH_Group nh(H,N);
            this->NH_Groups.push_back(nh);
        }

        // if N-Atom:
        if (el.getSymbol() == Element::O) { // hoffe der Vergleich funktioniert
            // Hier noch nicht fertig, es muss das C-Atom gefunden werden per Bond und dann
            // In die Atom *H-Variable gesteckt werden
            Atom *O = &A;
            Atom *C;

            // Add found Atoms to Group and add to List
            CO_Group co(C,O);
            this->CO_Groups.push_back(co);
        }
    }*/

}








void DSSP::startAlgorithm() {

        for(CO_Group CO : CO_Groups) {

        // look for the position of the O-Atom of this Group
        Vector3 pos = CO.O->getPosition();
        double x = pos.x;
        double y = pos.y;
        double z = pos.z; 

        // look for all near NH-Groups/H-Atoms
        std::vector<NH_Group*> near_NHgroups = space.search( x,  y,  z);

        // Iteriere über alle NH-Gruppen, die in den Koordinatenboxen liegen

        for(NH_Group *NH : near_NHgroups) {

            if (CO.checkDistance(*NH,2.5)) {

                // check for the other values:
                bool energy = CO.checkEnergy(*NH,1.0);
                bool angle = CO.checkAngle(*NH,120.0);
                if (energy && angle) { // if all values correct add this as a Hydrogen-Bond to results
                    IJ_Tuple ij(*NH,CO);
                    this->result.push_back(ij);
                }
            }
        }

}
}
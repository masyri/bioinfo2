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
    Vector3 M_Point = C_start + ((C_end - C_start) / 2.0);
    Vector3 direction = N_Atom - M_Point;
    return N_Atom + (direction.normalize() * 1.02);

}






void DSSP::getGroups(){

    // Iteration over Residues

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

            Vector3 position_C_N = atomC_N->getPosition();
            Vector3 position_N   = atomN->getPosition();
            Vector3 position_C_O = atomC_O->getPosition();

            Vector3 position_H   = calculate_H_position(position_C_N, position_C_O, position_N);


            atomH->setPosition(position_H);

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

    // Create Coordinate Space
      
        this->space =   Space3D( S , 8.0 );

    // statistics for testing

    std::stringstream s("");
    int i = 0;
    for (ProteinIterator p_iter = S.beginProtein(); +p_iter; ++p_iter) {
        s << S.getProtein(0)->getID() << " / " << p_iter->getName();i++;

    }

    this->names = s.str();



}








void DSSP::startAlgorithm() {

        for(CO_Group CO : CO_Groups) {

        // look for the position of the O-Atom of this Group
        Vector3 pos = CO.O->getPosition();

        // Iteriere über alle NH-Gruppen, die in den Koordinatenboxen liegen

        for(NH_Group NH : NH_Groups) {

            if (pos.getDistance(NH.H->getPosition()) < 8.5) {

                // check for the other values:
                bool energy = CO.checkEnergy(NH,-0.5);
                bool angle = CO.checkAngle(NH,120.0);
                if (energy && angle) { // if all values correct add this as a Hydrogen-Bond to results
                    IJ_Tuple ij(NH,CO,NH.index,CO.index);
                    this->result.push_back(ij);
                }
            }
        }

}}

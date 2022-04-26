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
    Vector3 M_Point = C_end - C_start / 2.0;
    Vector3 direction = N_Atom - M_Point;
    return direction.normalize * 1.02;

}


Space3D create(System S) {

    double max_x = 0;
    double max_y = 0;
    double max_z = 0;

    double min_x = 0;
    double min_y = 0;
    double min_z = 0;

    BALL::ResidueIterator resit = S.beginResidue();
    for (; +resit ; ++resit) {
        AtomIterator a_it = resit->beginAtom();
        if (a_it->getElement() == PTE[Element::N]) {

            Atom *atomN = &*a_it;

            double px = atomN->getPosition().x;
            double py = atomN->getPosition().y;
            double pz = atomN->getPosition().z;

            if (px > max_x) {max_x = px;}
            if (py > max_y) {max_y = py;}
            if (pz > max_z) {max_z = pz;}

            if (px < min_x) {min_x = px;}
            if (py < min_y) {min_y = py;}
            if (pz < min_z) {min_z = pz;}

            a_it++;
        }
    }

    std::cout << "\n x " << min_x << " " << max_x;
    std::cout << "\n y " << min_y << " " << max_y;
    std::cout << "\n z " << min_z << " " << max_z;
    std::cout << "\n z ";



}





void DSSP::getGroups(){
    // Iteration over Resiudes
    // für jede aminosäure schauen ob sie WSBB mit einer anderen ausbildet
    BALL::ResidueIterator resit = S.beginResidue();
    for (; +resit ; ++resit)
    {
       
        AtomIterator a_it = resit->beginAtom();
        if(a_it->getElement() == PTE[Element::N]){
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
        auto hyd = PTE[Element::H];
        atomH->setElement(hyd);

        Vector3 position_C_N = atomC_N->getPosition();
        Vector3 position_N = atomN->getPosition();
        Vector3 position_C_O = atomC_O->getPosition();

        atomH->setPosition(calculate_H_position(position_C_N, position_N, position_C_O));

    // indieces in gruppen speichern
        // create NH Group
        NH_Group nh(atomH,atomN);
        this->NH_Groups.push_back(nh);
        // create CO Group
        CO_Group co(atomC_O,atomO);
        this->CO_Groups.push_back(co);
        }

    }
}


DSSP::DSSP(BALL::System S) {

    this->S = S;

    // open a fragment database
    FragmentDB fragment_db("");

    // add hydrogens
    //S.apply(fragment_db.add_hydrogens);

    // ToDo: Space3D erstellen und alle Groups einsortieren, dazu berechnen wie groß die max-Koordinaten sind

    create(S);

    //Space3D sss(100,100,100,10);

    //this->Space =  sss;

    return;

    // iterate over all atoms to find NH- and CO-Groups
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
        }
}





void DSSP::startAlgorithm() {

    Space3D Space(100,100,100,10);

        for(CO_Group CO : CO_Groups) {

        // look for the position of the O-Atom of this Group
        Vector3 pos = CO.O->getPosition();
        double x = pos.x;
        double y = pos.y;
        double z = pos.z; 

        // look for all near NH-Groups/H-Atoms
        std::vector<NH_Group*> near_NHgroups = Space.search( x,  y,  z);

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

//
// Created by manjaro on 21.04.22.
//

#include "DSSP.h"




DSSP::DSSP(BALL::System S) {

    this->S = S;

    // open a fragment database
    FragmentDB fragment_db("");

    // add hydrogens
    S.apply(fragment_db.add_hydrogens);


    // ToDo: Space3D erstellen und alle Groups einsortieren, dazu berechnen wie groß die max-Koordinaten sind



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
            CO_Group co(&C,&O);
            this->CO_Groups.push_back(co);
        }
        }
}





void DSSP::startAlgorithm() {

    //
    // Dieser Algorithmus sollte funktionieren (Wenn die beiden Listen korrekt gefüttert worden)
    //
    // (ist wahrscheinlich nicht schnell genug, da bei jedem CO jedesmal alle NHs abgesucht werden)
    //

    // run over all CO-Groups

    for(CO_Group CO : CO_Groups) {

        // look for a NH-group with correct distance / run over all NH-Group and calc distances
        NH_Group *found_NH;
        for(NH_Group NH : NH_Groups) {
            if (CO.checkDistance(NH,2.5)) {
                found_NH = &NH;
                // check for the other values:
                bool energy = CO.checkEnergy(NH,1.0);
                bool angle = CO.checkAngle(NH,120.0);
                if (energy && angle) { // if all values correct add this as a Hydrogen-Bond to results
                    IJ_Tuple ij(NH,CO);
                    this->result.push_back(ij);
                }
            }
        }
    }


    //
    //
    // Alternative Box-Suche
    //

        for(CO_Group CO : CO_Groups) {

        // look for the position of the O-Atom of this Group
        Vector3 pos = CO.O->getPosition();
        double x = pos.x;
        double y = pos.y;
        double z = pos.z; 

        // look for all near NH-Groups/H-Atoms
        std::vector<NH_Group*> near_NHgroups = Space.search( x,  y,  z);

        // Iteriere über alle NH-Gruppen, die in den Koordinatenboxen liegen
        for(NH_Group NH : near_NHgroups) {
            if (CO.checkDistance(NH,2.5)) {
                found_NH = &NH;
                // check for the other values:
                bool energy = CO.checkEnergy(NH,1.0);
                bool angle = CO.checkAngle(NH,120.0);
                if (energy && angle) { // if all values correct add this as a Hydrogen-Bond to results
                    IJ_Tuple ij(NH,CO);
                    this->result.push_back(ij);
                }
            }
        }
    }




}
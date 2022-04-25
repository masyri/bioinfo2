//
// Created by manjaro on 21.04.22.
//

#include "DSSP.h"

bool DSSP::checkEnergy(BALL::Atom* atomN, BALL::Atom* atomO, BALL::Atom* atomH, BALL::Atom* atomC) {
        
        double f_d1_d2 = 27.888; 

        double dist_NO =  atomN->getPosition().getDistance(atomO->getPosition());
        double dist_HC =  atomH->getPosition().getDistance(atomC->getPosition());
        double dist_HO =  atomH->getPosition().getDistance(atomO->getPosition());
        double dist_NC =  atomN->getPosition().getDistance(atomC->getPosition());

        auto e = f_d1_d2 * ( 1 / dist_NO + 1 / dist_HC - 1 / dist_HO - 1 / dist_NC );
    cout << e << endl;
    return e < -0.5;
}

bool DSSP::checkDistance(BALL::Atom* atomH, BALL::Atom* atomO) {
    
    auto dist = atomH->getPosition().getDistance(atomO->getPosition());
    cout << dist << endl;
    return dist < 2.5 ;
}

bool DSSP::checkAngle(BALL::Atom* atomN, BALL::Atom* atomO, BALL::Atom* atomH) {
/*
    // get position of 3 points
        Vector3 position_H = atomH->getPosition();
        Vector3 position_N = atomN->getPosition();
        Vector3 position_O = atomO->getPosition();
        cout << position_H << endl;
        cout << position_N << endl;
        cout << position_O << endl;
        // make 2 vectors which starts at the H-Atom in the direction to the N-Atom and the O-Atom
        Vector3 vector_H_N = position_N - position_H;
        Vector3 vector_H_O = position_N - position_H; // Hab ich die beiden Vektoren jetzt richtig erstellt?

        double angle = vector_H_N.getAngle(vector_H_O); // ist der Return dieser Methode in Grad oder im Whatever-Maß ? Ist wichtig wegen dem vergleichen mit dem min_angle von 120°
        cout << angle << endl;
    */
   int angle = 130;
    return angle >= 120;
}

// dauert wahrscheinlich zu lange, da alle amino mit allen amino getestet werden
void DSSP::findWSBB(){
    // Iteration over Resiudes
    // für jede aminosäure schauen ob sie WSBB mit einer anderen ausbildet
    BALL::ResidueIterator resit = S.beginResidue();
    for (; +resit ; ++resit)
    {
        std::cout << "Current residue: " << resit->getFullName() << std::endl;

        // get N Atom
        AtomIterator a_it = resit->beginAtom();
        if(a_it->getElement() == PTE[Element::N]){
        Atom* atomN = &*a_it;
         cout << "ATOMN "<< atomN->getElement().getSymbol() << endl;
        // get C Atom
        a_it++;
        Atom* atomC_N = &*a_it;     //c atom von N gruppe
        cout << "ATOMC "<< atomC_N->getElement().getSymbol() << endl;
        }

        // // Iteration over Resiudes
        // für die momentane Aminosäure testen mit jeder anderen
        BALL::ResidueIterator resit2 = S.beginResidue();
        for (; +resit2 ; ++resit2)
        {
            std::cout << "Current residue2: " << resit2->getFullName() << std::endl;
            // get C atom
            AtomIterator a_it2 = resit2->beginAtom();
            if(a_it2->getElement() == PTE[Element::N]){
            a_it2++;
            a_it2++;
            Atom* atomC_O = &*a_it2;
            cout << "ATOM C O "<< atomC_O->getElement().getSymbol() << endl;
            // get O atom
            a_it2++;
            Atom* atomO = &*a_it2;
            cout << "ATOMO "<< atomO->getElement().getSymbol() << endl;
        }

       
       // H-Atom berechnen bzw erstellen
       //Berechnen Sie die Position des ben¨otigten Wasserstoffs: Dieser liegt in der durch die
        //Peptidbindung definierten Ebene und halbiert den (gr¨oßeren) Winkel zwischen N
        //und den angrenzenden Kohlenstoffen. Die L¨ange der Bindung zwischen N und H
        //betr¨agt 1.02 ˚A
        Atom* atomH = &*a_it;

        // Test ob zwischen dem NH und dem CO eine WSBB besteht
        /*
        //check if E(i, j) < −0.5 kcal /mol
        if(checkEnergy(atomN, atomO, atomH, atomC_O)){
        // check if θNHO > 120° 
        if(checkAngle(atomN, atomO, atomH)){
        // check if d(Oj, Hi) < 2.5 ˚A
        if(checkDistance(atomH, atomO)){
            // add (resit,resit2) zu WSBB Tuple vektor
             cout << "WSBB wurde hinzugefügt  "<<  endl;
             WSBB_Tuple bridge(&*resit, &*resit2);
             wsbb.push_back(bridge);
        }}}
        break;*/
        }


    }
}


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
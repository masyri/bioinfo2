#include <BALL/FORMAT/PDBFile.h>
#include <BALL/STRUCTURE/peptides.h>
#include <BALL/STRUCTURE/fragmentDB.h>
#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/chain.h>
#include <BALL/KERNEL/protein.h>
#include <BALL/KERNEL/selector.h>
#include <BALL/KERNEL/PTE.h>
#include <iostream>

using namespace BALL;


void countAtom(ChainIterator ch_it){
            int C_count = 0;
            int N_count = 0;
            int O_count = 0;
            int H_count = 0;
            for (ResidueIterator r_it = ch_it->beginResidue(); +r_it; r_it++) {

                    // iterate over all atoms
                    AtomIterator a_it = r_it->beginAtom();
                    for (; +a_it; ++a_it)
                    {

                        if (a_it->getElement() == PTE[Element::C]){C_count++;}
                        if (a_it->getElement() == PTE[Element::N]){N_count++;}
                        if (a_it->getElement() == PTE[Element::O]){O_count++;}
                        if (a_it->getElement() == PTE[Element::H]){H_count++;}

                    }
                }

            std::cout << "\nNumber of carbon molecules: " << C_count << std::endl;
            std::cout << "Number of nitrogen molecules: " << N_count << std::endl;
            std::cout << "Number of oxygen molecules: " << O_count << std::endl;
            std::cout << "Number of hydrogen molecules: " << H_count << std::endl;
}


// WATER MOLECULES
void waterMolekules(System S){

// define the selector by Expression
        Selector wat("residue(HOH) OR residue(WAT)");
// apply
        S.apply(wat);
// count
        std::cout << "\nNumber of water molecules: " << wat.getNumberOfSelectedAtoms() << std::endl;
// remove
        S.removeSelected();
}


//One-Letter-Code/Three-Letter-Code
void letterCodes(ChainIterator ch_it){
        // get the One-Letter-Code sequence
        String ball_seq= "";
        for (ResidueIterator r_it = ch_it->beginResidue(); +r_it; r_it++) {
            if ((r_it->isAminoAcid()) && (r_it->getName() != String("ACE"))) {
                ball_seq += Peptides::OneLetterCode(r_it->getName());
            }
        }

        // One-Letter-Code
        std::cout << "\nOne letter code: " << ball_seq << std::endl;

// convert to three-letter code
        std::list<String> tlc_seq = Peptides::OneLetterToThreeLetter(ball_seq);

// Three-Letter-Code
        std::string ball2_seq;
        for(const auto &ami : tlc_seq)
        {
            ball2_seq += ami;
        }
        std::cout << "\nThree-letter-code: " << ball2_seq << std::endl;

}

int main(int argc, char* argv[]) {

    std::string arg_In = argv[1];
// read the PDB-file into a BALL::System
    PDBFile f(arg_In);
    System S;
    f >> S;

// now we open a fragment database
    FragmentDB fragment_db("");

// and normalize the atom names, i.e. we convert different
// naming standards to the PDB naming scheme - just in case!
    S.apply(fragment_db.normalize_names);

// now we add any missing hydrogens to the residues
// the data on the hydrogen positions stems from the
// fragment database. However the hydrogen positions
// created in this way are only good estimates
    S.apply(fragment_db.add_hydrogens);

// now we create the bonds between the atoms (PDB files hardly
// ever contain a complete set of CONECT records)
    S.apply(fragment_db.build_bonds);


// check the first molecule
    if (S.getProtein(0)) {
// cast the system's first molecule to BALL::Protein
        Protein *protein = S.getProtein(0);

// get the protein's sequence
        String ball2_seq = "";
        for (ChainIterator ch_it = protein->beginChain(); +ch_it; ++ch_it) {
            for (ResidueIterator r_it = ch_it->beginResidue(); +r_it; r_it++) {
                if ((r_it->isAminoAcid()) && (r_it->getName() != String("ACE"))) {
                    ball2_seq += Peptides::OneLetterCode(r_it->getName());
                }
            }
        }
        std::cout << "\nSequence: " << ball2_seq << std::endl;
        

// get the number of chains in the protein
        std::cout << "\nNumber of chains in the protein: " << protein->countChains() << std::endl;


// iterate over all chains
        int number = 1;
        for (ChainIterator ch_it = protein->beginChain(); +ch_it; ++ch_it) {
// get the number of residues per chain
            std::cout << "\n\nCHAIN " << number << std::endl;
            std::cout << "\nNumber of residues: " << ch_it->countResidues() << std::endl;
            letterCodes(ch_it);
            countAtom(ch_it);
            number++;
        }

// water molekules
        waterMolekules(S);

    }
}

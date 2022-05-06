//
// Created by manjaro on 06.05.22.
//

#include "Predictor.h"



/**
 *  P R E D I C T O R - C O N S T R U C T O R
 *
 *  Create from a List of PDB-Files a Set of Datasets for Prediction
 *  @filelist    PDB-File list
 *
 * */
Predictor::Predictor(vector<string> filelist) {

    // iterate over all files:

    for (const auto& file : filelist) {

        // open file:
        PDBFile f(file, ios::in);
        System S;
        f >> S;

        // extract all aminos
        auto amino_lists = getAminosFromMultipleProteins(S);

        // create datasets
        for (const auto& _aminos : amino_lists) {

            auto DS = createDatasetArrayFromProtein(_aminos);
            data_point_arrays.push_back(DS);
        }
    }

    // dfg





}



/**
 *  P R E D I C T O R - A M I N O - E X T R A C T
 *
 *  Extract all Aminos from all proteins of this System
 *  @S    Molecule System
 *
 * */
vector<vector<Amino>> Predictor::getAminosFromMultipleProteins(System S) {

    vector<vector<Amino>> _array;

    for(ProteinIterator protein = S.beginProtein(); +protein; ++protein) {

        // init Amino-List
        vector<Amino> _aminos;

        // create List of all Aminos of this protein and
        // store structure, id and code
        for (auto &iter: S.residues()){
            if (iter.isAminoAcid()){
                // Get Aminoacid ID
                int ID = atoi(iter.getID().c_str());
                // Get Aminoacid Char
                auto code = Peptides::OneLetterCode(iter.getName());
                // Get assigned structure
                auto SecStruct = iter.getSecondaryStructure()->getType();
                // Decision SS Type
                switch (SecStruct) {
                    case SecondaryStructure::HELIX:             _aminos.emplace_back(ID,'H',code,protein->getID()); break;
                    case SecondaryStructure::COIL:              _aminos.emplace_back(ID,'L',code,protein->getID()); break;
                    case SecondaryStructure::TURN:              _aminos.emplace_back(ID,'t',code,protein->getID()); break;
                    case SecondaryStructure::STRAND:            _aminos.emplace_back(ID,'S',code,protein->getID()); break;
                    case SecondaryStructure::UNKNOWN:           _aminos.emplace_back(ID,'u',code,protein->getID()); break;
                    default:                                    _aminos.emplace_back(ID,'-',code,protein->getID()); break;
                }
            }
        }
        // push to return list
        _array.push_back(_aminos);
    }
    // end

    return _array;
}



/**
 *  P R E D I C T O R - D A T A S E T
 *
 *  Build a DataPointArray from a Amino-Vector
 *  @aminos    List of aminos
 *
 * */
DataPointArray Predictor::createDatasetArrayFromProtein(vector<Amino> aminos) {

    vector<int> pos = { 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 , 12 };

    int max_neighbor = (int)aminos.size() - 1;

    DataPointArray AR((int)aminos.size());

    while(true) {

        // if less then 6 right neighbors => break
        if (pos[12] > max_neighbor) {break;}
        // create Datapoint on position with 6 left neighbors
        DataPoint datapoint(aminos[pos[6]]);
        // Add all neighbors to this Datapoint
        for (int z = 0 ; z < 13 ; z++) {
            datapoint.Set.push_back(aminos[pos[z]]);
        }
        // Add this Datapoint to Array
        AR.array.push_back(datapoint);
        // Move position one position right
        for (int z = 0 ; z < 13 ; z++) {
            pos[z]++;
        }
    }

    return AR;
}






/**
 *  P R E D I C T O R - F I L E
 *
 *  Create a CSV FIle with all Datasets
 *  @Format      { x-6 , ... , x , ... , x+6 , structure(x) } x = reference AA
 *  @outputfile  filename for output
 *  @return      a file in *.csv - format
 *
 * */
void Predictor::createTableFile(const string& outputfile) {

    ofstream file;
    file.open (outputfile);
    file << "AS_x-6" << "\t" << "AS_x-5" << "\t" << "AS_x-4" << "\t" << "AS_x-3" << "\t" << "AS_x-2" << "\t" << "AS_x-1" << "\t" << "AS_x" << "\t";
    file << "AS_x+1" << "\t" << "AS_x+2" << "\t" << "AS_x+3" << "\t" << "AS_x+4" << "\t" << "AS_x+5" << "\t" << "AS_x+6" << "\t" << "SecondaryStructure";

    for(auto all_dataset : this->data_point_arrays) {
        for(auto datapoint : all_dataset.array) {
            // print all aminoacids
            file << "\n";
            for(auto amino : datapoint.Set) {
                file << amino.getName() << "\t";
              }
            // print structure of datapoint
            file << datapoint.Ref.getStructure();

        }
    }

    file.close();

}

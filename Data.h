//
// Created by manjaro on 06.05.22.
//

#ifndef PREDICTOR_DATA_H
#define PREDICTOR_DATA_H

#include <string>
#include <vector>

using namespace std;

/**
 * Amino contains id, name and structure of a Amino Acid and
 * name of the protein
 *
 */
class Amino {
public:
    Amino(int id, char structure, char name, string protein) {
        this->ID = id;
        this->name = name;
        this->structure = structure;
        this->protein = protein;
    }

    const int getID() const         {return this->ID;}
    char getStructure() const  {return this->structure;}
    char getName() const       {return this->name;}
    const basic_string<char> getProteinName() const       {return this->protein;}

private:
    int ID;
    char structure;
    char name;
    string protein;
};





/**
 * Datapoint contains all six neighbors of a Amino at
 * index i (12 neighbor-Aminos + Ref-Amino i)
 *
 * @Ref : Amino with index i
 * @Set : All Aminos with Ref-Aminos from i-6 to i+6 (Ref i is inclusive)
 *
 */
class DataPoint {
public:
    explicit DataPoint(Amino i) {
        this->Ref = i;
    }
    Amino Ref = Amino(0, '0', '0',"");
    vector<Amino> Set;
};






/**
 * DatapointArray contains
 * all Datapoints of a protein
 *
 * @array                  : Array of all AminoDatasets
 * @getProteinName         : return name of protein of this Array
 * @getCountAllAmino       : return count of all Aminos of the protein
 * @getCountInDataSetAmino : return count of all Dataset-Aminos
 */
class DataPointArray {
public:
    DataPointArray(int protein_amino_count) {
        this->protein_amino_count = protein_amino_count;
    }
    // returns name of protein
    string getProteinName() {return this->array[0].Ref.getProteinName();}
    // returns count of all Aminos from the Protein (for testing)
    int getCountAllAmino() const       {return this->protein_amino_count;}
    // returns count of all DataSets with correct count of neighbors (for testing)
    int getCountInDataSetAmino() const {return this->array.size();}

    // Dataset
    vector<DataPoint> array;

private:
    int protein_amino_count;
};


#endif //PREDICTOR_DATA_H

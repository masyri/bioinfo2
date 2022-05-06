//
// Created by manjaro on 06.05.22.
//

#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/molecule.h>
#include <BALL/KERNEL/atom.h>
#include <BALL/KERNEL/bond.h>
#include <BALL/KERNEL/PTE.h>
#include <BALL/STRUCTURE/secondaryStructureProcessor.h>
#include <BALL/STRUCTURE/fragmentDB.h>
#include <BALL/STRUCTURE/peptides.h>
#include <BALL/FORMAT/PDBFile.h>
#include <vector>
#include <string>
#include "Data.h"

using namespace std;
using namespace BALL;

class Predictor {
public:

    explicit Predictor(vector<string> filelist);

    static vector<vector<Amino>> getAminosFromMultipleProteins(System S);

    static DataPointArray createDatasetArrayFromProtein(vector<Amino> aminos);

    void createTableFile(const string& outputfile);

    // for testing
    int countdatasets() {
        int c = 0;
        for (auto arrays : data_point_arrays) {
            c += (int)arrays.array.size();
        }
        return c;
    };

    vector<DataPointArray> data_point_arrays;

};


#endif //PREDICTOR_H

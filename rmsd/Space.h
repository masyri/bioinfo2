//
// Created by manjaro on 02.06.22.
//

#ifndef RMSD_SPACE_H
#define RMSD_SPACE_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "../console/Color.h"
#include "matrix/Matrix.h"
#include "BALL/MATHS/vector3.h"

/**
 * SPACE
 *
 * Includes coordinates
 *
 *
 *
 *
 * */

using namespace std;
using namespace BALL;



class Pos {

public:
    Pos(const string& index, double x, double y, double z) {
        this->index = index;
        this->x = x;
        this->y = y;
        this->z = z;
    }

    string index = "unknown"; // to make the object recognizable
    double x = 0;   // Coordinate x
    double y = 0;   // Coordinate y
    double z = 0;   // Coordinate z

};




class Space {

public:


    Space() = default;

    void addPosition(const string& index, double x, double y, double z) {
        positions.emplace_back(index,x,y,z);
    }



    /*
     * returns the center of all coordinates in this Space
     * */
    Vector3 calcCenterCoordinate() {
        double x = 0;
        double y = 0;
        double z = 0;
        for (const Pos& p : this->positions) {
            x += p.x;
            y += p.y;
            z += p.z;
        }
        double mul = 1.0 / (double)this->positions.size();
        return {mul * x,mul * y,mul * z};

    }




    /*
     * Move the coordinate center at a new point
     * @param newCenter : New Coordinate Center
     * */
    void moveCenterCoordinate(Vector3 newCenter) {
        for (const Pos& p : this->positions) {
            p.x - newCenter.x;
            p.y - newCenter.y;
            p.z - newCenter.z;
        }
    }


    void matrixvector(Matrix<double> M) {

        for(Pos pos : this->positions) {

            double _x = M.getValue(0,0) * pos.x
                    + M.getValue(0,1) * pos.y
                    + M.getValue(0,2) * pos.z;
            double _y = M.getValue(1,0) * pos.x
                    + M.getValue(1,1) * pos.y
                    + M.getValue(1,2) * pos.z;
            double _z = M.getValue(2,0) * pos.x
                    + M.getValue(2,1) * pos.y
                    + M.getValue(2,2) * pos.z;

            pos.x = _x;
            pos.y = _y;
            pos.z = _z;

        }

    }


    /*
     * print all coordinates to console
     * */
    void print(){

        std::cout << C::BWHITE << "\n[Coordinate Space] Objects: " << this->positions.size() << "\n" << C::RESET ;
        for (const Pos& p : this->positions) {
            std::cout << C::BGREEN << " " << setw(4) << p.index << " , " << C::BBLUE << setw(7) << p.x << setw(7) << p.y << setw(7) << p.z << "\n";

        }


    }



vector<Pos> positions;

};


#endif //RMSD_SPACE_H

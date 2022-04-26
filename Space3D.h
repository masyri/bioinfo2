//
// Created by manjaro on 22.04.22.
//

#ifndef SPACE3D_H
#define SPACE3D_H

#include <vector>
#include <iostream>
#include "console/Color.h"
#include "Groups.h"


class Box3D {
public:
    Box3D() = default;
    std::vector<NH_Group*> NH_Groups; // position of the H-Atom
    std::vector<CO_Group*> CO_Groups; // position of the O-Atom
};


/*
 * Divides a 3D-space into boxes for faster search in a small coordinate neighborhood.
 *
 *
 * .___.___.___.
 * | x |   |   |
 * |___|___|___|
 * |   |   |   |
 * |___|x__|___|
 * |   |   | x |
 * |___|___|___|
 *
 *
 * */
class Space3D {
public:
    Space3D(double x, double y, double z, double boxsize) {
        this->size_x = x;
        this->size_y = y;
        this->size_z = z;
        this->boxsize = boxsize;
        this->count_x = x / boxsize + 1.0;
        this->count_y = y / boxsize + 1.0;
        this->count_z = z / boxsize + 1.0;

        for (int Z = 0; Z < count_z ; Z++) {
            std::vector<std::vector<Box3D>> y_axis;
            for (int Y = 0; Y < count_y ; Y++) {
                std::vector<Box3D> x_axis;
                for (int X = 0; X < count_x; X++) {
                    Box3D box;
                    x_axis.push_back(box);
                }
                y_axis.push_back(x_axis);
            }
            Space.push_back(y_axis);
        }
    }

    std::vector<NH_Group*> search(double x, double y, double z);

    void pushToSpace(double x, double y, double z,NH_Group &NH);
    void pushToSpace(double x, double y, double z,CO_Group &CO);

    void print(){
        int item_count = 0; int box_count = Space[0][0].size() * Space[0].size() * Space.size();

        std::cout  << C::BBLUE << "\n [Space3D]" << " Boxsize: " << boxsize << " Boxcount: " << box_count << " Itemcount: " << item_count << C::BLUE
                               << "\n x " << size_x << " boxes: " << Space[0][0].size()
                               << "\n y " << size_y << " boxes: " << Space[0].size()
                               << "\n z " << size_z << " boxes: " << Space.size() << C::RESET << "\n";}

private:
    double size_x;
    double size_y;
    double size_z;
    double boxsize;
    int count_x;
    int count_y;
    int count_z;
    std::vector<std::vector<std::vector<Box3D>>> Space;


};





#endif //SPACE3D_H

//
// Created by manjaro on 22.04.22.
//

#ifndef SPACE3D_H
#define SPACE3D_H

#include <vector>
#include <iostream>
#include "console/Color.h"
#include "Groups.h"






/*
 * Single 3D-Box with nice contents.
 *
 *  
 * */
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



/*
 * Create a Space3D Coordinate space
 *
 * @x,y,z     the size of the complete space
 * @boxsize   the size of a single box
 *
 * */
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



/*
 * Create a Space3D Coordinate space
 *
 * @S         the molecule-systen with their coordinates
 * @boxsize   the size of a single box
 *
 * */
    Space3D(System S, double boxsize) {

        double max_x = 0;    double max_y = 0;    double max_z = 0;
        double min_x = 0;    double min_y = 0;    double min_z = 0;

        // Search for the biggest and smallest 
        // x y z coordinate in this molecule
        //
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

        // 
        this->neg_x = abs(min_x - 3);
        this->neg_y = abs(min_y - 3);
        this->neg_z = abs(min_z - 3);

        this->size_x = neg_x + (max_x + 10);
        this->size_y = neg_y + (max_y + 10);
        this->size_z = neg_z + (max_z + 10);

        //

        this->boxsize = boxsize;

        this->count_x = size_x / boxsize + 1.0;
        this->count_y = size_y / boxsize + 1.0;
        this->count_z = size_z / boxsize + 1.0;

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



/*
 * print for testing
 *
 * */
    void print(){
        int item_count = 0;
        for (int Z = 0; Z < count_z ; Z++) {
            for (int Y = 0; Y < count_y ; Y++) {
                for (int X = 0; X < count_x; X++) {
                    item_count += Space[Z][Y][X].CO_Groups.size();
                    item_count += Space[Z][Y][X].NH_Groups.size();
                }
            }
        }
        int box_count = Space[0][0].size() * Space[0].size() * Space.size();

        std::cout  << C::BBLUE << "\n [Space3D]" << " Boxsize: " << boxsize << " Boxcount: " << box_count << " Itemcount: " << item_count << C::BLUE
                               << "\n x " << size_x << " boxes: " << Space[0][0].size()
                               << "\n y " << size_y << " boxes: " << Space[0].size()
                               << "\n z " << size_z << " boxes: " << Space.size() << C::RESET << "\n";
    }




    std::vector<NH_Group*> search(double x, double y, double z);

    void pushToSpace(double x, double y, double z,NH_Group &NH);
    void pushToSpace(double x, double y, double z,CO_Group &CO);





private:

    double size_x;
    double size_y;
    double size_z;

    double neg_x = 0;
    double neg_y = 0;
    double neg_z = 0;

    double boxsize;

    int count_x;
    int count_y;
    int count_z;

    std::vector<std::vector<std::vector<Box3D>>> Space;


};



#endif //SPACE3D_H

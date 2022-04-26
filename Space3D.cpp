//
// Created by manjaro on 22.04.22.
//

#include <set>
#include "Space3D.h"

/*
 * search over all neighbor boxes at a given point (x,y,z)
 *
 * (search over 8 - 27 boxes)
 *
 * */
std::vector<NH_Group*> Space3D::search(double x, double y, double z) {
    
    int _x = (int)(x / boxsize);
    int _y = (int)(y / boxsize);
    int _z = (int)(z / boxsize);
    std::set<int> neighbors_x = { abs(_x - 1) , _x , _x < Space[0][0].size() - 1 ? _x + 1 : _x};
    std::set<int> neighbors_y = { abs(_y - 1) , _y , _y < Space[0].size() - 1 ? _y + 1 : _y};
    std::set<int> neighbors_z = { abs(_z - 1) , _z , _z < Space.size() - 1 ? _z + 1 : _z};
    
    //std::cout << "\n search at " << x << " " << y << " " << z;
    
    std::vector<NH_Group*> res;

    for(int _x_ : neighbors_x) {
        for(int _y_ : neighbors_y) {
            for(int _z_ : neighbors_z) {
                
                //std::cout << "\n (x,y,z) " << _x_ << " " << _y_ << " " << _z_;

                for(NH_Group *NH : this->Space[_z_][_y_][_x_].NH_Groups) {
                    
                    res.push_back(NH);
                    
                }
            }
        }
    }


    return res;
}





/*
 * Insert a NH-Group to this Coordinate-Space
 *
 * @x,y,z   the position of the H-Atom of the referenced NH-Group
 * @CO      the reference of the NH_Group
 *
 * */
void Space3D::pushToSpace(double x, double y, double z,NH_Group &NH) {
    
    int _x = (int)(x / boxsize);
    int _y = (int)(y / boxsize);
    int _z = (int)(z / boxsize);
    this->Space[_z][_y][_x].NH_Groups.push_back(&NH);
}

/*
 * Insert a CO-Group to this Coordinate-Space
 *
 * @x,y,z   the position of the O-Atom of the referenced CO-Group
 * @CO      the reference of the CO_Group
 *
 * */
void Space3D::pushToSpace(double x, double y, double z,CO_Group &CO) {
    
    int _x = (int)(x / boxsize);
    int _y = (int)(y / boxsize);
    int _z = (int)(z / boxsize);
    this->Space[_z][_y][_x].CO_Groups.push_back(&CO);
}

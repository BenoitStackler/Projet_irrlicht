#ifndef DEF_MUR
#define DEF_MUR

#include <irrlicht.h>
#include <vector>
#include <string>
#include "Obstacle.hpp"

class Mur : public Obstacle
{

    public:
        Mur();
        Mur(irr::core::vector2d<int> pos, irr::f32 size);
        Mur(irr::core::vector2d<int> pos, irr::f32 size, irr::core::vector3df rot);

        Mur(int pos_x,int pos_y);
        Mur(int pos_x, int pos_y, int nx_param, int ny_param); 

        std::string type();

};

#endif
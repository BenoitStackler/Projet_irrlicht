#ifndef DEF_CAISSE
#define DEF_CAISSE

#include <vector>
#include <string>
#include "Obstacle.hpp"
#include <irrlicht.h>

class Caisse : public Obstacle

{

    public:
        Caisse();
        Caisse(std::string t);
        Caisse(irr::core::vector2d<int> pos, irr::f32 size);
        Caisse(irr::core::vector2d<int> pos, irr::f32 size, irr::core::vector3df rot);

        Caisse(int pos_x,int pos_y);
        Caisse(int pos_x, int pos_y, int nx_param, int ny_param); 
};

#endif

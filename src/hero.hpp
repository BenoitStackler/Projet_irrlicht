/* hero.hpp */
#ifndef HERO_HPP
#define HERO_HPP

#include <irrlicht.h>
#include "character.hpp"
#include <vector>
#include "vec2.hpp"
#include "Path.hpp"


class Hero : public Character
{
    public:

    Hero();
    Hero(const irr::io::path&  filename, const irr::io::path&  textname, irr::core::vector3di position, irr::core::vector3df direction, float life, float baseDamage);
    Hero(const irr::io::path&  filename, const irr::io::path&  textname);

    void compute_movements(int x_dest, int y_dest);
    void move();

    void compute_mvt_to_grid(irr::core::vector3df pos, Node_Graph closest_start);
    void compute_mvt_grid(Node_Graph closest_start, Node_Graph closest_dest);
    void compute_mvt_from_grid(irr::core::vector3df pos, Node_Graph closest_dest);

    void compute_mvt(irr::core::vector3df start, irr::core::vector3df dest);

    private:
    std::vector<irr::core::vector3df> movement_positions;
};

#endif
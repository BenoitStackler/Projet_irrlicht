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

    Hero(const irr::io::path&  filename, const irr::io::path&  textname, irr::core::vector3df position, irr::core::vector3df direction, float life, float baseDamage);
    Hero(const irr::io::path&  filename, const irr::io::path&  textname);

    void compute_movements(Path path);
    void move();

    private:
    std::vector<irr::core::vector3df> movement_positions;
};

#endif
/* hero.hpp */
#ifndef HERO_HPP
#define HERO_HPP

#include <irrlicht.h>
#include "character.hpp"


class Hero : public Character
{
    public:

    Hero(const irr::io::path&  filename, const irr::io::path&  textname, irr::core::vector3df position, irr::core::vector3df direction, float life, float baseDamage);
    Hero(const irr::io::path&  filename, const irr::io::path&  textname);
};

#endif
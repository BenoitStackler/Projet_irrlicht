/* hero.cpp */

#include "hero.hpp"
#include "character.hpp"
#include "projectile.hpp"

Hero::Hero(const irr::io::path&  filename, const irr::io::path&  textname, irr::core::vector3df position, irr::core::vector3df direction, float life, float baseDamage) :
        Character(filename, textname, position, direction, life, baseDamage)
{}

Hero::Hero(const irr::io::path&  filename, const irr::io::path&  textname) :
        Hero(filename, textname, irr::core::vector3df(0.0f), irr::core::vector3df(0.0f), 100.0f, 20.0f)
{}

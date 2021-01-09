/* enemy.hpp */
#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <irrlicht.h>
#include "character.hpp"
#include <vector>
#include "Hero.hpp"

class Enemy : public Character
{
    public:

    Enemy(const irr::io::path&  filename, const irr::io::path&  textname, irr::core::vector3df position, irr::core::vector3df direction, float life, float baseDamage);
    Enemy(const irr::io::path&  filename, const irr::io::path&  textname);
};

std::vector<Enemy> create_enemy(int number, Hero hero);

#endif
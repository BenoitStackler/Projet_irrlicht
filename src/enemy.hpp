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
    Enemy(const irr::io::path &filename, const irr::io::path &textname, irr::core::vector3di position, irr::core::vector3df direction, float life, float baseDamage);
    Enemy(const irr::io::path &filename, const irr::io::path &textname);
    Enemy();

    Projectile shoot();
};

std::vector<Enemy> create_enemy(Hero hero);

#endif
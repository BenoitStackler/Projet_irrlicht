/* enemy.cpp */

#include "enemy.hpp"
#include "character.hpp"
#include "projectile.hpp"

Enemy::Enemy(const irr::io::path&  filename, const irr::io::path&  textname, irr::core::vector3df position, irr::core::vector3df direction, float life, float baseDamage) :
        Character(filename, textname, position, direction, life, baseDamage)
{}

Enemy::Enemy(const irr::io::path&  filename, const irr::io::path&  textname) :
        Enemy(filename, textname, irr::core::vector3df(0.0f), irr::core::vector3df(0.0f), 20.0f, 20.0f)
{}

std::vector<Enemy> create_enemy(int number, Hero hero)
{
        std::vector<Enemy> enemies;
        irr::core::vector3df hero_pos = hero.position();
        enemies.push_back(Enemy("./irrlicht-1.8.4/media/faerie.md2","./irrlicht-1.8.4/media/Faerie5.BMP",irr::core::vector3df(180,0,140),irr::core::vector3df(0, 90, 0),20.0f,20.0f));
        enemies.push_back(Enemy("./irrlicht-1.8.4/media/faerie.md2","./irrlicht-1.8.4/media/faerie2.bmp",irr::core::vector3df(150,0,140),irr::core::vector3df(0, -45, 0),20.0f,20.0f));
        enemies.push_back(Enemy("./irrlicht-1.8.4/media/faerie.md2","./irrlicht-1.8.4/media/faerie2.bmp",irr::core::vector3df(180,0,120),irr::core::vector3df(0, 20, 0),20.0f,20.0f));
        enemies.push_back(Enemy("./irrlicht-1.8.4/media/faerie.md2","./irrlicht-1.8.4/media/faerie2.bmp",irr::core::vector3df(160,0,130),irr::core::vector3df(0, 35, 0),20.0f,20.0f));
        return enemies;
}
/* enemy.cpp */

#include "enemy.hpp"
#include "character.hpp"
#include "projectile.hpp"
#include "world.hpp"

extern World world;

Enemy::Enemy(const irr::io::path &filename, const irr::io::path &textname, irr::core::vector3di position, irr::core::vector3df direction, float life, float baseDamage) : Character(filename, textname, position, direction, life, baseDamage)
{
}

Enemy::Enemy(const irr::io::path &filename, const irr::io::path &textname) : Enemy(filename, textname, irr::core::vector3di(0), irr::core::vector3df(0.0f), 20.0f, 20.0f)
{
}
Enemy::Enemy()
{
}

std::vector<Enemy> create_enemy(Hero hero)
{
        std::vector<Enemy> enemies;
        irr::core::vector3df hero_pos = hero.position();
        Enemy enemy = Enemy("./irrlicht-1.8.4/media/faerie.md2", "./irrlicht-1.8.4/media/Faerie5.BMP", irr::core::vector3di(50, 0, 50), hero_pos - irr::core::vector3df(100, 0, 100), 20.0f, 10.0f);
        enemies.push_back(enemy);
        world.addEnemy(&enemy);
        enemy = Enemy("./irrlicht-1.8.4/media/faerie.md2", "./irrlicht-1.8.4/media/faerie2.bmp", irr::core::vector3di(10, 0, 10), hero_pos - irr::core::vector3df(-100, 0, -100), 20.0f, 10.0f);
        enemies.push_back(enemy);
        world.addEnemy(&enemy);
        enemy = Enemy("./irrlicht-1.8.4/media/faerie.md2", "./irrlicht-1.8.4/media/faerie2.bmp", irr::core::vector3di(10, 0, 25), hero_pos - irr::core::vector3df(180, 0, 120), 20.0f, 10.0f);
        enemies.push_back(enemy);
        world.addEnemy(&enemy);
        enemy = Enemy("./irrlicht-1.8.4/media/faerie.md2", "./irrlicht-1.8.4/media/faerie2.bmp", irr::core::vector3di(25, 0, 10), hero_pos - irr::core::vector3df(160, 0, 130), 20.0f, 10.0f);
        enemies.push_back(enemy);
        world.addEnemy(&enemy);
        return enemies;
}
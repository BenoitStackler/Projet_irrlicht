/* enemy.cpp */

#include "enemy.hpp"
#include "character.hpp"
#include "projectile.hpp"
#include "world.hpp"

extern World world;
extern Hero hero;

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
        Enemy* enemy1 = new Enemy("./irrlicht-1.8.4/media/faerie.md2", "./irrlicht-1.8.4/media/Faerie5.BMP", irr::core::vector3di(50, 0, 5), hero_pos - irr::core::vector3df(100, 0, 100), 40.0f, 10.0f);
        enemies.push_back(*enemy1);
        world.addEnemy(enemy1);

        Enemy* enemy2 = new Enemy("./irrlicht-1.8.4/media/faerie.md2", "./irrlicht-1.8.4/media/faerie2.bmp", irr::core::vector3di(10, 0, 75), hero_pos - irr::core::vector3df(-100, 0, -100), 20.0f, 10.0f);
        enemies.push_back(*enemy2);
        world.addEnemy(enemy2);

        Enemy* enemy3 = new Enemy("./irrlicht-1.8.4/media/faerie.md2", "./irrlicht-1.8.4/media/faerie2.bmp", irr::core::vector3di(10, 0, 25), hero_pos - irr::core::vector3df(180, 0, 120), 20.0f, 10.0f);
        enemies.push_back(*enemy3);
        world.addEnemy(enemy3);

        Enemy* enemy4 = new Enemy("./irrlicht-1.8.4/media/faerie.md2", "./irrlicht-1.8.4/media/faerie2.bmp", irr::core::vector3di(25, 0, 10), hero_pos - irr::core::vector3df(160, 0, 130), 20.0f, 10.0f);
        enemies.push_back(*enemy4);
        world.addEnemy(enemy4);

        Enemy* enemy5 = new Enemy("./irrlicht-1.8.4/media/faerie.md2", "./irrlicht-1.8.4/media/Faerie5.BMP", irr::core::vector3di(85, 0, 85), hero_pos - irr::core::vector3df(100, 0, 100), 40.0f, 10.0f);
        enemies.push_back(*enemy5);
        world.addEnemy(enemy5);

        Enemy* enemy6 = new Enemy("./irrlicht-1.8.4/media/faerie.md2", "./irrlicht-1.8.4/media/faerie2.bmp", irr::core::vector3di(85, 0, 10), hero_pos - irr::core::vector3df(-100, 0, -100), 20.0f, 10.0f);
        enemies.push_back(*enemy6);
        world.addEnemy(enemy6);

        Enemy* enemy7 = new Enemy("./irrlicht-1.8.4/media/faerie.md2", "./irrlicht-1.8.4/media/faerie2.bmp", irr::core::vector3di(80, 0, 28), hero_pos - irr::core::vector3df(180, 0, 120), 20.0f, 10.0f);
        enemies.push_back(*enemy7);
        world.addEnemy(enemy7);

        Enemy* enemy8 = new Enemy("./irrlicht-1.8.4/media/faerie.md2", "./irrlicht-1.8.4/media/faerie2.bmp", irr::core::vector3di(55, 0, 70), hero_pos - irr::core::vector3df(160, 0, 130), 20.0f, 10.0f);
        enemies.push_back(*enemy8);
        world.addEnemy(enemy8);
        return enemies;
}

Projectile Enemy::shoot()
{
        direction(hero.position() - position());
        return Projectile(this, 1.0f, baseDamage());
}
#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include "projectile.hpp"
#include "Obstacle.hpp"
#include "hero.hpp"
#include "enemy.hpp"

class World
{
public:
    World();
    World(Hero hero, std::vector<Obstacle> obstacles, std::vector<Enemy> enemies);

    void defHero(Hero hero);
    void addObstacle(Obstacle obstacle);
    void addEnemy(Enemy enemy);
    void addProjectile(Projectile projectile);

    Hero getHero();
    std::vector<Obstacle> getObstacles();
    std::vector<Enemy> getEnemies();
    std::vector<Projectile> getProjectiles();

private:
    Hero m_hero;
    std::vector<Obstacle> m_obstacles;
    std::vector<Enemy> m_enemies;
    std::vector<Projectile> m_projectiles;
};

#endif
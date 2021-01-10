#include "world.hpp"

World::World()
{
}

World::World(Hero hero, std::vector<Obstacle> obstacles, std::vector<Enemy> enemies) : m_hero(hero), m_obstacles(obstacles), m_enemies(enemies)
{
}

void World::defHero(Hero hero)
{
    m_hero = hero;
}
void World::addObstacle(Obstacle obstacle)
{
    m_obstacles.push_back(obstacle);
}

void World::addEnemy(Enemy enemy)
{
    m_enemies.push_back(enemy);
}
void World::addProjectile(Projectile projectile)
{
    m_projectiles.push_back(projectile);
}

Hero World::getHero()
{
    return m_hero;
}
std::vector<Obstacle> World::getObstacles()
{
    return m_obstacles;
}
std::vector<Enemy> World::getEnemies()
{
    return m_enemies;
}
std::vector<Projectile> World::getProjectiles()
{
    return m_projectiles;
}
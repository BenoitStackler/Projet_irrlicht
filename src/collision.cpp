#include "collision.hpp"
#include <iostream>

extern irr::scene::ISceneCollisionManager *collMan;
extern irr::scene::ISceneManager *smgr;

void collisionProj(std::vector<Projectile *> vect_proj)
{
    std::cout << "collision" << std::endl;
    collMan = smgr->getSceneCollisionManager();
    for (auto p : vect_proj)
    {
        irr::core::line3d<irr::f32> ray;
        ray.start = p->position();
        ray.end = ray.start + (p->direction() - ray.start).normalize() * 1000.0f;
        irr::core::vector3df intersection;
        irr::core::triangle3df hitTriangle;
        irr::scene::ISceneNode *selectedNode = collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle);
        if (selectedNode)
        {
        }
    }
}
/* projectile.cpp */

#include "projectile.hpp"
#include "character.hpp"
#include <iostream>
#include <vector>

extern irr::video::IVideoDriver *driver;
extern irr::scene::ISceneManager *smgr;
extern std::vector<irr::scene::ITriangleSelector *> selector;

Projectile::Projectile(Character *caster, float speed, float damage) : m_position(caster->position()), m_direction(caster->direction()), m_speed(speed), m_damage(damage)
{
    m_node = smgr->addSphereSceneNode(2.0f);
    if (m_node)
    {
        position(m_position + irr::core::vector3df(0.0f, 10, 0.0f));
        m_node->setMaterialTexture(0, driver->getTexture("./irrlicht-1.8.4/media/1.jpg"));
        m_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        for (auto s : selector)
        {
            irr::scene::ISceneNodeAnimator *anim = smgr->createCollisionResponseAnimator(s, m_node, irr::core::vector3df(5, 5, 5), irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0));
            m_node->addAnimator(anim);
            anim->drop();
        }
    }
}

Projectile::Projectile(Character *caster)
{
    Projectile(caster, 1.0f, 10.0f);
}

Projectile::Projectile()
{
}

void Projectile::impact()
{
}

void Projectile::move()
{
    position(position() + direction());
}

void Projectile::position(irr::core::vector3df position)
{
    m_node->setPosition(position);
    m_position = position;
}

void Projectile::direction(irr::core::vector3df direction)
{
    m_direction = direction;
}

irr::core::vector3df Projectile::position()
{
    return m_position;
}

irr::core::vector3df Projectile::direction()
{
    return m_direction;
}
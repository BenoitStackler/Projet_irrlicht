/* projectile.cpp */

#include "projectile.hpp"
#include "character.hpp"
#include <iostream>

extern irr::video::IVideoDriver* driver;
extern irr::scene::ISceneManager* smgr;

Projectile::Projectile(Character *caster, float speed, float damage) :
                       m_position(caster->position()), m_direction(caster->direction()), m_speed(speed), m_damage(damage)
{
    m_node = smgr->addSphereSceneNode(1.0f);
    if (m_node)
    {
        position(m_position + irr::core::vector3df(0.0f,10,0.0f));
        m_node->setMaterialTexture(0, driver->getTexture("./irrlicht-1.8.4/media/wall.bmp"));
        m_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    }
}

Projectile::Projectile(Character *caster)
{
    Projectile(caster, 1.0f, 10.0f);
}

void Projectile::impact()
{

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
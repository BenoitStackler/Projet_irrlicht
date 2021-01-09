/* character.cpp */

#include "character.hpp"
#include "projectile.hpp"
#include <iostream>

extern irr::video::IVideoDriver* driver;
extern irr::scene::ISceneManager* smgr;
extern irr::IrrlichtDevice* device;

Character::Character(const irr::io::path&  filename, const irr::io::path&  textname, irr::core::vector3df pos, irr::core::vector3df direct, float life, float baseDamage) :
            m_direction(direct) , m_life(life), m_baseDamage(baseDamage)
{
    m_mesh = smgr->getMesh(filename);
    if (!m_mesh)
    {
        device->drop();
    }
    m_direction = irr::core::vector3df(direct);
    m_node = smgr->addAnimatedMeshSceneNode(m_mesh);
    direction(direct);
    position(pos);
    m_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    m_node->setMD2Animation(irr::scene::EMAT_STAND);
    m_node->setMaterialTexture(0, driver->getTexture(textname));
}

Character::Character(const irr::io::path&  filename, const irr::io::path&  textname)
{
    Character(filename, textname, irr::core::vector3df(0.0f), irr::core::vector3df(0.0f), 100.0f, 20.0f);
}

void Character::impact()
{

}

void Character::move()
{

}

Projectile Character::shoot()
{
    return Projectile(this, 1.0f, m_baseDamage);
}

irr::core::vector3df const Character::position() const
{
    return m_position;
}

irr::core::vector3df const Character::direction() const
{
    return m_direction;
}

void Character::position(irr::core::vector3df position)
{
    m_position = position;
    m_node->setPosition(position);
}

void Character::direction(irr::core::vector3df direction)
{
    float angle = direction.dotProduct(m_direction);
    m_direction = direction;
    m_node->setRotation(direction);
}
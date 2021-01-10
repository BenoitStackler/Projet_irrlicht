/* character.cpp */

#include "character.hpp"
#include "projectile.hpp"
#include <iostream>
#include <cmath>
#include "utils.hpp"

extern irr::video::IVideoDriver *driver;
extern irr::scene::ISceneManager *smgr;
extern irr::IrrlichtDevice *device;

Character::Character() {}

Character::Character(const irr::io::path &filename, const irr::io::path &textname, irr::core::vector3di pos, irr::core::vector3df direct, float life, float baseDamage) : m_direction(direct), m_life(life), m_baseDamage(baseDamage)
{
    m_mesh = smgr->getMesh(filename);
    if (!m_mesh)
    {
        device->drop();
    }
    m_direction = irr::core::vector3df(direct);
    m_node = smgr->addAnimatedMeshSceneNode(m_mesh);
    direction(direct);
    position(grid_to_pix(pos) + irr::core::vector3df(0.0f, 25.0f, 0.0f));
    m_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    m_node->setMD2Animation(irr::scene::EMAT_STAND);
    m_node->setMaterialTexture(0, driver->getTexture(textname));
    m_node->setID(IDFlag_IsPickable);
}

Character::Character(const irr::io::path &filename, const irr::io::path &textname)
{
    Character(filename, textname, irr::core::vector3di(0), irr::core::vector3df(0.0f), 100.0f, 20.0f);
}

float const Character::life() const
{
    return m_life;
}
float const Character::baseDamage() const
{
    return m_baseDamage;
}

int Character::impact()
{
    m_life -= 10.0f;
    if (m_life <= 0.0f)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
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

irr::scene::IAnimatedMeshSceneNode * Character::node()
{
    return m_node;
}

void Character::position(irr::core::vector3df position)
{
    m_position = position;
    m_node->setPosition(position);
}

void Character::direction(irr::core::vector3df dir)
{
    dir.normalize();
    m_direction = dir;
    irr::core::vector3df cross = dir.crossProduct(irr::core::vector3df(0.0f, 0.0f, 1.0f));
    float cos_angle = dir.dotProduct(irr::core::vector3df(0.0f, 0.0f, 1.0f));
    float angle;

    if (cross.Y < 0)
    {
        angle = 3*M_PI/2 + acos(cos_angle);
    }
    else
    {
        angle = 3*M_PI/2 - acos(cos_angle);
    }
    m_node->setRotation(irr::core::vector3df(0.0f, angle * 180 / M_PI, 0.0f));
}

void Character::lookat(irr::core::vector3df target)
{
    direction(target -  position());
    
}
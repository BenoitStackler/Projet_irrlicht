#include "Obstacle.hpp"
#include <irrlicht.h>
#include <iostream>

extern irr::video::IVideoDriver *driver;
extern irr::scene::ISceneManager *smgr;
extern float dim_pix_x;
extern float dim_pix_y;

Obstacle::Obstacle() {}

Obstacle::Obstacle(irr::core::vector2d<int> pos)
    : m_position(pos)
{
    m_node = smgr->addCubeSceneNode();
    if (m_node)
    {
        position(m_position);
        m_node->setMaterialTexture(0, driver->getTexture("./irrlicht-1.8.4/media/wall.bmp"));
        m_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    }
}

Obstacle::Obstacle(irr::core::vector2d<int> pos, irr::f32 size)
    : m_position(pos), m_size(size)
{
    m_node = smgr->addCubeSceneNode(size);
    if (m_node)
    {
        position(m_position);
        m_node->setMaterialTexture(0, driver->getTexture("./irrlicht-1.8.4/media/wall.bmp"));
        m_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    }
}

Obstacle::Obstacle(irr::core::vector2d<int> pos, irr::f32 size, irr::core::vector3df rot)
    : m_position(pos), m_size(size), m_rotation(rot)
{
    m_node = smgr->addCubeSceneNode(size);
    if (m_node)
    {
        position(m_position);
        rotation(m_rotation);
        m_node->setMaterialTexture(0, driver->getTexture("./irrlicht-1.8.4/media/wall.bmp"));
        m_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    }
}
//Getters

//Position de l'obstacle
irr::core::vector2d<int> const Obstacle::position() const
{
    return m_position;
}
//Setters
//Position de l'obstacle

void Obstacle::position(irr::core::vector2d<int> position)
{
    m_position = position;
    irr::core::vector3df pos = irr::core::vector3df(position.X * dim_pix_x, 10.0f, position.Y * dim_pix_y);
    std::cout << position.X * dim_pix_x << "  " << position.Y * dim_pix_x << "  " << std::endl;
    m_node->setPosition(pos);
}

void Obstacle::rotation(irr::core::vector3df rotation)
{
    m_node->setRotation(rotation);
}

std::string Obstacle::type()
{
    return "Obstacle";
}

void Obstacle::scale(irr::core::vector3df scale)
{
    m_node->setScale(scale);
}

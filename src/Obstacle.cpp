#include "Obstacle.hpp"
#include <irrlicht.h>

extern irr::video::IVideoDriver *driver;
extern irr::scene::ISceneManager *smgr;
extern float dim_pix_x;
extern float dim_pix_y;

Obstacle::Obstacle() {}

Obstacle::Obstacle(irr::core::vector2d<int> pos)
    : m_position(pos), m_x(pos.X), m_y(pos.Y)
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
    : m_position(pos), m_size(size), m_x(pos.X), m_y(pos.Y)
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
    : m_position(pos), m_size(size), m_rotation(rot), m_x(pos.X), m_y(pos.Y)
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

Obstacle::Obstacle(int pos_x, int pos_y) //Position de l'obstacle définie et dimensions par défaut (1,1)
{
    irr::core::vector2d<int> pos(pos_x, pos_y);
    m_x = pos_x;
    m_y = pos_y;
    m_position = pos;
    m_node = smgr->addCubeSceneNode();
    if (m_node)
    {
        position(m_position);
        m_node->setMaterialTexture(0, driver->getTexture("./irrlicht-1.8.4/media/wall.bmp"));
        m_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    }
}

Obstacle::Obstacle(int pos_x, int pos_y, int nx_param, int ny_param) //Position et dimensions définies
{
    irr::core::vector2d<int> pos(pos_x, pos_y);
    m_x = pos_x;
    m_y = pos_y;
    m_position = pos;
    m_node = smgr->addCubeSceneNode();
    if (m_node)
    {
        position(m_position);
        m_node->setMaterialTexture(0, driver->getTexture("./irrlicht-1.8.4/media/wall.bmp"));
        m_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    }
    m_nx = nx_param;
    m_ny = ny_param;
}

//Getters
//Position de l'obstacle
irr::core::vector2d<int> const Obstacle::position() const
{
    return m_position;
}

const int Obstacle::x() const { return m_x; }; //Getter de position en x de l'obstacle
const int Obstacle::y() const { return m_y; }; //Getter de position en y de l'obstacle

//Dimensions de l'obstacle
const int Obstacle::nx() const { return m_nx; }; //Getter de dimension en x de l'obstacle
const int Obstacle::ny() const { return m_ny; }; //Getter de dimension en y de l'obstacle

const int Obstacle::id() const { return m_id; }; //Getter d'id de l'obstacle

irr::scene::IMeshSceneNode *const Obstacle::node()
{
    return m_node;
}
//Setters
//Position de l'obstacle
void Obstacle::position(irr::core::vector2d<int> position)
{
    m_position = position;
    irr::core::vector3df pos = irr::core::vector3df(position.X * dim_pix_x, 0.0f, position.Y * dim_pix_y);
    m_node->setPosition(pos);
}

void Obstacle::rotation(irr::core::vector3df rotation)
{
    m_node->setRotation(rotation);
}

void Obstacle::x(int pos_x) { m_x = pos_x; };
void Obstacle::y(int pos_y) { m_y = pos_y; };

//Dimensions de l'obstacle
void Obstacle::nx(int len) { m_nx = len; };
void Obstacle::ny(int height) { m_ny = height; };

std::string Obstacle::type()
{
    return "Obstacle";
}

void Obstacle::scale(irr::core::vector3df scale)
{
    m_node->setScale(scale);
}
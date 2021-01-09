#include "Terrain.hpp"

extern irr::video::IVideoDriver *driver;
extern irr::scene::ISceneManager *smgr;
extern irr::IrrlichtDevice *device;

Terrain::Terrain() {}
Terrain::Terrain(const irr::io::path &filename, const irr::io::path &textname) : Terrain(filename, textname, irr::core::vector3df(0.0f))
{
}

Terrain::Terrain(const irr::io::path &filename, const irr::io::path &textname, irr::core::vector3df position) : Terrain(filename, textname, position, irr::core::vector3df(0.0f), irr::core::vector3df(0.0f))
{
}
Terrain::Terrain(const irr::io::path &filename, const irr::io::path &textname, irr::core::vector3df pos, irr::core::vector3df rot, irr::core::vector3df sc) : m_position(pos), m_rotation(rot), m_scale(sc)
{
    m_node = smgr->addTerrainSceneNode(filename);
    rotation(rot);
    position(pos);
    scale(sc);
    m_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    m_node->setMaterialTexture(0, driver->getTexture(textname));
}

void Terrain::position(irr::core::vector3df pos)
{
    m_position = pos;
    m_node->setPosition(pos);
}
void Terrain::rotation(irr::core::vector3df rot)
{
    m_rotation = rot;
    m_node->setRotation(rot);
}
void Terrain::scale(irr::core::vector3df sc)
{
    m_scale = sc;
    m_node->setScale(sc);
}

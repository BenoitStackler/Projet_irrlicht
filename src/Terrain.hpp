#ifndef DEF_TERRAIN
#define DEF_TERRAIN

#include <irrlicht.h>
#include <vector>


class Terrain
{

public:
    //Constructeurs
    Terrain();                                               
    Terrain(const irr::io::path&  filename, const irr::io::path&  textname);                          
    Terrain(const irr::io::path&  filename, const irr::io::path&  textname, irr::core::vector3df position);     
    Terrain(const irr::io::path&  filename, const irr::io::path&  textname, irr::core::vector3df position, irr::core::vector3df rotation, irr::core::vector3df scale);

    void position(irr::core::vector3df pos);
    void rotation(irr::core::vector3df rot);
    void scale(irr::core::vector3df sc);
private:

    //Attributs de position du point haut gauche du terrain
    irr::core::vector3df m_position;
    irr::core::vector3df m_rotation;
    irr::core::vector3df m_scale;

    irr::scene::ITerrainSceneNode*   m_node;

    //Attributs de dimentions du terrain
    int m_nx;     //Longueur du terrain (en nombre de case de grille)
    int m_ny;     //Largeur du terrain (en nombre de case de grille)


};
#endif
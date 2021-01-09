/* character.hpp */
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <irrlicht.h>
#include <string>
#include "projectile.hpp"

class Character
{
    public :
    Character(const irr::io::path&  filename, const irr::io::path&  textname, irr::core::vector3di position, irr::core::vector3df direct, float life, float baseDamage);
    Character(const irr::io::path&  filename, const irr::io::path&  textname);

    void impact();
    void move();
    Projectile shoot();
    irr::core::vector3df const position() const;
    irr::core::vector3df const direction() const;

    void position(irr::core::vector3df position);
    void direction(irr::core::vector3df direction);

    float const life() const;
    float const baseDamage() const;
    

    private :

    // Attributs
    float                               m_life;
    float                               m_baseDamage;
    irr::core::vector3df                m_position;
    irr::core::vector3df                m_direction;
    irr::scene::IAnimatedMesh*          m_mesh;
    irr::scene::IAnimatedMeshSceneNode* m_node;
};

#endif
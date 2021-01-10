/* projectile.hpp */
#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <irrlicht.h>
class Character;

class Projectile
{
public:
    Projectile(Character *caster, float speed, float damage);
    Projectile(Character *caster);
    Projectile();

    void impact();
    void move();
    void position(irr::core::vector3df position);
    void direction(irr::core::vector3df direction);

    irr::core::vector3df position();
    irr::core::vector3df direction();

private:
    // Attributs
    float m_speed;
    float m_damage;
    irr::core::vector3df m_position;
    irr::core::vector3df m_direction;
    irr::scene::ISceneNode *m_node;
};

#endif
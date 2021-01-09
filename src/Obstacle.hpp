#ifndef DEF_OBSTACLE
#define DEF_OBSTACLE

#include <irrlicht.h>
#include <vector>
#include <string>

class Obstacle
{
public:
    Obstacle();
    Obstacle(irr::core::vector2d<int> position);
    Obstacle(irr::core::vector2d<int> position, irr::f32 size);
    Obstacle(irr::core::vector2d<int> position, irr::f32 size, irr::core::vector3df rotation);

    //Getters
    //Position de l'obstacle
    irr::core::vector2d<int> const position() const;
    std::string type(); //Retourne une string donnant le type d'obstacle(mur ou caisse)

    void position(irr::core::vector2d<int> position);
    void rotation(irr::core::vector3df rotation);
    void scale(irr::core::vector3df scale);

private:
    irr::core::vector2d<int> m_position;
    irr::core::vector3df m_rotation;
    irr::f32 m_size;
    irr::scene::ISceneNode *m_node;
};

#endif
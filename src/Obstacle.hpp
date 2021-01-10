#ifndef DEF_OBSTACLE
#define DEF_OBSTACLE

#include <irrlicht.h>
#include <vector>
#include <string>

enum ID_Flag
{
    // I use this ISceneNode ID to indicate a scene node that is
    // not pickable by getSceneNodeAndCollisionPointFromRay()
    ID_IsNotPickable = 0,

    // I use this flag in ISceneNode IDs to indicate that the
    // scene node can be picked by ray selection.
    IDFlag_IsPickable = 1 << 0,

    // I use this flag in ISceneNode IDs to indicate that the
    // scene node can be highlighted.  In this example, the
    // homonids can be highlighted, but the level mesh can't.
    IDFlag_IsHighlightable = 1 << 1
};

class Obstacle
{
public:
    Obstacle();
    Obstacle(irr::core::vector2d<int> position);
    Obstacle(irr::core::vector2d<int> position, irr::f32 size);
    Obstacle(irr::core::vector2d<int> position, irr::f32 size, irr::core::vector3df rotation);

    Obstacle(int pos_x, int pos_y);                             //Position de l'obstacle définie et dimensions par défaut (1,1)
    Obstacle(int pos_x, int pos_y, int nx_param, int ny_param); //Position et dimensions définies

    //Getters
    //Position de l'obstacle
    int x() const; //Getter de position en x de l'obstacle
    int y() const; //Getter de position en y de l'obstacle

    //Dimensions de l'obstacle
    int nx() const; //Getter de dimension en x de l'obstacle
    int ny() const; //Getter de dimension en y de l'obstacle

    int id() const; //Getter d'id de l'obstacle

    irr::scene::IMeshSceneNode *const node();

    //Setters
    //Position de l'obstacle
    void x(int pos_x);
    void y(int pos_y);

    //Dimensions de l'obstacle
    void nx(int len);
    void ny(int height);

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
    irr::scene::IMeshSceneNode *m_node;

    //Attributs de position du point haut gauche de l'obstacle
    int m_x; //Position en x du point haut gauche de l'obstacle (en nombre de case de grille)
    int m_y; //Position en y du point haut gauche du de l'obstacle (en nombre de case de grille)

    //Attributs de dimentions de l'obstacle
    int m_nx; //Longueur de l'obstacle (en nombre de case de grille)
    int m_ny; //Largeur de l'obstacle (en nombre de case de grille)

    int m_height;

    int m_id; //Identifiant de l'obstacle
};
#endif
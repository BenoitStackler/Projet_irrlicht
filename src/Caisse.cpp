#include "Caisse.hpp"


Caisse::Caisse():
Obstacle()
{}

Caisse::Caisse(std::string t):
Obstacle(t)
{}

Caisse::Caisse(irr::core::vector2d<int> pos, irr::f32 size)  :
Obstacle(pos, size)
{setType("Caisse");
setTexture("./irrlicht-1.8.4/media/t351sml.jpg");}

Caisse::Caisse(irr::core::vector2d<int> pos, irr::f32 size, irr::core::vector3df rot):
Obstacle(pos, size, rot)
{setType("Caisse");
setTexture("./irrlicht-1.8.4/media/t351sml.jpg");}

Caisse::Caisse(int pos_x,int pos_y):
Obstacle(pos_x,pos_y)
{setType("Caisse");
setTexture("./irrlicht-1.8.4/media/t351sml.jpg");}

Caisse::Caisse(int pos_x, int pos_y, int nx_param, int ny_param):
Obstacle(pos_x, pos_y, nx_param, ny_param)
{setType("Caisse");
setTexture("./irrlicht-1.8.4/media/t351sml.jpg");}


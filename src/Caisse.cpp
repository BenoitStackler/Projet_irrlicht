#include "Caisse.hpp"


Caisse::Caisse():
Obstacle()
{}

Caisse::Caisse(irr::core::vector2d<int> pos, irr::f32 size)  :
Obstacle(pos, size)
{}
Caisse::Caisse(irr::core::vector2d<int> pos, irr::f32 size, irr::core::vector3df rot):
Obstacle(pos, size, rot)
{}

Caisse::Caisse(int pos_x,int pos_y):
Obstacle(pos_x,pos_y)
{}

Caisse::Caisse(int pos_x, int pos_y, int nx_param, int ny_param):
Obstacle(pos_x, pos_y, nx_param, ny_param)
{} 


std::string Caisse::type() { 
	return "Caisse";
}
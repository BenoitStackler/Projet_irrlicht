#include "Mur.hpp"


Mur::Mur() : Obstacle() {}

Mur::Mur(std::string t) : Obstacle(t) {}

Mur::Mur(irr::core::vector2d<int> pos, irr::f32 size)  
{
	Obstacle(pos, size);
	setType("Mur");
}

Mur::Mur(irr::core::vector2d<int> pos, irr::f32 size, irr::core::vector3df rot)
{
	Obstacle(pos, size, rot);
	setType("Mur");
}

Mur::Mur(int pos_x,int pos_y):
Obstacle(pos_x,pos_y)
{setType("Mur");}

Mur::Mur(int pos_x, int pos_y, int nx_param, int ny_param):
Obstacle(pos_x, pos_y, nx_param, ny_param)
{setType("Mur");} 

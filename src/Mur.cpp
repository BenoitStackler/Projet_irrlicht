#include "Mur.hpp"


//Mur::Mur() : Obstacle() {}

Mur::Mur(irr::core::vector2d<int> pos, irr::f32 size)  
{
	Obstacle(pos, size);
}

Mur::Mur(irr::core::vector2d<int> pos, irr::f32 size, irr::core::vector3df rot)
{
	Obstacle(pos, size, rot);
}

std::string Mur::type() {
	return "Mur";
}
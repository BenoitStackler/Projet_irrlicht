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



std::string Caisse::type() { 
	return "Caisse";
}
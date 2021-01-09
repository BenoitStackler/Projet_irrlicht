/* hero.cpp */

#include "hero.hpp"
#include "character.hpp"
#include "projectile.hpp"
#include "Path.hpp"

Hero::Hero(const irr::io::path&  filename, const irr::io::path&  textname, irr::core::vector3df position, irr::core::vector3df direction, float life, float baseDamage) :
        Character(filename, textname, position, direction, life, baseDamage)
{}

Hero::Hero(const irr::io::path&  filename, const irr::io::path&  textname) :
        Hero(filename, textname, irr::core::vector3df(0.0f), irr::core::vector3df(0.0f), 100.0f, 20.0f)
{}


void Hero::move()
{
        if (!movement_positions.empty())
        {
                position(movement_positions[0]);
                movement_positions.erase(movement_positions.begin());
        }
}

void Hero::compute_movements(Path path)
{
        std::vector<Node_Graph> nodes;
        for (int k = 1 ; k < nodes.size() ; k++)
        {
                Node_Graph node_first = nodes[k-1];
                Node_Graph node_last = nodes[k];

                float dx = 10*(node_last.x() - node_first.x());
                float dy = 10*(node_last.y() - node_first.y());

                float norm_dx_dy = sqrt(pow(dx,2) + pow(dy,2));
                dx /= norm_dx_dy;
                dy /= norm_dx_dy;

                for (int i = 0 ; i < norm_dx_dy ; i++)
                {
                        movement_positions.push_back(irr::core::vector3df(position().X + i*dx, position().Y, position().Z + i*dy));
                }
        }
}
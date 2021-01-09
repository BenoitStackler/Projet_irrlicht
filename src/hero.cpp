/* hero.cpp */

#include "hero.hpp"
#include "character.hpp"
#include "projectile.hpp"

#define offset 2
#define multiplicator 10.0f

extern Grid grid;
extern std::vector<Node_Graph> vec_nodes;

Hero::Hero(const irr::io::path&  filename, const irr::io::path&  textname, irr::core::vector3di position, irr::core::vector3df direction, float life, float baseDamage) :
        Character(filename, textname, position, direction, life, baseDamage)
{}

Hero::Hero(const irr::io::path&  filename, const irr::io::path&  textname) :
        Hero(filename, textname, irr::core::vector3di(0), irr::core::vector3df(0.0f), 100.0f, 20.0f)
{}

void Hero::move()
{
        if (!movement_positions.empty())
        {
                position(movement_positions[0]);
                movement_positions.erase(movement_positions.begin());
        }
}



void Hero::compute_movements(irr::core::vector2di dest)
{
        irr::core::vector3df pos_act = position();
        irr::core::vector3di pos_new;
        irr::core::vector2di pos_node_start;
        pos_new.X = int(round(pos_act.X/multiplicator - offset));
        pos_new.Y = 0;
        pos_new.Z = int(round(pos_act.Z/multiplicator - offset));

        pos_node_start.X = pos_new.X;
        pos_node_start.Y = pos_new.Z;
        Hero("./irrlicht-1.8.4/media/sydney.md2", "./irrlicht-1.8.4/media/sydney.bmp", pos_new, irr::core::vector3df(0, 0, 0), life(), baseDamage());


        std::vector<Node_Graph> nodes_path;
        for (Node_Graph node : vec_nodes)
        {
                nodes_path.push_back(node);
        }

        Node_Graph start(7, 4, -1);
        Node_Graph end(1, 9, -2);
        nodes_path.push_back(start);
        nodes_path.push_back(end);

        start.compute_neighbours(nodes_path, grid);
        end.compute_neighbours(nodes_path, grid);

        for (int k = 0 ; k < nodes_path.size() ; k++){
                nodes_path[k].compute_neighbours(nodes_path, grid);
        }

        Path path = find_path(nodes_path, start, end);

        std::vector<Node_Graph> nodes = path.path();
        movement_positions.clear();
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

        delete &start;
        delete &end;
}
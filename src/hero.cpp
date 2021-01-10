/* hero.cpp */

#include "hero.hpp"
#include "character.hpp"
#include "projectile.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include "Receiver.hpp"

#define offset 2
#define multiplicator 10.0f

extern Grid grid;
extern std::vector<Node_Graph> vec_nodes;
extern std::map<std::string, Path> map_paths;
extern irr::s32 x_souris;
extern irr::s32 y_souris;

Hero::Hero() {}

Hero::Hero(const irr::io::path &filename, const irr::io::path &textname, irr::core::vector3di position, irr::core::vector3df direction, float life, float baseDamage) : Character(filename, textname, position, direction, life, baseDamage)
{
}

Hero::Hero(const irr::io::path &filename, const irr::io::path &textname) : Hero(filename, textname, irr::core::vector3di(0), irr::core::vector3df(0.0f), 100.0f, 20.0f)
{
}

void Hero::move()
{
        if (!movement_positions.empty())
        {
                position(movement_positions[0]);
                movement_positions.erase(movement_positions.begin());
        }
}

Projectile Hero::shoot()
{
        irr::core::vector3df pos_souris = irr::core::vector3df(x_souris, 0.0f, y_souris);
        direction(pos_souris - position());
        return Projectile(this, 1.0f, baseDamage());
}


void Hero::compute_movements(float x_dest, float y_dest)
{
        movement_positions.clear();

        irr::core::vector3df current_pos = position();
        irr::core::vector2di pos_grid_start = pix_to_grid(current_pos);

        irr::core::vector2di pos_grid_dest = pix_to_grid(irr::core::vector3df(x_dest, current_pos.Y, y_dest));

        Node_Graph closest_start = find_closest_node(pos_grid_start.X, pos_grid_start.Y, pos_grid_dest.X, pos_grid_dest.Y, vec_nodes);
        Node_Graph closest_dest = find_closest_node(pos_grid_dest.X, pos_grid_dest.Y, pos_grid_start.X, pos_grid_start.Y, vec_nodes);

        Node_Graph start_node(pos_grid_start.X, pos_grid_start.Y, vec_nodes.back().number() +1);
        Node_Graph target_node(pos_grid_dest.X, pos_grid_dest.Y, vec_nodes.back().number() +2);

        std::vector<Node_Graph> Graph;
        for (auto node : vec_nodes)
        {
                Graph.push_back(node);
        }
        Graph.push_back(start_node);
        Graph.push_back(target_node);

        for (int k = 0; k < Graph.size() ; k++)
        {
                Graph[k].compute_neighbours(Graph, grid);
        }


        Path path = find_path(Graph, Graph[Graph.size() - 2], Graph[Graph.size() - 1]);


        for (int k = 1 ; k < path.path().size() ; k++)
        {
                compute_mvt_grid(path.path()[k-1], path.path()[k]);
        }
        

}

void Hero::compute_mvt_to_grid(irr::core::vector3df pos, Node_Graph closest_start)
{
        irr::core::vector2di coords_grid_node;
        coords_grid_node.X = closest_start.x();
        coords_grid_node.Y = closest_start.y();
        irr::core::vector3df coords_px_node = grid_to_pix(coords_grid_node);
        compute_mvt(pos, coords_px_node);
}


void Hero::compute_mvt_grid(Node_Graph closest_start, Node_Graph closest_dest)
{
        irr::core::vector2di coords_grid_node_start;
        coords_grid_node_start.X = closest_start.x();
        coords_grid_node_start.Y = closest_start.y();
        irr::core::vector3df coords_px_node_start = grid_to_pix(coords_grid_node_start);
        irr::core::vector2di coords_grid_node_dest;
        coords_grid_node_dest.X = closest_dest.x();
        coords_grid_node_dest.Y = closest_dest.y();
        irr::core::vector3df coords_px_node_dest = grid_to_pix(coords_grid_node_dest);
        compute_mvt(coords_px_node_start, coords_px_node_dest);
}


void Hero::compute_mvt_from_grid(irr::core::vector3df pos, Node_Graph closest_dest)
{
        irr::core::vector2di coords_grid_node;
        coords_grid_node.X = closest_dest.x();
        coords_grid_node.Y = closest_dest.y();
        irr::core::vector3df coords_px_node = grid_to_pix(coords_grid_node);
        compute_mvt(coords_px_node, pos);
}


void Hero::compute_mvt(irr::core::vector3df start, irr::core::vector3df dest)
{
        float dx =(dest.X - start.X);
        float dy =(dest.Z - start.Z);
        float norm_dx_dy = sqrt(pow(dx,2) + pow(dy,2));

        if (norm_dx_dy != 0.0f)
        {
                dx /= norm_dx_dy;
                dy /= norm_dx_dy;

                for (int i = 0 ; i < norm_dx_dy ; i++)
                {
                        movement_positions.push_back(irr::core::vector3df(start.X + i*dx, start.Y, start.Z + i*dy));
                }
                movement_positions.push_back(irr::core::vector3df(start.X + norm_dx_dy*dx, start.Y, start.Z + norm_dx_dy*dy));
        }
}



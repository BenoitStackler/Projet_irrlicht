/* hero.cpp */

#include "hero.hpp"
#include "character.hpp"
#include "projectile.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>

#define offset 2
#define multiplicator 10.0f

extern Grid grid;
extern std::vector<Node_Graph> vec_nodes;
extern std::map<std::string, Path> map_paths;

Hero::Hero(){}

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



void Hero::compute_movements(float x_dest, float y_dest)
{
        std::cout << "Start Compute Movement" << std::endl;
        movement_positions.clear();

        irr::core::vector3df current_pos = position();
        irr::core::vector2di pos_grid_start = pix_to_grid(current_pos);

        std::cout << "Grid start : " << pos_grid_start.X << ", " << pos_grid_start.Y << std::endl;
        irr::core::vector2di pos_grid_dest = pix_to_grid(irr::core::vector3df(x_dest, current_pos.Y, y_dest));
        std::cout << "Grid start : " << pos_grid_dest.X << ", " << pos_grid_dest.Y << std::endl;

        Node_Graph closest_start = find_closest_node(pos_grid_start.X, pos_grid_start.Y, pos_grid_dest.X, pos_grid_dest.Y, vec_nodes);
        Node_Graph closest_dest = find_closest_node(pos_grid_dest.X, pos_grid_dest.Y, pos_grid_start.X, pos_grid_start.Y, vec_nodes);

        if (closest_start.number() == -1 || closest_dest.number() == -1)
        {
                irr::core::vector3df start = current_pos;
                irr::core::vector3df dest = irr::core::vector3df(x_dest, current_pos.Y, y_dest); //grid_to_pix(pos_grid_dest);
                compute_mvt(start, dest);
        }
        else
        {
                
                compute_mvt_to_grid(current_pos, closest_start);

                std::string name = "";
                name += std::to_string(closest_start.number());
                name += "-";
                name += std::to_string(closest_dest.number());

                std::map<std::string, Path>::iterator path_it = map_paths.find(name);

                std::string s = path_it->first;

                Path path = path_it->second;

                for (int k = 1 ; k < path.path().size() ; k++)
                {
                        compute_mvt_grid(path.path()[k-1], path.path()[k]);
                }
                irr::core::vector3df dest = irr::core::vector3df(x_dest, current_pos.Y, y_dest); //grid_to_pix(pos_grid_dest);

                compute_mvt_from_grid(dest, closest_dest);

        }

        std::cout << "End Compute Movement" << std::endl;
        

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



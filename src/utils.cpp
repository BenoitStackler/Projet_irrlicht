#include "utils.hpp"

#define offset 2.0f
#define multiplicator 10.0f
#define dist_collide 5.0f


extern bool EndGame;
extern bool Win;

irr::core::vector3df grid_to_pix(irr::core::vector2di coords_grid_2d)
{
    irr::core::vector3df coords_pix;
    coords_pix.X = (coords_grid_2d.X + offset) * multiplicator;
    coords_pix.Y = 25.0f;
    coords_pix.Z = (coords_grid_2d.Y + offset) * multiplicator;

    return coords_pix;
}



irr::core::vector3df grid_to_pix(irr::core::vector3di coords_grid_3d)
{
    irr::core::vector3df coords_pix;
    coords_pix.X = (coords_grid_3d.X + offset) * multiplicator;
    coords_pix.Y = coords_grid_3d.Y;
    coords_pix.Z = (coords_grid_3d.Z + offset) * multiplicator;

    return coords_pix;
}

irr::core::vector2di grid_to_pix_obst(irr::core::vector2di coords_grid_2d)
{
    irr::core::vector2di coords_pix;
    coords_pix.X = (coords_grid_2d.X + offset);
    coords_pix.Y = (coords_grid_2d.Y + offset);

    return coords_pix;
}

irr::core::vector2di pix_to_grid(irr::core::vector3df coords_pix_3d)
{
    irr::core::vector2di coords_grid;
    coords_grid.X = (coords_pix_3d.X / multiplicator - offset);
    coords_grid.Y = (coords_pix_3d.Z / multiplicator - offset);

    return coords_grid;
}


void compute_collisions(World* world_ptr)

{
    auto hero_ptr = world_ptr->getHero();

    auto it_proj_begin = world_ptr->getProjectiles().begin();
    auto it_enemies_begin = world_ptr->getEnemies().begin();
    auto it_obstacles_begin = world_ptr->getObstacles().begin();

    std::cout << "test 1" << std::endl;
    for (auto it_proj = it_proj_begin  ; it_proj != world_ptr->getProjectiles().end() ; it_proj++)
    {
        std::cout << "test 2" << std::endl;
        float dist = sqrt(pow((*it_proj)->position().X - (hero_ptr)->position().X, 2) + pow((*it_proj)->position().Z - (hero_ptr)->position().Z, 2));
        std::cout << "test 3" << std::endl;
        if (dist < dist_collide)
        {
            int dead = (hero_ptr)->impact();
            (*it_proj)->node()->drop();
            world_ptr->getProjectiles().erase(it_proj);
            if (dead)
            {
                EndGame = true;
            }
        }

        for (auto it_enemies = it_enemies_begin  ; it_enemies != world_ptr->getEnemies().end() ; it_enemies++)
        {
            float dist = sqrt(pow((*it_proj)->position().X - (*it_enemies)->position().X, 2) + pow((*it_proj)->position().Z - (*it_enemies)->position().Z, 2));
            if (dist < dist_collide)
            {
                int dead = (*it_enemies)->impact();
                (*it_proj)->node()->drop();
                world_ptr->getProjectiles().erase(it_proj);
                if (dead)
                {
                    (*it_enemies)->node()->drop();
                    world_ptr->getEnemies().erase(it_enemies);
                    if (world_ptr->getEnemies().empty())
                    {
                        EndGame = true;
                        Win = true;
                    }
                }
            }
        }

        for (auto it_obstacles = it_obstacles_begin  ; it_obstacles != world_ptr->getObstacles().end() ; it_obstacles++)
        {
            if ((*it_obstacles)->type() == "Mur")
            {
                auto pos_obst = grid_to_pix((*it_obstacles)->position());
                float dist = sqrt(pow((*it_proj)->position().X - pos_obst.X, 2) + pow((*it_proj)->position().Z - pos_obst.Z, 2));
                if (dist < dist_collide)
                {
                    (*it_proj)->node()->drop();
                    world_ptr->getProjectiles().erase(it_proj);
                }

            }
        }
    }
}
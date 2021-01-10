#include "utils.hpp"

#define offset 2.0f
#define multiplicator 10.0f
#define dist_collide 5.0f


extern bool EndGame;
extern bool Win;
extern World world;

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


void compute_collisions()

{
    auto hero_ptr = world.getHero();

    int it_proj = 0;

    for (auto proj_ptr : world.getProjectiles())
    {
        bool collision_found = false;
        float dist = sqrt(pow((proj_ptr)->position().X - (hero_ptr)->position().X, 2) + pow((proj_ptr)->position().Z - (hero_ptr)->position().Z, 2));
        if (dist < dist_collide)
        {
            int dead = (hero_ptr)->impact();
            
            (proj_ptr)->node()->remove();
            world.deleteProjectile(it_proj);
            it_proj--;
            if (dead)
            {
                EndGame = true;
            }
            collision_found = true;
            std::cout << "Attention, vous avez ete touche.e" << std::endl;
        }

        int it_enemy = 0;
        for (auto enemy_ptr : world.getEnemies())
        {
            if (!collision_found)
            {
                float dist = sqrt(pow((proj_ptr)->position().X - (enemy_ptr)->position().X, 2) + pow((proj_ptr)->position().Z - (enemy_ptr)->position().Z, 2));
                if (dist < dist_collide)
                {
                    collision_found = true;
                    int dead = (enemy_ptr)->impact();
                    (proj_ptr)->node()->remove();
                    world.deleteProjectile(it_proj);
                    it_proj--;
                    if (dead)
                    {
                        (enemy_ptr)->node()->remove();
                        world.deleteEnemy(it_enemy);
                        it_enemy--;
                        if (world.getEnemies().empty())
                        {
                            EndGame = true;
                            Win = true;
                        }
                    }
                }
            }
            it_enemy++;
        }



        for (auto it_obstacles : world.getObstacles())
        {
            if (!collision_found)
            {   
                if ((it_obstacles)->type() == "Mur")
                {
                    irr::core::vector2di index_NW = irr::core::vector2di((it_obstacles)->x(), (it_obstacles)->y());
                    irr::core::vector2di index_SE = index_NW + irr::core::vector2di((it_obstacles)->nx(), (it_obstacles)->ny());
                    auto pos_obst_NW = grid_to_pix(index_NW);
                    auto pos_obst_SE = grid_to_pix(index_SE);

                    //std::cout << pos_obst_SE.X << std::endl;
                    if (proj_ptr->position().X > pos_obst_NW.X && 
                        proj_ptr->position().X < pos_obst_SE.X && 
                        proj_ptr->position().Z > pos_obst_NW.Z && 
                        proj_ptr->position().Z < pos_obst_SE.Z)

                    //float dist = sqrt(pow((proj_ptr)->position().X - pos_obst.X, 2) + pow((proj_ptr)->position().Z - pos_obst.Z, 2));
                    //std::cout << pos_obst.X << std::endl;
                    //if (dist < dist_collide + 10.0f)
                    {
                        collision_found = true;
                        (proj_ptr)->node()->remove();
                        world.deleteProjectile(it_proj);
                        it_proj--;
                    }

                }
            }
        }
        it_proj++;
    }
}
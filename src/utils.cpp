#include "utils.hpp"

#define offset 2.0f
#define multiplicator 10.0f


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

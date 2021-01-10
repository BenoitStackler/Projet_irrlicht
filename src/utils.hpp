#ifndef DEF_UTILS
#define DEF_UTILS

#include <vector>
#include <string>
#include <irrlicht.h>

irr::core::vector3df grid_to_pix(irr::core::vector2di coords_grid_2d);
irr::core::vector3df grid_to_pix(irr::core::vector3di coords_grid_3d);
irr::core::vector2di grid_to_pix_obst(irr::core::vector2di coords_grid_2d);
irr::core::vector2di pix_to_grid(irr::core::vector3df coords_pix_3d);





#endif

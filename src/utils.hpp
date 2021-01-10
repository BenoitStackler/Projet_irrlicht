#ifndef DEF_UTILS
#define DEF_UTILS

#include <vector>
#include <string>
#include <irrlicht.h>

enum ID_Flag
{
    // I use this ISceneNode ID to indicate a scene node that is
    // not pickable by getSceneNodeAndCollisionPointFromRay()
    ID_IsNotPickable = 0,

    // I use this flag in ISceneNode IDs to indicate that the
    // scene node can be picked by ray selection.
    IDFlag_IsPickable = 1 << 0,

    // I use this flag in ISceneNode IDs to indicate that the
    // scene node can be highlighted.  In this example, the
    // homonids can be highlighted, but the level mesh can't.
    IDFlag_IsHighlightable = 1 << 1
};

irr::core::vector3df grid_to_pix(irr::core::vector2di coords_grid_2d);
irr::core::vector3df grid_to_pix(irr::core::vector3di coords_grid_3d);
irr::core::vector2di grid_to_pix_obst(irr::core::vector2di coords_grid_2d);
irr::core::vector2di pix_to_grid(irr::core::vector3df coords_pix_3d);

#endif

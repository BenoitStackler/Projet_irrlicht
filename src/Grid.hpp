#ifndef DEF_GRID
#define DEF_GRID

#include <vector>
#include <string>

#include "Grid.hpp"
#include "Obstacle.hpp"
#include "colormod.hpp"
#include "vec2.hpp"


class Grid
{
    public:
        Grid();
        Grid(int Nx_param, int Ny_param);
        Grid(int Nx_param, int Ny_param, int value);

        /** Sizes of the grid */
        int const& Nx();
        int const& Ny();
        int const N();

        /** Access to the position kx, ky*/
        int& operator()(int kx, int ky);

        /** Access to the position k*/
        int& operator[](int k);

    private:
        int Nx_data;
        int Ny_data;
        std::vector<int> grid_data;

};

Grid create_grid_obstacles(int Nx, int Ny, std::vector<Obstacle> obstacles);
std::vector<vec2> get_nodes_positions(int Nx, int Ny, std::vector<Obstacle> obstacles, Grid grid);

#endif
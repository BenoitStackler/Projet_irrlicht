#include "Grid.hpp"
#include "Obstacle.hpp"
#include "colormod.hpp"
#include "vec2.hpp"
#include <iostream>

/** Constructors */
Grid::Grid(){}

Grid::Grid(int Nx_param, int Ny_param)
    :Nx_data(Nx_param), Ny_data(Ny_param){
        for (int k = 0 ; k < Nx_data*Ny_data ; k++)
            grid_data.push_back(0);
    }

Grid::Grid(int Nx_param, int Ny_param, int value)
    :Nx_data(Nx_param), Ny_data(Ny_param){
        for (int k = 0 ; k < Nx_data*Ny_data ; k++)
            grid_data.push_back(value);
    }

/** Sizes of the grid */
int const& Grid::Nx(){
    return Nx_data;
}

int const& Grid::Ny(){
    return Ny_data;
}

int const Grid::N(){
    return Nx_data*Ny_data;
}

/** Access to the position kx, ky*/
int& Grid::operator()(int kx, int ky){
    if (kx >= Nx_data){
        Color::Modifier red(Color::FG_RED);
        Color::Modifier def(Color::FG_DEFAULT);
        std::cout << red <<"Error" << def << ": Grid::operator(): kx must be smaller than Nx" << std::endl;
    }
    if (ky >= Ny_data){
        Color::Modifier red(Color::FG_RED);
        Color::Modifier def(Color::FG_DEFAULT);
        std::cout << red <<"Error" << def << ": Grid::operator(): ky must be smaller than Ny" << std::endl;
    }

    return grid_data[kx + ky*Nx_data];
}

/** Access to the position k*/
int& Grid::operator[](int k){
    if (k >= Nx_data*Ny_data){
        Color::Modifier red(Color::FG_RED);
        Color::Modifier def(Color::FG_DEFAULT);
        std::cout << red <<"Error" << def << ": Grid::operator(): k must be smaller than N" << std::endl;
    }

    return grid_data[k];
}

Grid create_grid_obstacles(int Nx, int Ny, std::vector<Obstacle> obstacles){
    Grid grid(Nx, Ny);

    for (int k = 0 ; k < obstacles.size() ; k++){
        Obstacle obst = obstacles[k]; 
        for (int i = 0 ; i < obst.nx() ; i++){
            for (int j = 0 ; j < obst.ny() ; j++){
                grid(obst.x() + i, obst.y() + j) = 1;
            }
        }
    }
    return grid;
}

std::vector<vec2> get_nodes_positions(int Nx, int Ny, std::vector<Obstacle> obstacles, Grid grid){
    std::vector<vec2> nodes;
    for (Obstacle obst : obstacles){
        int x = obst.x();
        int y = obst.y();
        int nx = obst.nx();
        int ny = obst.ny();

        // Top-left corner
        if (x > 0 && y > 0){
            if (grid(x-1, y-1) == 0 && grid(x, y-1) == 0 && grid(x-1, y) == 0){
                vec2 p;
                p.x = x-1;
                p.y = y-1;
                nodes.push_back(p);
            }
        }
        
        // Top-right corner
        if (x > 0 && y+ny <= Ny-1){
            if (grid(x-1, y+ny) == 0 && grid(x, y+ny) == 0 && grid(x-1, y+ny-1) == 0){
                vec2 p;
                p.x = x-1;
                p.y = y+ny;
                nodes.push_back(p);
            }
        }

        // Bottom-left corner
        if (x+nx <= Nx-1 && y > 0){
            if (grid(x+nx, y-1) == 0 && grid(x+nx-1, y-1) == 0 && grid(x+nx, y) == 0){
                vec2 p;
                p.x = x+nx;
                p.y = y-1;
                nodes.push_back(p);
            }
        }

        // Bottom-right corner
        if (x+nx <= Nx-1 && y+ny <= Ny-1){
            if (grid(x+nx, y+ny) == 0 && grid(x+nx-1, y+ny) == 0 && grid(x+nx, y+ny-1) == 0){
                vec2 p;
                p.x = x+nx;
                p.y = y+ny;
                nodes.push_back(p);
            }
        }
    }

    return nodes;
}
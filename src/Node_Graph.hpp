#ifndef DEF_NODE_GRAPH
#define DEF_NODE_GRAPH

#include <vector>
#include <unordered_set>
#include "Grid.hpp"
#include "vec2.hpp"


class Node_Graph
{
    public:
        Node_Graph();
        Node_Graph(int x_param, int y_param);
        Node_Graph(int x_param, int y_param, int node_number_param);


        /** Sizes of the grid */
        int const& x();
        int const& y();
        int const size_neighbours();
        std::vector<Node_Graph> const& neighbours();
        std::vector<Node_Graph> const& tested_neighbours();
        int const number();

        void set_neighbour(const std::vector<Node_Graph>& neighbours);
        void set_tested_neighbour(const std::vector<Node_Graph>& neighbours);
        void add_neighbour(const Node_Graph& node);
        void add_tested_neighbour(const Node_Graph& node);
        void compute_neighbours(const std::vector<Node_Graph>& nodes, Grid& grid_obstacles);

        friend bool operator== ( const Node_Graph &n1, const Node_Graph &n2);
        
    private:
        int x_data;
        int y_data;
        int node_number_data;
        std::vector<Node_Graph> neighbours_data;
        std::vector<Node_Graph> tested_neighbours_data;

};

bool find(std::vector<Node_Graph>& vect, Node_Graph elem, Node_Graph& node_found);
Node_Graph find_closest_node(int x, int y, std::vector<Node_Graph> graph);
Node_Graph find_closest_node(int x, int y, int x_dest, int y_dest, std::vector<Node_Graph> graph);


int octant_number(vec2 const& p0,vec2 const& p1);
std::vector<vec2> bresenham_first_octant(vec2 const& p0,vec2 const& p1,int const octant);
std::vector<vec2> bresenham(vec2 const& p0,vec2 const& p1);
vec2 symmetry_octant(vec2 const& p,int const octant);
vec2 symmetry_octant_inverse(vec2 const& p,int const octant);

#endif
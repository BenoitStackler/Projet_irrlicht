#include "Node_Graph.hpp"
#include <cmath>
#include <iostream>


// Constructors
Node_Graph::Node_Graph()
    :x_data(0), y_data(0){}

Node_Graph::Node_Graph(int x_param, int y_param)
    :x_data(x_param), y_data(y_param){}

Node_Graph::Node_Graph(int x_param, int y_param, int node_number_param)
    :x_data(x_param), y_data(y_param), node_number_data(node_number_param){}


int const& Node_Graph::x(){
    return x_data;
}

int const& Node_Graph::y(){
    return y_data;
}

int const Node_Graph::size_neighbours(){
    int const s = neighbours_data.size();
    return s;
}

std::vector<Node_Graph> const& Node_Graph::neighbours(){
    return neighbours_data;
}

std::vector<Node_Graph> const& Node_Graph::tested_neighbours(){
    return tested_neighbours_data;
}

int const Node_Graph::number() const {
    return node_number_data;
}

void Node_Graph::add_neighbour(const Node_Graph& node){
    neighbours_data.push_back(node);
}

void Node_Graph::add_tested_neighbour(const Node_Graph& node){
    tested_neighbours_data.push_back(node);
}

void Node_Graph::set_neighbour(const std::vector<Node_Graph>& neighbours){
    neighbours_data = neighbours;
}


void Node_Graph::set_tested_neighbour(const std::vector<Node_Graph>& neighbours){
    tested_neighbours_data = neighbours;
}

void Node_Graph::compute_neighbours(const std::vector<Node_Graph>& nodes, Grid& grid_obstacles){
    for (Node_Graph node_test : nodes){
        if ((x_data != node_test.x()) || (y_data != node_test.y())){

            vec2 p0;
            p0.x = this->x();
            p0.y = this->y();
            vec2 p1;
            p1.x = node_test.x();
            p1.y = node_test.y();

            std::vector<vec2> path = bresenham(p0, p1);
            bool crosses_obstacle = false;

            int s = path.size();
            int k = 0;

            while (!crosses_obstacle && k<s){
                vec2 p = path[k];
                if (grid_obstacles(p.x, p.y) == 1)
                    crosses_obstacle = true;
                k++;
            }
            if (!crosses_obstacle)
                this->add_neighbour(node_test);
            
        }
    }
}

bool operator== ( const Node_Graph &n1, const Node_Graph &n2) 
{
        return (n1.x_data == n2.x_data && n1.y_data == n2.y_data);
}





bool find(std::vector<Node_Graph>& vect, Node_Graph elem, Node_Graph& node_found){
    bool ret = false;
    for (int k=0 ; k< vect.size() ; k++){
        if (vect[k].number() == elem.number()){
            ret = true;
            node_found = vect[k];
            break;
        }
    }
    return ret;
}


/** Compute Bresenham algorithm in the first octant */
std::vector<vec2> bresenham_first_octant(vec2 const& p0,vec2 const& p1,int const octant)
{
    std::vector<vec2> path;
    int dx = p1.x - p0.x;
    int dy = p1.y - p0.y;

    float alpha = dy/float(dx);
    int y0 = p0.y;

    for(int x = p0.x; x <= p1.x; ++x){
        
        vec2 p_inf;
        vec2 p_sup;
        p_inf.x = x;
        p_sup.x = x;
        p_inf.y = floor(alpha*(x-p0.x) + y0);
        p_sup.y = ceil(alpha*(x-p0.x) + y0);
        p_inf = symmetry_octant_inverse(p_inf, octant);
        p_sup = symmetry_octant_inverse(p_sup, octant);
        path.push_back(p_inf);
        path.push_back(p_sup);
    }
    return path;

}

std::vector<vec2> bresenham(vec2 const& p0,vec2 const& p1)
{
    int const octant = octant_number(p0,p1);
    vec2 const p0_octant = symmetry_octant(p0,octant);
    vec2 const p1_octant = symmetry_octant(p1,octant);


    std::vector<vec2> path = bresenham_first_octant(p0_octant,p1_octant,octant);
    
    return path;
}


int octant_number(vec2 const& p0,vec2 const& p1)
{
    int const x0 = p0.x;
    int const y0 = p0.y;

    int const x1 = p1.x;
    int const y1 = p1.y;

    int const dx = x1-x0;
    int const dy = y1-y0;

    if( dy>=0 )
    {
        if( dx>=0 )
        {
            if( dx>=dy )   return 0;
            else           return 1;
        }
        else
        {
            if( -dx>=dy )  return 3;
            else           return 2;
        }
    }
    else
    {
        if( dx>=0 )
        {
            if( dx>=-dy )  return 7;
            else           return 6;
        }
        else
        {
            if( -dx>=-dy ) return 4;
            else           return 5;
        }
    }

}

// Going from original position to first octant
vec2 symmetry_octant(vec2 const& p,int const octant)
{
    int const x = p.x;
    int const y = p.y;

    vec2 p_octant;

    switch(octant)
    {
    case 0: 
        p_octant.x = x;
        p_octant.y = y;
        return p_octant;
    case 1:
        p_octant.x = y;
        p_octant.y = x;
        return p_octant;
    case 2: 
        p_octant.x = y;
        p_octant.y = -x;
        return p_octant;
    case 3: 
        p_octant.x = -x;
        p_octant.y = y;
        return p_octant;
    case 4: 
        p_octant.x = -x;
        p_octant.y = -y;
        return p_octant;
    case 5: 
        p_octant.x = -y;
        p_octant.y = -x;
        return p_octant;
    case 6: 
        p_octant.x = -y;
        p_octant.y = x;
        return p_octant;
    case 7: 
        p_octant.x = x;
        p_octant.y = -y;
        return p_octant;
    }
    return p;
}

// Going from first octant to original position
vec2 symmetry_octant_inverse(vec2 const& p,int const octant)
{
    int const x = p.x;
    int const y = p.y;

    vec2 p_octant;
    switch(octant)
    {
        case 0: 
        p_octant.x = x;
        p_octant.y = y;
        return p_octant;
    case 1:
        p_octant.x = y;
        p_octant.y = x;
        return p_octant;
    case 2: 
        p_octant.x = -y;
        p_octant.y = x;
        return p_octant;
    case 3: 
        p_octant.x = -x;
        p_octant.y = y;
        return p_octant;
    case 4: 
        p_octant.x = -x;
        p_octant.y = -y;
        return p_octant;
    case 5: 
        p_octant.x = -y;
        p_octant.y = -x;
        return p_octant;
    case 6: 
        p_octant.x = y;
        p_octant.y = -x;
        return p_octant;
    case 7: 
        p_octant.x = x;
        p_octant.y = -y;
        return p_octant;

    }
    return p;
}


Node_Graph find_closest_node(int x, int y, std::vector<Node_Graph> graph)
{
    float min_dist = 10000.0f;
    int index_closest = 0;

    for (int k = 0 ; k <  graph.size() ; k++)
    {
        float dist = sqrt(pow(x - graph[k].x(), 2) + pow(y - graph[k].y(), 2));
        if (dist < min_dist)
        {
            index_closest = k;
            min_dist = dist;
        }
    }

    return graph[index_closest];
}


Node_Graph find_closest_node(int x, int y, int x_dest, int y_dest, std::vector<Node_Graph> graph)
{
    float min_dist = sqrt(pow(x - x_dest, 2) + pow(y - y_dest, 2));
    int index_closest = -1;

    for (int k = 0 ; k <  graph.size() ; k++)
    {
        float dist = sqrt(pow(x - graph[k].x(), 2) + pow(y - graph[k].y(), 2));
        if (dist < min_dist)
        {
            index_closest = k;
            min_dist = dist;
        }
    }

    if (index_closest == -1)
    {
        return Node_Graph(x_dest, y_dest, -1);
    }

    else
    {
        return graph[index_closest];
    }
}
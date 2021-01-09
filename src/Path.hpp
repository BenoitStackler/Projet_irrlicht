#ifndef DEF_PATH
#define DEF_PATH

#include <vector>
#include <string>
#include "Node_Graph.hpp"


class Path
{
    public:
        Path();
        Path(float dist_param);
        Path(Node_Graph node, Node_Graph start, float dist_param);
        Path(Path path_param, Node_Graph next, float dist_param);
        

        float const& dist();
        std::vector<Node_Graph> const& path();

        void reverse();
        int size();
        



    private:
        float dist_data;
        std::vector<Node_Graph> path_data;
};


Path find_path(std::vector<Node_Graph>& Graph, Node_Graph& source, Node_Graph& target);
Path find_path_recursive(std::vector<Node_Graph>& Nodes_left, Node_Graph& source, Node_Graph& target);

#endif
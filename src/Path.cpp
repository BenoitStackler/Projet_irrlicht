#include "Path.hpp"
#include "colormod.hpp"
#include <iostream>
#include "Node_Graph.hpp"
#include <cmath>


Path::Path(){}
Path::Path(float dist_param):dist_data(dist_param){}
Path::Path(Node_Graph node, Node_Graph start, float dist_param){
    path_data.push_back(start);
    path_data.push_back(node);
    dist_data = dist_param;
}
Path::Path(Path path_param, Node_Graph next, float dist_param){
    path_data = path_param.path();
    path_data.push_back(next);
    if (path_param.dist() < 0){
        dist_data = -1;
    }
    else
    {
        dist_data = path_param.dist() + dist_param;
    }
    
}


float const& Path::dist(){
    return dist_data;
}

std::vector<Node_Graph> const& Path::path(){
    return path_data;
}

int Path::size(){
    return path_data.size();
}



void Path::reverse(){
    std::vector<Node_Graph> newPath;
    for (int k = path_data.size()-1 ; k >= 0 ; k--){
        newPath.push_back(path_data[k]);
    }

    path_data = newPath;
}


Path find_path(std::vector<Node_Graph>& Graph, Node_Graph& source, Node_Graph& target){
    std::vector<Node_Graph> Nodes_left;
    for (Node_Graph v : Graph){
        if (!(v == source)){
            Nodes_left.push_back(v);
        }
    }

    Path path_S_to_T;
    path_S_to_T = find_path_recursive(Nodes_left, source, target);
    path_S_to_T.reverse();
    return path_S_to_T;
}

Path find_path_recursive(std::vector<Node_Graph>& Nodes_left, Node_Graph& source, Node_Graph& target){
    std::vector<Node_Graph> Nodes_possible;

    for (Node_Graph node : source.neighbours()){
        Node_Graph* node_found = new Node_Graph();
        if (find(Nodes_left, node, *node_found)){
            Nodes_possible.push_back(*node_found);
        }
    }

    Node_Graph* node_found = new Node_Graph();
    // Dead end
    if (Nodes_possible.empty()){
        Path wrongPath(-1.0f);
        return wrongPath;
    }

    // Target found
    if (find(Nodes_possible, target, *node_found)){
        Path finalPath(source, target, sqrt(pow(source.x() - target.x(), 2) + pow(source.y() - target.y(), 2)));
        return finalPath;
    }

    // Path found
    std::vector<Path> possiblePaths;
    for (Node_Graph node_next : Nodes_possible){
        float dist = sqrt(pow(node_next.x() - source.x(), 2) + pow(node_next.y() - source.y(), 2));
        std::vector<Node_Graph> Nodes_left_after;
        for (int k=0 ; k < Nodes_left.size() ; k++){
            if (!(Nodes_left[k] == node_next)){
                Nodes_left_after.push_back(Nodes_left[k]);
            }
        }

        Path f = find_path_recursive(Nodes_left_after, node_next, target);
        Path foundPath(f, source, dist);
        possiblePaths.push_back(foundPath);
    }

    float min_dist = 10000000.0f;
    int index_min_dist = -1;
    for (int k=0 ; k<possiblePaths.size() ; k++){
        if (possiblePaths[k].dist() < min_dist && possiblePaths[k].dist() >= 0){
            min_dist = possiblePaths[k].dist();
            index_min_dist = k;
        }
    }


    if (index_min_dist == -1){
        Path wrongPath(-1.0f);
        return wrongPath;
    }
    else
    {
        return possiblePaths[index_min_dist];
    }
}


#ifndef BreadthFirstSearch_H
#define BreadthFirstSearch_H

#include <vector>
#include <queue>
#include <queue>
#include <algorithm>
#include "Graph.h"


std::vector< int > BreadthFirstSearch( const GraphL& graph, int start_node ){

    std::vector< bool > visited( graph.numNodes() );
    visited[ start_node ] = true;

    std::queue< int > queue;
    queue.push( start_node );

    std::vector< int > precedingNodes( graph.numNodes(), -1 );

    while( !queue.empty() ){
        auto current = queue.front();
        queue.pop();

        for( const auto& node : graph.adlist( current) ){
            if( visited[ node ] ) continue;
            visited[node] = true;
            precedingNodes[node] = current;
            queue.push( node );
        }
    }
    return precedingNodes;

}



std::vector< int > reconstructedPath( int start_node, int end_node, const std::vector< int >& precedingNodes ){
    
    std::vector< int > path = { end_node };
    int current;
    while( ( current = precedingNodes[ path.back() ] ) != -1 ){
        path.push_back( current );
    }

    std::reverse( path.begin(), path.end() );
    if( path.front() != start_node ){
        return std::vector< int >();
    } 
    return path;
}


std::vector< int > shortestPath( const GraphL& graph, int start_node, int end_node ){
    std::vector< int > precedingNodes = BreadthFirstSearch( graph, start_node );
    return reconstructedPath( start_node, end_node, precedingNodes );
}


#endif

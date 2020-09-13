#ifndef DepthFirstSearch_H
#define DepthFirstSearch_H

#include <vector>
#include <iostream>
#include "Graph.h"


void depthFirstSearch_recursion( const GraphL& graph, int node, std::vector< bool >& visited, std::list< int >& traversion ){

    visited[ node ] = true;
    traversion.push_back( node );
    
    for( const auto& entry : graph.adlist( node ) ){
        if( visited[ entry ] ) continue;
        depthFirstSearch_recursion( graph, entry, visited, traversion );
    }
}


std::list<int> depthFirstSearch( const GraphL& graph, int node, std::vector< bool >& visited ){//, bool keep_visited = false ){
    
    std::list< int > traversion;
    depthFirstSearch_recursion( graph, node, visited, traversion );
    return traversion;
}


std::map< int, std::list< int > > connectedComponents( const GraphL& graph ){
    std::map< int, std::list< int > > ret;
    int current_index = 0;
    std::vector< bool > visited( graph.numNodes(), false );
    for( const auto& item : graph ){ 
        auto node = item.first;
        if( visited[ node ] ) continue;
        auto traversion = depthFirstSearch( graph, node, visited );
        for( const auto& entry : traversion ){
            ret[current_index].push_back( entry  );
        }
        ++current_index;
    }
    return ret;
}
#endif

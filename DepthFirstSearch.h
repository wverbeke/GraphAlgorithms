#ifndef DepthFirstSearch_H
#define DepthFirstSearch_H

#include <vector>
#include <iostream>
#include "Graph.h"


void depthFirstSearch_recursion( const GraphL& graph, int node, std::vector< bool >& visited, std::list< int >& traversion ){

    if( visited[ node ] ) return;
    else visited[ node ] = true;
    traversion.push_back( node );
    
    for( const auto& entry : graph.adlist( node ) ){
        depthFirstSearch_recursion( graph, entry, visited, traversion );
    }
}


std::list<int> depthFirstSearch( const GraphL& graph, int node, std::vector< bool >& visited ){//, bool keep_visited = false ){
    
    //static std::vector< bool > visited;
    //if( visited.empty() || !keep_visited ){
    //    visited = std::vector< bool >( graph.numNodes() );
    //}
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
        ret[current_index] = std::list< int >();
        for( const auto& entry : traversion ){
            ret[current_index].push_back( entry  );
        }
        ++current_index;
    }
    return ret;
}
#endif

#ifndef TopologicalSort_H
#define TopologicalSort_H

#include <vector>
#include <algorithm>

#include "Graph.h"



void dfs( const GraphL& graph, int start_node, std::vector< bool >& visited, std::vector< int >& traversion ){
    if( visited[ start_node ] ) return;
    visited[ start_node ] = true;
    
    for( const auto& node : graph.adlist( start_node ) ){
        dfs( graph, node, visited, traversion );
    }
    traversion.push_back( start_node );
}



std::vector< int > topologicalSort( const GraphL& graph ){

    std::vector< bool > visited( graph.numNodes() );

    //initially fill node_order in reverse
    std::vector< int > node_order;

    for( const auto& entry : graph ){
        auto node = entry.first;
        if( visited[ node ] ) continue;
        std::vector< int > traversion;
        dfs( graph, node, visited, traversion );
        for( const auto& t : traversion ){
            node_order.push_back( t );
        }
    }
    
    std::reverse( node_order.begin(), node_order.end() );
    return node_order;
}


int dfs_optimized( const GraphL& graph, int& current_index, int start_node, std::vector< bool >& visited, std::vector< int >& ordering ){
    visited[ start_node ] = true;
    for( const auto& node : graph.adlist( start_node ) ){
        if( visited[ node ] ) continue;
        current_index = dfs_optimized( graph, current_index, node, visited, ordering );
    }
    ordering[ current_index ] = start_node;
    return current_index - 1;
}


std::vector< int > topologicalSort_optimized( const GraphL& graph ){
    std::vector< bool > visited( graph.numNodes(), false );
    std::vector< int > ordering( graph.numNodes() );
    int current_index = ordering.size() - 1;
    for( const auto& entry : graph ){
        auto node = entry.first;
        if( visited[ node ] ) continue;
        current_index = dfs_optimized( graph, current_index, node, visited, ordering );
    }
    return ordering;
}



template< typename T > int dfs( const GraphLW< T >& graph, int current_index, int start_node, std::vector< bool >& visited, std::vector< int >& ordering ){
    visited[ start_node ] = true;
    for( const auto& edge : graph.adList( start_node ) ){
        if( visited[ edge.to() ] ) continue;
        current_index = dfs( graph, current_index, edge.to(), visited, ordering );
    }
    ordering[ current_index ] = start_node;
    return current_index - 1;

}




template< typename T > std::vector< int > topologicalSort( const GraphLW< T >& graph ){

    std::vector< bool > visited( graph.numNodes(), false );
    std::vector< int > ordering( graph.numNodes() );
    int current_index = ordering.size();

    for( const auto& entry : graph ){
        auto node = entry.first;
        if( visited[node] ) continue;
        current_index = dfs( graph, current_index, node, visited, ordering );
    }
    return ordering;
}

#endif

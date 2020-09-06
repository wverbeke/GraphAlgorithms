#ifndef shortestPathDAG_H
#define shortestPathDAG_H


#include <vector>

#include "Graph.h"
#include "topologicalSort.h"


template< typename T > std::vector< int > shortestPathDAG( const GraphLW< T >& graph, const int start_node ){

    auto topSort = topologicalSort( graph );

    //assume graph indices start at 0
    //index i corresponds to distance from start_node to node i
    std::vector< int > distances( graph.numNodes(), -1 );
    distances[ start_node ] = 0;

    for( const auto& node : topSort ){
        if( distances[ node ] == -1 ) continue;

        for( const auto& next : graph.adList( node ) ){
            int new_dist = distances[ node ] + next.weight();
            if( distances[ next.to() ] == -1 ) distances[ next.to() ] = new_dist;
            else if( distances[next.to() ] > new_dist ){
                distances[next.to()] = new_dist;
            }
        }
    }
    return distances;
}



template< typename T > std::vector< int > longestPathDAG( GraphLW< T >& graph, const int start_node ){
    graph.invertWeights();
    auto path = shortestPathDAG( graph, start_node );
    for( auto& entry : path ){
        entry = -1*entry;
    }
    graph.invertWeights();
    return path;
}


#endif 

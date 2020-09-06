#ifndef BellmanFord_H
#define BellmanFord_H


#include "Graph.h"
#include <limits>
#include <vector>


template< typename T > std::vector< T > bellmanFord( const GraphLW< T >& graph, int start_index ){

    std::vector< T > dist( graph.numNodes(), std::numeric_limits< T >::infinity() );
    dist[ start_index ] = 0;

    //initial loop to set all distances
    //final for any node not involved in negative cycle
    for( int i = 0; i < graph.numNodes(); ++i ){
        
        //double loop here is effectively a single loop over all edges
        for( int j = 0; j < graph.numNodes(); ++j ){
            for( const auto& edge : graph.adList( j ) ){
                T new_dist = dist[j] + edge.weight();
                if( new_dist < dist[ edge.to() ] ){
                    dist[ edge.to() ] = new_dist;
                }            
            }
        }
    }

    //second loop to cement negative cycles
    for( int i = 0; i < graph.numNodes(); ++i ){
        for( int j = 0; j < graph.numNodes(); ++j ){
            for( const auto& edge : graph.adList( j ) ){
                T new_dist = dist[j] + edge.weight();
                if( new_dist < dist[ edge.to() ] ){
                    dist[ edge.to() ] = -std::numeric_limits< T >::infinity();
                }
            }
        }
    }
    return dist;
}

#endif

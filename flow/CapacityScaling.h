#ifndef CapacityScaling_H
#define CapacityScaling_H

/*
implement Ford-Fulkerson method, using a DFS with capacity scaling to find the augmented paths
*/

#include <vector>
#include <limits>
#include <cmath>
#include "Graph.h"


template< typename T > T dfs_capacityScaling( Graph< T >& graph, int start_node, int sink, T flow, long delta, std::vector< bool >& visited ){
    if( start_node == sink ) return flow;

    visited[ start_node ] = true;
    
    for( auto& edgePtr : graph.adList( start_node ) ){
        auto& edge = *edgePtr;
        if( visited[ edge.to() ] ) continue;
        if( edge.remainingCapacity() <= delta ) continue;

        T bottleneck = dfs_capacityScaling( graph, edge.to(), sink, std::min( flow, edge.remainingCapacity() ), delta, visited );

        if( bottleneck > 0 ){
            edge.addFlow( bottleneck );
            return bottleneck;
        }
    }
    return 0;
}


template< typename T > long maxPowerOfTwoLessEqual( T num ){

    //base 2 logarithm
    T log = std::log( num ) / std::log( 2 );
    long log_floor = std::floor( log );
    return std::pow( 2, log_floor ); 
}



template< typename T > T fordFulkerson_DFS_capacityScaling( Graph< T >& graph, int source, int sink ){

    T total_flow = 0;
    T flow_augment = std::numeric_limits< T >::infinity();

    //find the maximum edge capacity
    T max_capacity = 0;
    for( const auto& entry : graph ){
        auto node = entry.first;
        for( const auto& edgePtr : graph.adList( node ) ){
            if( edgePtr->capacity() > max_capacity ){
                max_capacity = edgePtr->capacity();
            }
        }
    }
    
    //find largest power of 2 less or equal to max_capacity
    long delta = maxPowerOfTwoLessEqual( max_capacity );

    while( flow_augment > 0 || delta != 0 ){
        std::vector< bool > visited( graph.numNodes(), false );
        flow_augment = dfs_capacityScaling( graph, source, sink, std::numeric_limits< T >::infinity(), delta, visited );
        if( flow_augment > 0 ){
            total_flow += flow_augment;
        } else {
            delta /= 2;
        }
    }

    return total_flow;
}


#endif

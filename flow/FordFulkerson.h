#ifndef FordFulkerson_H
#define FordFulkerson_H


#include <vector>
#include <limits>
#include <algorithm>
#include "Graph.h"

//implementation of Ford-Fulkerson method, using a DFS to find augmenting paths
//worst-case scenario scaling is O( f * E ) with F the total flow


template< typename T > T depthFirstSearch( Graph< T >& graph, int start_node, int drain, T flow, std::vector< bool >& visited ){

    std::cout << "node : " << start_node << "\tflow = " << flow << std::endl;
    if( start_node == drain ){
        std::cout << "reached end with flow " << flow << std::endl;
        return flow;
    }
    visited[ start_node ] = true;

    for( auto& edgePtr : graph.adList( start_node ) ){
        auto& edge = *edgePtr;
        if( visited[ edge.to() ] ) continue;
        if( edge.remainingCapacity() <= 0 ) continue;

        //WARNING : this variable has to be local, otherwise a 0 from a path not ending in the drain can get propagated all the way back
        T bottleneck = depthFirstSearch( graph, edge.to(), drain, std::min( flow, edge.remainingCapacity() ), visited );

        if( bottleneck > 0 ){
            edge.addFlow( bottleneck );
            return bottleneck;
        }
    }
    return 0;
}


#include <iostream>
template< typename T > T fordFulkerson_DFS( Graph< T >& graph, int source, int drain ){

    T total_flow = 0;
    T flow = std::numeric_limits< T >::infinity();

    while( flow > 0 ){
        std::vector< bool > visited( graph.numNodes(), false );
        flow = depthFirstSearch( graph, source, drain, flow, visited );
        std::cout << "flow = " << flow << std::endl;
        total_flow += flow;
    }
    return total_flow;
}



#endif 

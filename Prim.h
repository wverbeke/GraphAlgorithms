#ifndef Prim_H
#define Prim_H

/*
Implementation of Prim's minimum spanning tree algorithm
*/

#include <vector>
#include <utility>
#include <queue>
#include <limits>

#include "Graph.h"


//add all edges pointing to unvisited nodes to the priority queue
template< typename T, typename Q > void addEdgesToQueue( const GraphLW< T >& graph, int node, Q& pq, std::vector< bool >& visited ){
    
    visited[ node ] = true;
    for( const auto& edge : graph.adList( node ) ){
        if( visited[ edge.to() ] ) continue;
        pq.push( edge );
    }
}


template< typename T > std::pair< std::vector< Edge< T > >, T > primMinimumSpanningTree( const GraphLW< T >& graph ){

    auto comp = []( const Edge< T >& lhs, const Edge< T >& rhs ){ return lhs.weight() > rhs.weight(); };
    std::priority_queue< Edge< T >, std::vector< Edge< T > >, decltype( comp ) > pq( comp );

    std::vector< bool > visited( graph.numNodes(), false );
    std::vector< Edge< T > > minSpanTree;
    T total_cost = 0;

    //choose 0 as starting node, but this can be random in principle
    addEdgesToQueue( graph, 0, pq, visited );
    
    while( !pq.empty() ){
        auto next_edge = pq.top();
        pq.pop();
    
        if( visited[ next_edge.to() ] ) continue;

        minSpanTree.push_back( next_edge );
        total_cost += next_edge.weight();
        addEdgesToQueue( graph, next_edge.to(), pq, visited );
    }

    //no MST found
    if( minSpanTree.size() != ( graph.numNodes() - 1 ) ) return { std::vector< Edge< T > >(), std::numeric_limits< T >::infinity() };

    return { minSpanTree, total_cost };

}




#endif

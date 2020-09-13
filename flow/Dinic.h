#ifndef Dinic_H
#define Dinic_H


//implementation of Dinic's ( Dinitz's ) algorithm to find the maximum flow

#include "Graph.h"
#include <vector>
#include <queue>
#include <limits>



template< typename T > std::vector< int > breadthFirstSearch( Graph< T >& graph, int source, int sink ){

    std::vector< int > levels( graph.numNodes(), -1 );
    std::queue< int > queue;
    queue.push( source );
    levels[ source ] = 0;

    while( !queue.empty() ){
        auto next = queue.front();
        queue.pop();
        if( next == sink ) break;
        for( auto& edgePtr : graph.adList( next ) ){
            auto& edge = *edgePtr;

            if( levels[ edge.to() ] != -1 ) continue;
            if( edge.remainingCapacity() <= 0 ) continue;

            levels[ edge.to() ] = levels[ next ] + 1;
            queue.push( edge.to() ); 
        }
    }

    if( levels[ sink ] == -1 ){
        return std::vector< int >();
    } else {
        return levels;
    }
}


template< typename T > T dfs_levelGraph( Graph< T >& graph, int start_node, int sink, T flow, const std::vector< int >& levels, std::vector< int >& next ){

    if( start_node == sink ) return flow;
    
    //only loop over edges that have not yet been tried
    //once an edge finds a route to the sink, the bottleneck will be returned while the next array stores this edge's index
    //next call to the DFS will then not re-encounter dead ends we have already seen
    for( ; next[ start_node ] < graph.adList( start_node ).size(); ++next[ start_node ] ){
        auto& edge = *graph.adList( start_node )[ next[ start_node ] ];
        if( levels[ edge.to() ] != levels[ edge.from() ] + 1 ) continue;
        if( edge.remainingCapacity() <= 0 ) continue;

        T bottleneck = dfs_levelGraph( graph, edge.to(), sink, std::min( flow, edge.remainingCapacity() ), levels, next );

        if( bottleneck > 0 ){
            edge.addFlow( bottleneck );
            return bottleneck;
        }
    }
    return 0;
}



template< typename T > T dinic( Graph< T >& graph, int source, int sink ){

    T max_flow = 0;
    std::vector< int > levels;
    while( true ){
        levels = breadthFirstSearch( graph, source, sink );
        if( levels.empty() ) return max_flow;

        //this array will be used to avoid going to any dead end
        std::vector< int > next( graph.numNodes(), 0 );

        T augmenting_flow;
        do{
            augmenting_flow = dfs_levelGraph( graph, source, sink, std::numeric_limits< T >::infinity(), levels, next );
            max_flow += augmenting_flow;
        } while( augmenting_flow > 0 );
    }

    return max_flow;
}

#endif 

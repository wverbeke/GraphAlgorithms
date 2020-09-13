#ifndef EdmondsKarp_H
#define EdmondsKarp_H

/*
implementation of Ford Fulkerson method using the Edmonds Karp algorithm to find augmenting flow paths
*/

#include <vector>
#include <queue>
#include <limits>

#include "Graph.h"


template< typename T > T edmondsKarp( Graph< T >& graph, int source, int sink ){

    std::vector< bool > visited( graph.numNodes(), false );
    std::queue< int > queue;

    //we need to know the edge coming from each node, this way we can also trace back the path using the "from()" method
    std::vector< Edge< T >* > previous( graph.numNodes(), nullptr );

    queue.push( source );
    visited[ source ] = true;

    while( !queue.empty() ){
        auto next = queue.front();
        queue.pop();

        //once we found the sink we can already stop
        if( next == sink ) break;

        for( auto& edgePtr : graph.adList( next ) ){
            auto& edge = *edgePtr;

            if( visited[ edge.to() ] ) continue;

            //only consider edges that have remaining capacity left
            if( edge.remainingCapacity() <= 0 ) continue;

            //do it after capacity checking to make sure you did actually visit it
            visited[ edge.to() ] = true;

            queue.push( edge.to() );
            previous[ edge.to() ] = edgePtr.get();
        }
    }

    //no more path to sink has capacity left
    if( previous[ sink ] == nullptr ) return 0;

    //now we know there is still an augmenting path
    T bottleneck = std::numeric_limits< T >::infinity();
    auto current_edge = previous[ sink ]; 
    
    //we know there is a path to the source, so previous edge being nullptr tells us we reached the source
    while( current_edge != nullptr ){
        bottleneck = std::min( bottleneck, current_edge->remainingCapacity() );
        current_edge = previous[ current_edge->from() ];
    }

    //augment the flow along the path
    current_edge = previous[ sink ];
    while( current_edge != nullptr ){
        current_edge->addFlow( bottleneck );
        current_edge = previous[ current_edge->from() ];
    }

    return bottleneck;

}



template< typename T > T fordFulkerson_edmondsKarp( Graph< T >& graph, int source, int sink ){
    T total_flow = 0;
    T current_flow;
    while( ( current_flow = edmondsKarp( graph, source, sink ) ) > 0 ){
        total_flow += current_flow;
    }
    return total_flow;
}




#endif

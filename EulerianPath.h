#ifndef EulerianPath_H
#define EulerianPath_H

#include <vector>
#include <list>
#include <utility>

#include "Graph.h"



template< typename T > std::pair< std::vector< int >, std::vector< int > > countInOut( const GraphLW< T >& graph ){

    //note that we keep a separate in and out array instead of adding and subtracting, since we need the out-array later
    std::vector< int > out( graph.numNodes(), 0 );
    std::vector< int > in( graph.numNodes(), 0 );

    //loop over all edges
    for( const auto& entry : graph ){
        for( const auto& edge : entry.second ){
            ++out[ edge.from() ];
            ++in[ edge.to() ];
        }        
    }

    return { in, out };
}


std::pair< int, int > startEndNode( const std::vector< int >& in, const std::vector< int >& out ){
    size_t num_start = 0;
    size_t num_end = 0;
    int start_node, end_node;
    for( size_t i = 0; i < in.size(); ++i ){

        //no eulerian path can exist
        if( std::abs( out[i] - in[i] ) > 1 ) return {-1, -1};

        if( ( out[i] - in[i] ) == 1 ){
            ++num_start;
            start_node = i;
        } else if( ( in[i] - out[i] ) == 1 ){
            ++num_end;
            end_node = i;
        }

        if( num_start > 1 || num_end > 1 ){
            return {-1, -1};
        }
    }
    return {start_node, end_node};
}


//modified DFS that processes ALL EDGES ( note that DFS is guaranteed to eventually visit all nodes in but not all edges / though several starting positions might be needed in disconnected or directed graph )
template< typename T > void depthFirstSearch( const GraphLW< T >& graph, int start_node, std::list< int >& traversal, std::vector< int >& out, const std::vector< std::vector< Edge< T > > >& edge_vec ){

    //note that we are not tracking whether a particular node has been visited or not, we allow multiple visitations of each node
    //the only thing we ensure is that we follow each edge at least once 
    
    //make sure all the edges have been processed for each node!
    while( out[start_node] != 0 ){

        //retrieve the next edge 
        auto edge = edge_vec[start_node][ --out[start_node] ];
        depthFirstSearch( graph, edge.to(), traversal, out, edge_vec );
    }
    traversal.push_front( start_node );
}


template< typename T > std::list< int > eulerianPath( const GraphLW< T >& graph ){
    
    auto in_out = countInOut( graph );
    auto in = in_out.first;
    auto out = in_out.second;

    //find start and end node, and verify an eulerian path exists
    auto start_end = startEndNode( in, out );
    auto start = start_end.first;
    auto end = start_end.second;

    if( start == -1 || end == -1 ) return std::list< int >();

    //make a vectors with all the edges for each node for easy accessing
    std::vector< std::vector< Edge< T > > > edge_vec( graph.numNodes() );
    for( size_t n = 0; n < graph.numNodes(); ++n ){
        for( const auto& edge : graph.adList( n ) ){
            edge_vec[n].push_back( edge );
        }
    }


    std::list< int > traversal;
    depthFirstSearch( graph, start, traversal, out, edge_vec );

    //make sure we didn't have a disconnected graph, which we recognize by the size of the traversal
    if( traversal.size() != graph.numEdges() + 1 ) return std::list< int >();
    
    return traversal;

}


#endif

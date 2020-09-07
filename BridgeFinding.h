#ifndef BridgeFinding_H
#define BridgeFinding_H

#include "Graph.h"


//bride-finding algorithm for undirected graphs
//runs in O( V + E ) time

template< typename T > void depthFirstSearch( const GraphLW< T >& graph, int start_node, int parent, int& label_count, std::vector< bool >& visited, std::vector< int >& labels, std::vector< int >& lowlinks, std::vector< Edge< T > >& bridges ){

    visited[ start_node ] = true;
    labels[ start_node ] = label_count++; //set to current value then increment
    lowlinks[ start_node ] = labels[ start_node ];
    for( const auto& edge : graph.adList( start_node ) ){
        if( edge.to() == parent ) continue;
        if( !visited[ edge.to() ] ){
            depthFirstSearch( graph, edge.to(), start_node, label_count, visited, labels, lowlinks, bridges );
            if( lowlinks[ edge.to() ] < lowlinks[ start_node ] ){
                lowlinks[ start_node ] = lowlinks[ edge.to() ];
            } else if( lowlinks[ edge.to() ] > labels[ start_node ] ){
                bridges.push_back( edge );
            }
        } else {
            if( labels[ edge.to() ] < lowlinks[ start_node ] ){
                lowlinks[ start_node ] = labels[ edge.to() ];
            }
        }
    }


}

template< typename T > std::vector< Edge< T > > findBridges( const GraphLW< T >& graph ){

    std::vector< Edge< T > > bridges;

    std::vector< bool > visited( graph.numNodes(), false );
    std::vector< int > labels( graph.numNodes() );
    std::vector< int > lowlinks( graph.numNodes() );

    int label_count = 0;

    for( const auto& entry : graph ){
        auto node = entry.first;
        
        if( visited[ node ] ) continue;  
        depthFirstSearch( graph, node, -1, label_count, visited, labels, lowlinks, bridges  );
    }

    return bridges;


}
#endif

#ifndef Tarjan_H
#define Tarjan_H

#include <vector>
#include <algorithm>
#include <stack>
#include "Graph.h"


//Implement Tarjan's algorithm to find strongly connected components in DIRECTED graphs


template< typename T > void depthFirstSearchTarjan( const GraphLW< T >& graph, int start_node, int& label_count, std::vector< int >& labels, std::vector< int >& lowlinks, std::stack< int >& stack, std::vector< bool >& in_stack ){

    labels[ start_node ] = label_count++;
    lowlinks[ start_node ] = labels[ start_node ];
    stack.push( labels[ start_node] );
    in_stack[ labels[ start_node ] ] = true;

    for( const auto& edge : graph.adList( start_node ) ){

        //unvisited
        if( labels[ edge.to() ] == -1 ) depthFirstSearchTarjan( graph, edge.to(), label_count, labels, lowlinks, stack, in_stack );

        //if the previous node is on the stack, propagate low-link values
        if( in_stack[ edge.to() ] ){
            lowlinks[ start_node ] = std::min( lowlinks[ edge.to() ], lowlinks[ start_node ] );
        }
    }

    if( lowlinks[ start_node ] == labels[ start_node ] ){
        while( stack.top() != labels[ start_node ] ){
            in_stack[ stack.top() ] = false;
            lowlinks[ stack.top() ] = labels[ start_node ]; //is this really necessary???
            stack.pop();
        }
        in_stack[ stack.top() ] = false;
        stack.pop();
    }
}




template< typename T > std::map< int, std::vector< int > > tarjan( const GraphLW< T >& graph ){

    std::vector< int > labels( graph.numNodes(), -1 );
    int label_count = 0;
    std::vector< int > lowlinks( graph.numNodes() );
    std::vector< bool > in_stack( graph.numNodes(), false );
    std::stack< int > stack;

    for( const auto& entry : graph ){
        auto node = entry.first;
        if( labels[ node ] != -1 ) continue;
        depthFirstSearchTarjan( graph, node, label_count, labels, lowlinks, stack, in_stack );

    }

    std::map< int, std::vector< int > > connected_components;
    for( size_t i = 0; i < lowlinks.size(); ++i ){
        connected_components[ lowlinks[i] ].push_back( i );        
    }
    return connected_components;
}



#endif 

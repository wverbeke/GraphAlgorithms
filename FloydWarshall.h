#ifndef FloydWarshall_H
#define FloydWarshall_H

#include "Graph.h"
#include <limits>
#include <vector>
#include <utility>


template< typename T > std::pair< std::vector< std::vector< T > >, std::vector< std::vector< int > > > floydWarshall( const GraphMW< T >& graph ){


    //keep track of current best distances 
    std::vector< std::vector< T > > dist = graph.weights();

    //also keep track of shortest path
    //use -1 default values
    std::vector< std::vector< int > > next( graph.numNodes(), std::vector< int >( graph.numNodes(), -1) );
    for( int i = 0; i < graph.numNodes(); ++i ){
        for( int j = 0; j < graph.numNodes(); ++j ){
            if( graph[i][j] < std::numeric_limits< T >::infinity() ){
                next[i][j] = j;
            }
        }
    }


    //for every possible node, process all optimal paths routing through this node and all preceding ones
    for( int k = 0; k < graph.numNodes(); ++k ){

        //for each i, j pair check if current best path, including potential routes via 0 to k-1, is better than path through k ( from previous best path from i to k )
        for( int i = 0; i < graph.numNodes(); ++i ){
            for( int j = 0; j < graph.numNodes(); ++j ){
                auto new_dist = dist[ i ][ k ] + dist[ k ][ j ];
                if( new_dist < dist[ i ][ j ] ){
                    dist[ i ][ j ] = new_dist;

                    //entry i,j denotes the next step to take to go from i to j / Since we now route via k we first need to take the next step to k
                    next[ i ][ j ] = next[ i ][ k ];
                }
            }
        }
    }

    //check for the potential presence of negative cycles, if we can further reduce a distance after the full processing above, it means a negative cycle is present 
    for( int k = 0; k < graph.numNodes(); ++k ){
        for( int i = 0; i < graph.numNodes(); ++i ){
            for( int j = 0; j < graph.numNodes(); ++j ){
                auto new_dist = dist[ i ][ k ] + dist[ k ][ j ];
                if( new_dist < dist[ i ][ j ] ){
                    dist[ i ][ j ] = - std::numeric_limits< T >::infinity();
                    next[ i ][ j ] = -1;
                }
            }
        }
    }

    return { dist, next };
}



template< typename T > std::vector< int > reconstructPath( int start_node, int end_node, const std::vector< std::vector< int > >& next, const std::vector< std::vector< T > >& dist ){

    std::vector< int > path;
    if( dist[ start_node ][ end_node ] == std::numeric_limits< T >::infinity() ) return path;

    int current = start_node; 
    path.push_back( start_node );
    if( start_node == end_node ) return path;
    while( true ){
        current = next[ current ][ end_node ];
        path.push_back( current );
        if( current == end_node || current == -1 ) break;
    }

    //value to indicate path is trapped in negative cycle
    if( path.back() == -1 ){
        return {-1};
    } 

    return path; 
}

#endif

#ifndef Dijkstra_H
#define Dijkstra_H

#include <queue>
#include <utility>
#include <algorithm>
#include "Graph.h"

#include <iostream>

//Dijkstra's lazy shortest path algorithm
template< typename T > std::pair< std::vector< T > , std::vector< int > > dijkstraLazy( const GraphLW< T >& graph, int start_node, int end_node = -1 ){
        
    //priority queue to track next element
    auto comp = []( const std::pair< int, int >& lhs, const std::pair< int, int >& rhs ){ return lhs.second > rhs.second; };
    std::priority_queue< std::pair< int, int >, std::vector< std::pair< int, int > >, decltype( comp ) > pq( comp );


    //distances with default value -1 for unseen vertices 
    std::vector< int > distances( graph.numNodes(), -1 );
    std::vector< bool > visited( graph.numNodes(), false );

    //also keep track of paths taken
    std::vector< int > preceding( graph.numNodes(), -1 );

    //initialize self
    pq.push( {start_node, 0} );
    distances[ start_node ] = 0;

    while( !pq.empty() ){
        auto top = pq.top();
        pq.pop();
        //if( visited[ top.first ] ) continue;
        visited[ top.first ] = true;

        //optimization : instant skip if node already has a better distance
        //it means that processing other nodes already gave a better distance to this node than routing through this one
        if( distances[ top.first ] != -1 && distances[ top.first ] < top.second ) continue;

        for( const auto& edge : graph.adList( top.first ) ){
            if( visited[ edge.to() ] ) continue; //more efficient to add the continue statement in the inner loop so no useless checks are done
            int new_dist = distances[ top.first ] + edge.weight();
            if( distances[ edge.to() ] == -1 || new_dist < distances[ edge.to() ] ){
                distances[ edge.to() ] = new_dist;
                pq.push( { edge.to(), new_dist } );

                preceding[ edge.to() ] = top.first;
            }
        }
        if( top.first == end_node ) break;
    }

    return { distances, preceding };
}


template< typename T > std::vector< int > shortestPath( const GraphLW< T >& graph, int start_node, int end_node ){
    auto dist_path = dijkstraLazy( graph, start_node, end_node );
    
    auto dist = dist_path.first;
    if( dist[end_node] == -1 ) return std::vector< int >();

    auto preceding = dist_path.second;

    std::vector< int > path = {end_node};
    int current = end_node;
    while( ( current = preceding[ current ] ) != -1 ){
        path.push_back( current );
    }
    std::reverse( path.begin(), path.end() );
    return path;
}



/*
std::pair< std::vector< int >, std::vector< int > > dijkstra_eager( const GraphLW& graph, int start_node, int end_node = -1 ){
    
    auto comp = []( const std::pair< int, int >& lhs, const std::pair< int, int >& rhs ){ return lhs.second > rhs.second; };
    std::priority_queue< std::pair< int, int >, std::vector< std::pair< int, int > >, decltype( comp ) > ipq( comp );    

    std::vector< bool > visited( graph.numNodes(), false );
    std::vector< int > distances( graph.numNodes(), -1 );
    std::vector< int > preceding( graph.numNodes(), -1 );

    distances[ start_node ] = 0;
    ipq.push( {0,0} );


    while( !ipq.empty() ){
        auto top = ipq.top();
        ipq.pop();
    
        if( visited[ top.first ] ) continue;
        visited[ top.first] = true;
        if( distances[ top.first ] != -1 && distances[ top.first ] < top.second ) continue;

        for( const auto& edge : graph.adList( top.first ) ){
            auto new_dist = distances[ top.first ] + edge.weight();
            if( distances[ edge.to() ] == -1 || new_dist < distances[ top.first ] ){
                distances[ edge.to() ] = new_dist;
            
                //update key-value pairs in PQ 
                //NOTE this is not a good implementation since we do linear search for the element
                //in a proper indexed priority queue this lookup would be logarithmic in time instead of linear
                auto it = std::find_if( ipq.begin(), ipq.end(), []( const auto& entry ){ entry.first == edge.to() } );
                if( it != ipq.cend() ){
                    it->second = new_dist;
                } else {
                    ipq.push( {edge.to(), new_dist } );
                }
                preceding[ edge.to() ] = top.first;
            }
        }
    }
    return { distances, preceding };
}
*/





#endif

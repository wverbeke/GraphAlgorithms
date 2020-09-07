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

                //the fact that an edge is used here matters in articulation point finding
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



//articulation point finding
//runs in O( V + E ) time
template< typename T > void depthFirstSearchAP( const GraphLW< T >& graph, int start_node, int parent, int& label_count, std::vector< bool >& visited, std::vector< int >& labels, std::vector< int >& lowlinks, std::vector< bool >& isAP, int& count_outgoing ){

    visited[ start_node ] = true;
    labels[ start_node ] = label_count++;
    lowlinks[ start_node ] = labels[ start_node ];

    for( const auto& edge : graph.adList( start_node ) ){
        if( edge.to() == parent ) continue;
        if( !visited[ edge.to() ] ){

            //root-node of this dfs
            if( parent == -1 ) ++count_outgoing;

            depthFirstSearchAP( graph, edge.to(), start_node, label_count, visited, labels, lowlinks, isAP, count_outgoing );
            if( lowlinks[ edge.to() ] < lowlinks[ start_node ] ){
                lowlinks[ start_node ] = lowlinks[ edge.to() ];
            }

            //detect presence of bridge 
            if( labels[ start_node ] < lowlinks[ edge.to() ] ){
                isAP[ start_node ] = true;
            }

            //can be aggregated with the above but for clarity they are separate 
            //the current label can only be equal to the low-link of the next node if it is the start of a new cycle, or it is the starting node inside a cycle
            //for the starting node we will reset the value depending on the number of outgoing edges outside of this function
            if( labels[ start_node ] == lowlinks[ edge.to() ] ){
                isAP[ start_node ] = true;
            }

        } else {

            //important to use the label of the node you go to here and not the lowlink
            //if there are two cycles with an articulation point connecting them, the use of the label here will ensure the elements in both cycles get a different low-link value
            if( labels[ edge.to() ] < lowlinks[ start_node ] ){
                lowlinks[ start_node ] = labels[ edge.to() ];
            }
        }


    }


}



template< typename T > std::vector< int > findArticulationPoints( const GraphLW< T >& graph ){

    std::vector< bool > visited( graph.numNodes(), false );
    std::vector< int > labels( graph.numNodes() );
    int label_count = 0;
    std::vector< int > lowlinks( graph.numNodes() );
    std::vector< bool > isAP( graph.numNodes(), false );

    for( const auto& entry : graph ){
        auto node = entry.first;
        if( visited[ node ] ) continue;
        int count_outgoing = 0;
        
        depthFirstSearchAP( graph, node, -1, label_count, visited, labels, lowlinks, isAP, count_outgoing );

        //note that checking for truth is not enough since the start node might have been incorrectly labeled as an AP if it was in a cycle
        isAP[ node ] = ( count_outgoing > 1 );
    }
    
    std::vector< int > APs; 
    for( size_t i = 0; i < isAP.size(); ++i ){
        if( isAP[i] ) APs.push_back( i );
    }
    return APs;
}


#endif

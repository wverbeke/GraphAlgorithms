

#include <iostream>

#include "Graph.h"
#include "FordFulkerson.h"
#include "EdmondsKarp.h"


Graph< float > test_graph(){

    Graph< float > ret;

    //source and drain ( easy to take them as the last 2 nodes in the graph )
    int s = 9, t = 10;

    ret.addEdge( s, 0, 10 );
    ret.addEdge( s, 1, 5 );
    ret.addEdge( s, 2, 10 );

    ret.addEdge( 0, 3, 10 );
    ret.addEdge( 1, 2, 10 );
    ret.addEdge( 2, 5, 15 );
    ret.addEdge( 3, 1, 20 );
    ret.addEdge( 3, 6, 15 );
    ret.addEdge( 4, 1, 15 );
    ret.addEdge( 4, 3, 3 );
    ret.addEdge( 5, 4, 4 );
    ret.addEdge( 5, 8, 10 );
    ret.addEdge( 6, 7, 10 );
    ret.addEdge( 7, 4, 10 );
    ret.addEdge( 7, 5, 7 );

    ret.addEdge( 6, t, 15 );
    ret.addEdge( 8, t, 10 );
    
    return ret;
}


int main(){

    Graph< float > graph = test_graph();

    auto max_flow = fordFulkerson_DFS( graph, 9, 10 );
    std::cout << "max flow with DFS augmentation = " << max_flow << std::endl;

    graph = test_graph();
    max_flow = fordFulkerson_edmondsKarp( graph, 9, 10 );
    std::cout << "max flow with Edmonds Karp augmentation = " << max_flow << std::endl;

    return 0;
}

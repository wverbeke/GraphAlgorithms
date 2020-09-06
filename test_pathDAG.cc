#include <iostream>
#include "Graph.h"
#include "shortestPathDAG.h"


GraphLW test_graph(){
    GraphLW ret;
    ret.addNode( 0, { {1,3}, {2,6} } );
    ret.addNode( 1, { {2,4}, {3,4}, {4,11} } );
    ret.addNode( 2, { {3,8}, {6,11} } );
    ret.addNode( 3, { {4,-4}, {5,5}, {6,2} } );
    ret.addNode( 4, { {7,9} } );
    ret.addNode( 5, { {7,1} } );
    ret.addNode( 6, { {7,2} } );
    ret.addNode( 7, {} );

    return ret;
}



int main(){

    auto graph = test_graph();
    auto spath = shortestPathDAG( graph, 0 );

    std::cout << spath[7] << std::endl;
    auto lpath = longestPathDAG( graph, 0 );
    std::cout << lpath[7] << std::endl;

    return 0;
}

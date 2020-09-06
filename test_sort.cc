
#include <iostream>
#include "Graph.h"
#include "topologicalSort.h"


GraphL test_graph(){
    GraphL ret;
    ret.addNode( 1, {4} );
    ret.addNode( 2, {4} );
    ret.addNode( 3, {1,2} );
    ret.addNode( 4, {7,8} );
    ret.addNode( 5, {1,4,6} );
    ret.addNode( 6, {10,11} );
    ret.addNode( 7, {9} );
    ret.addNode( 8, {9,10} );
    ret.addNode( 9, {12} );
    ret.addNode( 10, {12,13} );
    ret.addNode( 11, {10} );
    ret.addNode( 12, {} );
    ret.addNode( 13, {});
    return ret;
}


int main(){

    auto graph = test_graph();
    auto ordering = topologicalSort_optimized( graph );
    for( const auto& entry : ordering ){
        std::cout << entry << std::endl;
    }    
    return 0;
}

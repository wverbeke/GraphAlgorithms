

#include <vector> 
#include <iostream>
#include <utility>
#include <random>
#include <algorithm>

#include "Graph.h"
#include "BreadthFirstSearch.h"


std::vector< std::vector< char > > testGrid(){
    std::vector< std::vector< char > > grid;
    grid.push_back( { 'S', '.', '.', '#', '.', '.', '.' } );
    grid.push_back( { '.', '#', '.', '.', '.', '#', '.' } );
    grid.push_back( { '.', '#', '.', '.', '.', '.', '.' } );
    grid.push_back( { '.', '.', '#', '#', '.', '.', '.' } );
    grid.push_back( { '#', '.', '#', 'E', '.', '#', '.' } );
    return grid;
}


void printGrid( const std::vector< std::vector< char > >& grid ){
    for( const auto& row : grid ){
        for( const auto& column : row ){
            std::cout << column << " ";
        }
        std::cout << std::endl;
    }
}


GraphL gridToGraph( const std::vector< std::vector< char > >& grid ){
    GraphL graph;
    int num_columns = grid[0].size();
    for( size_t r = 0; r < grid.size(); ++r ){
        for( size_t c = 0; c < grid[r].size(); ++c ){
            int node = num_columns*r + c;
            std::list< int > neighbors;
            if( grid[ r ][ c ] != '#' ){
                int dr[4] = { -1, 1, 0, 0 };
                int dc[4] = { 0, 0, -1, 1 };
                for( int i = 0; i < 4; ++i ){
                    int rr = r + dr[i];
                    int cc = c + dc[i];
                    if( rr >= grid.size() ) continue;
                    if( cc >= grid[r].size() ) continue;
                    int neighbor = num_columns*rr + cc;
                    neighbors.push_back( neighbor );
                }
            }
            graph.addNode( node, neighbors );
        }
    }
    return graph;
}


std::pair< std::pair< int, int>, std::pair< int, int > > begin_end( const std::vector< std::vector< char > >& grid ){

    std::pair< int, int > begin = {-1, -1};
    std::pair< int, int > end = {-1, -1};
    for( size_t r = 0; r < grid.size(); ++r ){
        for( size_t c = 0; c < grid[r].size(); ++c ){
            if( grid[ r ][ c ] == 'S' ){
                begin = { r, c };
            } else if( grid[ r ][ c ] == 'E' ){
                end = { r, c };
            }
        }
    }
    return { begin, end };
}



std::pair< int, int > begin_end_grid( const std::vector< std::vector< char > >& grid ){
    int num_columns = grid[0].size();

    auto begin_end_index = begin_end( grid );
    int begin = begin_end_index.first.first * num_columns + begin_end_index.first.second;
    int end = begin_end_index.second.first * num_columns + begin_end_index.second.second;
    return { begin, end };
    /*
    std::pair< int, int > ret = {-1, -1};
    for( size_t r = 0; r < grid.size(); ++r ){
        for( size_t c = 0; c < grid[r].size(); ++c ){
            if( grid[ r ][ c ] == 'S' ){
                ret.first = num_columns*r + c;
            } else if( grid[ r ][ c ] == 'E' ){
                ret.second = num_columns*r + c;
            }
        }
    }
    return ret;
    */
}


std::vector< std::pair< int, int > > pathToGridIndices( const std::vector< int >& path, int num_columns ){
    std::vector< std::pair< int, int > > ret;
    for( const auto& entry : path ){
        int row = entry/num_columns;
        int column = entry%num_columns;
        ret.push_back( {row, column } );
    }
    return ret;
}


std::vector< std::vector< char > > randomGrid( size_t num_rows, size_t num_columns ){

	//algorithm to generate random numbers 
    static std::ranlux48 random_engine;
	static std::uniform_real_distribution<double> prob_obstacle(0, 1);

	std::vector< std::vector< char > > grid( num_rows, std::vector< char >( num_columns ) );

	//generate random obstacles
	for( size_t r = 0; r < num_rows; ++r ){
		for( size_t c = 0; c < num_columns; ++c ){
			double random = prob_obstacle( random_engine );
			if( random > 0.75 ){
				grid[ r ][ c ] = '#';
			} else {
				grid[ r ][ c ] = '.';
			}
		}
	}

	//generate start and end position
	std::uniform_int_distribution< int > randomRows( 0, num_rows - 1);
	std::uniform_int_distribution< int > randomColumns( 0, num_columns - 1);
	grid[ randomRows( random_engine ) ][ randomColumns( random_engine ) ] = 'S';
	grid[ randomRows( random_engine ) ][ randomColumns( random_engine ) ] = 'E';

	return grid;
}




//directly run a breadth-first search on the grid without explicitly converting it to a Graph
std::vector< std::pair< int, int > > pathOnGrid( const std::vector< std::vector< char > >& grid, int start_x, int start_y, int end_x, int end_y ){

    std::vector< std::vector< bool > > visited( grid.size(), std::vector< bool >( grid[0].size(), false ) );
    std::queue<int> x_queue;
    x_queue.push( start_x );
    std::queue<int> y_queue;
    y_queue.push( start_y );
    
    visited[ start_x ][ start_y ] = true;

    int dr[4] = { 0, 0, -1, 1 };
    int dc[4] = { -1, 1, 0, 0 };

    std::vector< std::vector< int > > prev_x( grid.size(), std::vector< int >( grid[0].size(), -1 ) );
    std::vector< std::vector< int > > prev_y( grid.size(), std::vector< int >( grid[0].size(), -1 ) );

    std::cout << "start_x = " << start_x << "\tstart_y = " << start_y << std::endl;
    std::cout << "end_x = " << end_x << "\tend_y = " << end_y << std::endl;

    int size_current_level = x_queue.size();
    int size_next_level = 0;
    int steps = 0;

    while( !x_queue.empty() ){
        auto current_x = x_queue.front();
        x_queue.pop();
        auto current_y = y_queue.front();
        y_queue.pop();
        if( current_x == end_x && current_y == end_y ){
            break;
        }

        --size_current_level;
        for( int i = 0; i < 4; ++i ){
            int x = current_x + dr[i];
            int y = current_y + dc[i];
            if( x >= grid.size() || x < 0 ) continue;
            if( y >= grid[x].size() || y < 0 ) continue;
            if( visited[ x ][ y ] ) continue;
            if( grid[x][y] == '#' ) continue;
            visited[ x ][ y ] = true;
            x_queue.push( x );
            y_queue.push( y );
            prev_x[x][y] = current_x;
            prev_y[x][y] = current_y;

            //BREAKS ONLY FOR LOOP
            //if( x == end_x && y == end_y ){
            //    break;
            //}
            ++size_next_level;
        }
        if( size_current_level == 0 ){
            std::cout << "size_next_level = " << size_next_level << std::endl;
            size_current_level = size_next_level;
            size_next_level = 0;
            ++steps;
        }
        
    }

    std::cout << "needed " << steps << " steps " << std::endl;

    //std::cout << prev_x[ start_x ][ start_y ] << "\t" << prev_y[ start_x ][ start_y ] << std::endl;
    //std::cout << prev_x[ end_x ][ end_y ] << "\t" << prev_y[ end_x ][ end_y ] << std::endl;
    
    //reconstruct path
    std::vector< std::pair< int, int > > path;
    int current_x = end_x;
    int current_y = end_y;
    path.push_back( { end_x, end_y } );
    //while( current_x != -1 && current_y != -1 ){
    while( true ){
        int x_prev = prev_x[ current_x ][ current_y ];
        int y_prev = prev_y[ current_x ][ current_y ];
        current_x = x_prev;
        current_y = y_prev;
        if( current_x == -1 || current_y == -1 ) break;
        //std::cout << "current_x = " << current_x << "\tcurrent_y = " << current_y << std::endl;
        path.push_back( { current_x, current_y } );
    }
    std::reverse( path.begin(), path.end() );


    if( path.front().first == start_x && path.front().second == start_y ){
        return path;
    } else {
        return std::vector< std::pair< int, int > >();
    }
    //return std::vector< std::pair< int, int > >();
}



void test_random_graph(){
    
    //auto grid = testGrid();

	auto grid = randomGrid( 50, 50 );
    auto graph = gridToGraph( grid );
    auto start_end = begin_end_grid( grid );
    auto path = shortestPath( graph, start_end.first, start_end.second );

    auto pathIndices = pathToGridIndices( path, grid[0].size() );
	//std::cout << "path.size() = " << path.size() << std::endl;
    for( auto& entry : pathIndices ){
		if( grid[entry.first][entry.second] != 'S' && grid[entry.first][entry.second] != 'E' ){
        	grid[entry.first][entry.second] = 'P';
		}
    }
	printGrid( grid );
}


void test_random_direct(){
    
    auto grid = testGrid();

	//auto grid = randomGrid( 50, 50 );
    auto start_end = begin_end( grid );

    std::cout << "start path finding" << std::endl;
    auto path = pathOnGrid( grid, start_end.first.first, start_end.first.second, start_end.second.first, start_end.second.second );
    std::cout << "path size = " << path.size() - 1 << std::endl;
    std::cout << "end path finding" << std::endl;

    for( auto& entry : path ){
		if( grid[entry.first][entry.second] != 'S' && grid[entry.first][entry.second] != 'E' ){
        	grid[entry.first][entry.second] = 'P';
		}
    }
	printGrid( grid );
}


int main(){
	test_random_direct();
	//for( int i = 0; i < 10; ++i ){
	//	test_random_direct();
	//	for( int i = 0; i < 10; ++i ){
	//		std::cout << std::endl;
	//	}
	//}
	return 0;
}

#ifndef Graph_H
#define Graph_H


#include <list>
#include <map>
#include <limits>
#include <vector>


//adjecently list implementation of unweighted graph

class GraphL{
    public:
        using iterator = std::map< int, std::list< int > >::iterator;
        using const_iterator = std::map< int, std::list< int > >::const_iterator;


        GraphL() = default; 
        void addNode( int i , const std::list< int >& l ){ _adjecency_lists[ i ] = l; }
        const std::list< int >& adlist( int i ) const{ return _adjecency_lists.at( i ); }

        size_t numNodes() const{ return _adjecency_lists.size(); }
        size_t numEdges() const{
            long sum = 0;
            for( const auto& entry : _adjecency_lists ){
                sum += entry.second.size();
            }
        }

        iterator begin(){ return _adjecency_lists.begin(); }
        const_iterator begin() const{ return _adjecency_lists.cbegin(); }
        const_iterator cbegin() const{ return _adjecency_lists.cbegin(); }

        iterator end(){ return _adjecency_lists.end(); }
        const_iterator end() const{ return _adjecency_lists.cend(); }
        const_iterator cend() const{ return _adjecency_lists.cend(); }
        

    private:
        std::map< int, std::list< int > > _adjecency_lists;
};



//adjecency list implementation of weighted graph

template< typename T > class Edge{
    public:
        Edge( int t, T w ) : _to( t ), _weight( w ) {}
        Edge( std::initializer_list< int > init ) : _to( *init.begin() ), _weight( *( init.begin() + 1 ) ) {}

        int to() const{ return _to; }
        T weight() const{ return _weight; }

        void setWeight( T weight ){ _weight = weight; }

    private:
        int _to;
        int _weight;
};


template< typename T > class GraphLW{

    public:
        using iterator = typename std::map< int, std::list< Edge< T > > >::iterator;
        using const_iterator = typename std::map< int, std::list< Edge< T > > >::const_iterator;

        GraphLW() = default;
        void addNode( int i, const std::list< Edge< T > >& l ){ _adjecency_lists[i] = l; }
        const std::list< Edge< T > >& adList( int i ) const{ return _adjecency_lists.at( i ); }

        size_t numNodes() const{ return _adjecency_lists.size(); }
        
        iterator begin(){ return _adjecency_lists.begin(); }
        const_iterator begin() const{ return _adjecency_lists.cbegin(); }
        const_iterator cbegin() const{ return _adjecency_lists.cbegin(); }

        iterator end(){ return _adjecency_lists.end(); }
        const_iterator end() const{ return _adjecency_lists.cend(); }
        const_iterator cend() const{ return _adjecency_lists.cend(); }

        //for finding longest path when topological order exists 
        void invertWeights(){
            for( auto& entry : _adjecency_lists ){
                for( auto& edge : entry.second ){
                    edge.setWeight( edge.weight() * -1 );
                }
            }
        }

    private:
        std::map< int, std::list< Edge< T > > > _adjecency_lists;
};


//adjecency matrix implementation of graph
template< typename T > class GraphMW{

    public:
        using size_type = typename std::vector< std::vector< T > >::size_type;
        using iterator = typename std::vector< std::vector< T > >::iterator;
        using const_iterator = typename std::vector< std::vector< T > >::const_iterator;

        GraphMW( size_type s ) : _weights( s, std::vector< T >( s , std::numeric_limits< T >::infinity() ) ){

            //set diagonals to 0
            for( int i = 0; i < s; ++i ){
                _weights[i][i] = 0;
            }
        }
        GraphMW( const std::vector< std::vector< T > >& weights ) : _weights( weights ) {}

        const std::vector< T >& operator[]( size_type i ) const{ return _weights[i]; }
        std::vector< T >& operator[]( size_type i ){ return _weights[i]; }
        const std::vector< std::vector< T > >& weights() const{ return _weights; }

        size_type numNodes() const{ return _weights.size(); }

    private:
        std::vector< std::vector< T > > _weights;
};


#endif

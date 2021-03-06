#ifndef Graph_H
#define Graph_H


#include <list>
#include <map>
#include <limits>
#include <vector>
#include <iostream>


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
        Edge( int t ) : _to( t ) {}
        Edge( int t, T w ) : _to( t ), _weight( w ) {}
        Edge( int f, int t, T w ) : _from( f ), _to( t ), _weight( w ) {}

        //this constructor is actually not OK since different types are used...
        Edge( std::initializer_list< int > init ) : _to( *init.begin() ), _weight( *( init.begin() + 1 ) ) {}

        int to() const{ return _to; }
        int from() const{ return _from; }
        T weight() const{ return _weight; }

        void setWeight( T weight ){ _weight = weight; }

    private:
        int _to;
        T _weight = 1;
        int _from = -1;
};

template< typename T > std::ostream& operator<<( std::ostream& os, const Edge< T >& edge ){
    os << "Edge";
    if( edge.from() != -1 ){
        os << " from " << edge.from();
    }
    os << " to " << edge.to() << " with weight " << edge.weight();
}


template< typename T > bool operator<( const Edge< T >& lhs, const Edge< T >& rhs ){
    return lhs.weight() < rhs.weight();
}


template< typename T > class GraphLW{

    public:
        using iterator = typename std::map< int, std::vector< Edge< T > > >::iterator;
        using const_iterator = typename std::map< int, std::vector< Edge< T > > >::const_iterator;
        using size_type = typename std::map< int, std::vector< Edge< T > > >::size_type;

        GraphLW() = default;
        void addNode( int i, const std::vector< Edge< T > >& l ){ _adjecency_lists[i] = l; }
        const std::vector< Edge< T > >& adList( int i ) const{ return _adjecency_lists.at( i ); }

        size_type numNodes() const{ return _adjecency_lists.size(); }
        size_type numEdges() const{
            size_type count = 0;
            for( const auto& entry : _adjecency_lists ){
                count += entry.second.size();
            }
            return count;
        }
        
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
        std::map< int, std::vector< Edge< T > > > _adjecency_lists;
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

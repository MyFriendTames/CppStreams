#ifndef MYFRIENDTAMES_CPP_STREAM_ITERATOR_HPP
#define MYFRIENDTAMES_CPP_STREAM_ITERATOR_HPP

#include <iterator>

namespace strm{
  template < typename T >
  class Iterator : public std::iterator< std::bidirectional_iterator_tag, T >{
    template < typename U > friend class Stream;
    
    private: strm::Node< T >* m_previousNode;
    private: strm::Node< T >* m_node;
    private: strm::Node< T >* m_nextNode;

    private: Iterator( strm::Node< T >* p_previousNode, strm::Node< T >* p_node, strm::Node< T >* p_nextNode );
    public: Iterator( const strm::Iterator< T >& other );
    
    public: Iterator& operator ++ ();
    public: Iterator operator ++ ( int );
    public: Iterator& operator -- ();
    public: Iterator operator -- ( int );

    public: bool operator == ( const strm::Iterator< T >& other );
    public: bool operator != ( const strm::Iterator< T >& other );
    
    public: operator bool ();

    public: T& operator * ();
    public: T& operator -> ();
  };
}

#include"CppStreamIterator.def.hpp"

#endif
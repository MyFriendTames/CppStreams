#ifndef MYFRIENDTAMES_CPP_STREAM_NODE_HPP
#define MYFRIENDTAMES_CPP_STREAM_NODE_HPP

namespace strm{
  template < typename T > class Stream;
  template < typename T > class Iterator;

  template < typename T >
  class Node{
    template < typename U > friend class Stream;
    template < typename U > friend class Iterator;

    private: T m_element;
    private: strm::Node< T > *m_previousNode;
    private: strm::Node< T > *m_nextNode;

    private: Node( const T& p_element, strm::Node< T >* p_previousNode, strm::Node< T >* p_nextNode );
    public: virtual ~Node();
  };
}

#include "CppStreamNode.def.hpp"

#endif
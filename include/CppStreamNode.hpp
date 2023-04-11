#ifndef MYFRIENDTAMES_CPP_STREAM_NODE_HPP
#define MYFRIENDTAMES_CPP_STREAM_NODE_HPP

namespace strm{
  template < typename T > class Stream;

  template < typename T >
  class StreamNode{
    template < typename U > friend class Stream;

    private: T m_element;
    private: strm::StreamNode< T > *m_previousNode;
    private: strm::StreamNode< T > *m_nextNode;

    private: StreamNode( const T& p_element, strm::StreamNode< T >* p_previousNode, strm::StreamNode< T >* p_nextNode );
    public: virtual ~StreamNode();
  };
}

#include "CppStreamNode.def.hpp"

#endif
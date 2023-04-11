template < typename T >
strm::Stream< T >::Stream() :
  m_refCount( new size_t( 1 ) ),
  m_firstNode( nullptr ),
  m_lastNode( nullptr ),
  m_size( 0 ){
}

template < typename T >
strm::Stream< T >::Stream( const strm::Stream< T >& p_other ) :
  m_refCount( ++*p_other.m_refCount ),
  m_firstNode( p_other.m_firstNode ),
  m_lastNode( p_other.m_lastNode ),
  m_size( p_other.m_size ){
}

template < typename T >
strm::Stream< T >::Stream( strm::Stream< T >&& p_other ) :
  m_refCount( p_other.m_refCount ),
  m_firstNode( p_other.m_firstNode ),
  m_lastNode( p_other.m_lastNode ),
  m_size( p_other.m_size ){
  p_other.m_refCount = nullptr;
  p_other.m_firstNode = nullptr;
  p_other.m_lastNode = nullptr;
  p_other.m_size = 0;
}

template < typename T >
strm::Stream< T >::Stream( const std::initializer_list< T >& data ) : Stream(){
  strm::StreamNode< T > *node;
  for ( auto& v : data ){
    ( !m_firstNode ? m_firstNode : node ) = ( !m_firstNode ? node : node->m_nextNode ) = new strm::StreamNode< T >( v, node, nullptr );
    ++m_size;
  }
  m_lastNode = node;
}

template < typename T >
strm::Stream< T >::~Stream(){
  if ( m_refCount ){
    if ( !--*m_refCount ){
      delete m_refCount;
      delete m_firstNode;
    }
  }
  m_refCount = nullptr;
  m_firstNode = nullptr;
  m_lastNode = nullptr;
  m_size = 0;
}

template < typename T >
const size_t& strm::Stream< T >::count() const {
  return m_size;
}

template < typename T >
strm::Stream< T >& strm::Stream< T >::forEach( const std::function< void( const T& ) >& callback ){
  for ( auto node( m_firstNode ); node; node = node->m_nextNode ) callback( node->m_element );
  return *this;
}

template < typename T >
strm::Stream< T >& strm::Stream< T >::forEach( const std::function< void( const T&, const size_t& ) >& callback ){
  size_t i( 0 );
  for ( auto node( m_firstNode ); node; node = node->m_nextNode ) callback( node->m_element, i++ );
  return *this;
}

template < typename T >
strm::Stream< T > strm::Stream< T >::map( const std::function< T( const T& ) >& callback ){
  return map< T >( callback );
}

template < typename T >
template < typename U >
strm::Stream< U > strm::Stream< T >::map( const std::function< U( const T& ) >& callback ){
  strm::Stream< U > stream;
  strm::StreamNode< U >* newNode( nullptr );
  for ( auto node( m_firstNode ); node; node = node->m_nextNode ){
    ( !stream.m_firstNode ? stream.m_firstNode : newNode ) = ( !stream.m_firstNode ? newNode : newNode->m_nextNode ) = new strm::StreamNode< U >( callback( node->m_element), newNode, nullptr );
    ++stream.m_size;
  }
  stream.m_lastNode = newNode;
  return stream;
}

template < typename T >
T strm::Stream< T >::reduce( const std::function< T( const T&, const T& ) >& callback, const T& ini ){
  return reduce< T >( callback, ini );
}

template < typename T >
template < typename U >
U strm::Stream< T >::reduce( const std::function< U( const U&, const T& ) >& callback, const U& ini ){
  U result( ini );
  for ( auto node( m_firstNode ); node; node = node->m_nextNode ){
    result = callback( result, node->m_element );
  }
  return result;
}
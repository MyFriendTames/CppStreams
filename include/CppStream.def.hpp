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
  strm::Node< T > *node;
  for ( auto& v : data ){
    ( !m_firstNode ? m_firstNode : node ) = ( !m_firstNode ? node : node->m_nextNode ) = new strm::Node< T >( v, node, nullptr );
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
strm::Iterator< T > strm::Stream< T >::begin() const{
  return strm::Iterator< T >( nullptr, m_firstNode, m_firstNode ? m_firstNode->m_nextNode : nullptr );
}

template < typename T >
strm::Iterator< T > strm::Stream< T >::end() const{
  return strm::Iterator< T >( m_lastNode, nullptr, nullptr );
}

template < typename T >
bool strm::Stream< T >::allMatch( const std::function< bool( const T& ) >& predicate ) const {
  for ( auto& element : *this ){
    if ( !predicate( element ) ){
      return false;
    }
  }
  return m_size > 0;
}

template < typename T >
bool strm::Stream< T >::anyMatch( const std::function< bool( const T& ) >& predicate ) const {
  for ( auto& element : *this ){
    if ( predicate( element ) ){
      return true;
    }
  }
  return false;
}

template < typename T >
size_t strm::Stream< T >::count() const {
  return m_size;
}

template < typename T >
const strm::Stream< T >& strm::Stream< T >::forEach( const std::function< void( const T& ) >& callback ) const {
  for ( auto it( begin() ); it; ++it ) callback( *it );
  return *this;
}

template < typename T >
const strm::Stream< T >& strm::Stream< T >::forEach( const std::function< void( const T&, const size_t& ) >& callback ) const {
  size_t i( 0 );
  for ( auto it( begin() ); it; ++it ) callback( *it, i++ );
  return *this;
}

template < typename T >
strm::Stream< T > strm::Stream< T >::map( const std::function< T( const T& ) >& callback ) const {
  return map< T >( callback );
}

template < typename T >
template < typename U >
strm::Stream< U > strm::Stream< T >::map( const std::function< U( const T& ) >& callback ) const {
  strm::Stream< U > stream;
  strm::Node< U >* newNode( nullptr );
  for ( auto node( m_firstNode ); node; node = node->m_nextNode ){
    ( !stream.m_firstNode ? stream.m_firstNode : newNode ) = ( !stream.m_firstNode ? newNode : newNode->m_nextNode ) = new strm::Node< U >( callback( node->m_element), newNode, nullptr );
    ++stream.m_size;
  }
  stream.m_lastNode = newNode;
  return stream;
}

template < typename T >
T strm::Stream< T >::reduce( const std::function< T( const T&, const T& ) >& callback, const T& ini ) const {
  return reduce< T >( callback, ini );
}

template < typename T >
template < typename U >
U strm::Stream< T >::reduce( const std::function< U( const U&, const T& ) >& callback, const U& ini ) const {
  U result( ini );
  for ( auto node( m_firstNode ); node; node = node->m_nextNode ){
    result = callback( result, node->m_element );
  }
  return result;
}
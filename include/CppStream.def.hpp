template < typename T >
strm::Stream< T >::Stream() :
  m_refCount( new size_t( 1 ) ),
  m_firstNode( nullptr ),
  m_lastNode( nullptr ),
  m_size( 0 ){
}

template < typename T >
strm::Stream< T >::Stream( const strm::Stream< T >& p_other ) :
  m_refCount( &( ++*p_other.m_refCount ) ),
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
  }
  m_lastNode = node;
  m_size = data.size();
}

template < typename T >
template < typename InputIterator >
strm::Stream< T >::Stream( const InputIterator& first, const InputIterator& last ) : Stream(){
  for ( auto it( first ); it != last; ++it ){
    m_lastNode = ( !m_firstNode ? m_lastNode : m_lastNode->m_nextNode ) = new strm::Node< T >( *it, m_lastNode, nullptr );
    if ( !m_firstNode ) m_firstNode = m_lastNode;
    ++m_size;
  }
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
}

template < typename T >
strm::Node< T > * const & strm::Stream< T >::add( const T& element ){
  m_lastNode = ( !m_firstNode ? m_lastNode : m_lastNode->m_nextNode ) = new strm::Node< T >( element, m_lastNode, nullptr );
  if ( !m_firstNode ) m_firstNode = m_lastNode;
  ++m_size;
  return m_lastNode;
}

template < typename T >
strm::Iterator< T > strm::Stream< T >::begin() const{
  return strm::Iterator< T >( nullptr, m_firstNode, m_firstNode ? m_firstNode->m_nextNode : nullptr );
}

template < typename T >
strm::Iterator< T > strm::Stream< T >::end() const {
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
strm::Stream< T > strm::Stream< T >::concat( const strm::Stream< T >& other ) const {
  if ( other.m_size ){
    if ( m_size ){
      strm::Stream< T > stream;
      for ( auto& v : *this ){
        stream.m_lastNode = ( !stream.m_firstNode ? stream.m_lastNode : stream.m_lastNode->m_nextNode ) = new strm::Node< T >( v, stream.m_lastNode, nullptr );
        if ( !stream.m_firstNode ) stream.m_firstNode = stream.m_lastNode;
      }
      for ( auto& v : other ){
        stream.m_lastNode = stream.m_lastNode->m_nextNode = new strm::Node< T >( v, stream.m_lastNode, nullptr );
      }
      stream.m_size = m_size + other.m_size;
      return stream;
    }
    return other;
  }
  return *this;
}

template < typename T >
strm::Stream< T > strm::Stream< T >::concat( strm::Stream< T >&& other ) const {
  if ( other.m_size ){
    if ( m_size ){
      strm::Stream< T > stream;
      for ( auto& v : *this ){
        stream.m_lastNode = ( !stream.m_firstNode ? stream.m_lastNode : stream.m_lastNode->m_nextNode ) = new strm::Node< T >( v, stream.m_lastNode, nullptr );
        if ( !stream.m_firstNode ) stream.m_firstNode = stream.m_lastNode;
      }
      for ( auto& v : other ){
        stream.m_lastNode = stream.m_lastNode->m_nextNode = new strm::Node< T >( v, stream.m_lastNode, nullptr );
      }
      stream.m_size = m_size + other.m_size;
      return stream;
    }
    return std::move( other );
  }
  return *this;
}

template < typename T >
strm::Stream< T > strm::Stream< T >::concat( const std::initializer_list< T >& data ) const {
  if ( data.size() ){
    if ( m_size ){
      strm::Stream< T > stream;
      for ( auto& v : *this ){
        stream.m_lastNode = ( !stream.m_firstNode ? stream.m_lastNode : stream.m_lastNode->m_nextNode ) = new strm::Node< T >( v, stream.m_lastNode, nullptr );
        if ( !stream.m_firstNode ) stream.m_firstNode = stream.m_lastNode;
      }
      for ( auto& v : data ){
        stream.m_lastNode = stream.m_lastNode->m_nextNode = new strm::Node< T >( v, stream.m_lastNode, nullptr );
      }
      stream.m_size = m_size + data.size();
      return stream;
    }
    return data;
  }
  return *this;
}

template < typename T >
template < typename InputIterator >
strm::Stream< T > strm::Stream< T >::concat( const InputIterator& first, const InputIterator& last ) const {
  if ( first != last ){
    if ( m_size ){
      strm::Stream< T > stream;
      for ( auto& v : *this ){
        stream.m_lastNode = ( !stream.m_firstNode ? stream.m_lastNode : stream.m_lastNode->m_nextNode ) = new strm::Node< T >( v, stream.m_lastNode, nullptr );
        if ( !stream.m_firstNode ) stream.m_firstNode = stream.m_lastNode;
      }
      stream.m_size = m_size;
      for ( auto it( first ); it != last; ++it ){
        stream.m_lastNode = stream.m_lastNode->m_nextNode = new strm::Node< T >( *it, stream.m_lastNode, nullptr );
        ++stream.m_size;
      }
      return stream;
    }
    return strm::Stream< T >( first, last );
  }
  return *this;
}

template < typename T >
const size_t& strm::Stream< T >::count() const {
  return m_size;
}

template < typename T >
strm::Stream< T > strm::Stream< T >::distinct( const std::function< bool( const T&, const T& ) >& predicate ) const {
  if ( m_size ){
    strm::Stream< T > stream;
    for ( auto& v : *this ){
      if ( !stream.anyMatch( [ &v, &predicate ] ( auto a ) { return predicate( v, a ); } ) ){
        stream.m_lastNode = ( !stream.m_firstNode ? stream.m_lastNode : stream.m_lastNode->m_nextNode ) = new strm::Node< T >( v, stream.m_lastNode, nullptr );
        if ( !stream.m_firstNode ) stream.m_firstNode = stream.m_lastNode;
      }
    }
    return stream;
  }
  return *this;
}

template < typename T >
strm::Stream< T > strm::Stream< T >::filter( const std::function< bool( const T& ) >& predicate ) const {
  strm::Stream< T > stream;
  for ( auto& v : *this ){
    if ( predicate( v ) ) stream.add( v );
  }
  return stream;
}

template < typename T >
std::optional< T > strm::Stream< T >::findFirst() const {
  if ( m_firstNode ) return m_firstNode->m_element;
  return {};
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
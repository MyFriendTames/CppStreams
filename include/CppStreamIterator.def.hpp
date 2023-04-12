template < typename T >
strm::Iterator< T >::Iterator( strm::Node< T >* p_previousNode, strm::Node< T >* p_node, strm::Node< T >* p_nextNode ) :
  m_previousNode( p_previousNode ),
  m_node( p_node ),
  m_nextNode( p_nextNode ){
}

template < typename T >
strm::Iterator< T >::Iterator( const strm::Iterator< T >& other ) :
  m_previousNode( other.m_previousNode ),
  m_node( other.m_node ),
  m_nextNode( other.m_nextNode ){
}

template < typename T >
strm::Iterator< T >& strm::Iterator< T >::operator ++ (){
  if ( m_node || m_nextNode ){
    m_previousNode = m_node;
    m_node = m_nextNode;
    m_nextNode = m_nextNode ? m_nextNode->m_nextNode : nullptr;
  }
  return *this;
}

template < typename T >
strm::Iterator< T > strm::Iterator< T >::operator ++ ( int ){
  if ( m_node || m_nextNode ){
    return strm::Iterator< T >(
      m_node,
      m_nextNode,
      m_nextNode ? m_nextNode->m_nextNode : nullptr
    );
  }
  return *this;
}

template < typename T >
strm::Iterator< T >& strm::Iterator< T >::operator -- (){
  if ( m_node || m_previousNode ){
    m_nextNode = m_node;
    m_node = m_previousNode;
    m_previousNode = m_previousNode ? m_previousNode->m_previousNode : nullptr;
  }
  return *this;
}

template < typename T >
strm::Iterator< T > strm::Iterator< T >::operator -- ( int ){
  if ( m_node || m_previousNode ){
    return strm::Iterator< T >(
      m_previousNode ? m_previousNode->m_previousNode : nullptr,
      m_previousNode,
      m_node
    );
  }
  return *this;
}

template < typename T >
bool strm::Iterator< T >::operator == ( const strm::Iterator< T >& other ){
  return m_node == other.m_node;
}

template < typename T >
bool strm::Iterator< T >::operator != ( const strm::Iterator< T >& other ){
  return m_node != other.m_node;
}

template < typename T >
strm::Iterator< T >::operator bool (){
  return !!m_node;
}

template < typename T >
T& strm::Iterator< T >::operator * (){
  return m_node->m_element;
}

template < typename T >
T& strm::Iterator< T >::operator -> (){
  return m_node->m_element;
}
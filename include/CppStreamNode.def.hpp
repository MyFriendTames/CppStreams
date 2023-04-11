template < typename T >
strm::StreamNode< T >::StreamNode( const T& p_element, strm::StreamNode< T >* p_previousNode, strm::StreamNode< T >* p_nextNode ) :
  m_element( p_element ),
  m_previousNode( p_previousNode ),
  m_nextNode( p_nextNode ){
}

template < typename T >
strm::StreamNode< T >::~StreamNode(){
  delete m_nextNode;
  m_previousNode = nullptr;
  m_nextNode = nullptr;
}
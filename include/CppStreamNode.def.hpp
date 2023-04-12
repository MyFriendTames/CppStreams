template < typename T >
strm::Node< T >::Node( const T& p_element, strm::Node< T >* p_previousNode, strm::Node< T >* p_nextNode ) :
  m_element( p_element ),
  m_previousNode( p_previousNode ),
  m_nextNode( p_nextNode ){
}

template < typename T >
strm::Node< T >::~Node(){
  delete m_nextNode;
  m_previousNode = nullptr;
  m_nextNode = nullptr;
}
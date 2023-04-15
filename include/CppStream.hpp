#ifndef MYFRIENDTAMES_CPP_STREAM_HPP
#define MYFRIENDTAMES_CPP_STREAM_HPP

#include <cstddef>
#include <initializer_list>
#include <functional>
#include <utility>
#include <optional>

#include "CppStreamNode.hpp"
#include "CppStreamIterator.hpp"

/// @brief CppStreams library namespace
namespace strm{
  /// @brief Main CppStreams class
  template < typename T >
  class Stream{
    template < typename U > friend class Stream;

    private: size_t* m_refCount;
    private: strm::Node< T >* m_firstNode;
    private: strm::Node< T >* m_lastNode;
    private: size_t m_size;

    /// @brief Default Contructor: creates an empty Stream
    public: Stream();
    /// @brief Copy Constructor: creates a new reference to an already existing Stream
    public: Stream( const strm::Stream< T >& p_other );
    /// @brief Move Constructor: moves all the pointers to a new Stream
    public: Stream( strm::Stream< T >&& p_other );
    /// @brief Initializer constructor: creates a new Stream filled with the data passed by parameter
    public: Stream( const std::initializer_list< T >& data );
    /// @brief Range constructor: creates new Stream using the data from the iterators range [first, last)
    public: template < typename InputIterator > Stream( const InputIterator& first, const InputIterator& last );
    
    /// @brief Frees all the allocated data
    public: virtual ~Stream();

    /// @brief Private method to add a new element to the Stream
    /// @param element The element to be added
    /// @return The newly created node
    public: strm::Node< T > * const & add( const T& element );

    /// @brief Returns an iterator pointing to the first element in the Stream
    /// @return Iterator to the first element
    public: strm::Iterator< T > begin() const;
    /// @brief Returns an iterator pointing to the past-the-end element in the Stream
    /// @return Iterator to the past-the-end element
    public: strm::Iterator< T > end() const;

    /// @brief Returns whether all elements of the Stream match the predicate
    /// @return true if all the elements satify the predicate
    public: bool allMatch( const std::function< bool( const T& ) >& predicate ) const;
    /// @brief Returns whether any element of the Stream match the predicate
    /// @return true if any element satify the predicate
    public: bool anyMatch( const std::function< bool( const T& ) >& predicate ) const;

    public: strm::Stream< T > concat( const strm::Stream< T >& other ) const;
    public: strm::Stream< T > concat( strm::Stream< T >&& other ) const;
    public: strm::Stream< T > concat( const std::initializer_list< T >& data ) const;
    public: template < typename InputIterator > Stream< T > concat( const InputIterator& first, const InputIterator& last ) const;

    public: const size_t& count() const;

    public: strm::Stream< T > distinct( const std::function< bool( const T&, const T& ) >& predicate ) const;

    public: strm::Stream< T > filter( const std::function< bool( const T& ) >& predicate ) const;

    public: std::optional< T > findFirst() const;

    public: const strm::Stream< T >& forEach( const std::function< void( const T& ) >& callback ) const;
    public: const strm::Stream< T >& forEach( const std::function< void( const T&, const size_t& ) >& callback ) const;

    public: strm::Stream< T > map( const std::function< T( const T& ) >& callback ) const;
    public: template < typename U > strm::Stream< U > map( const std::function< U( const T& ) >& callback ) const;

    public: T reduce( const std::function< T( const T&, const T& ) >& callback, const T& ini = T() ) const;
    public: template < typename U > U reduce( const std::function< U( const U&, const T& ) >& callback, const U& ini = U() ) const;
  };

  #include "CppStream.def.hpp"
}

#endif
#ifndef MYFRIENDTAMES_CPP_STREAM_HPP
#define MYFRIENDTAMES_CPP_STREAM_HPP

#include <cstddef>
#include <initializer_list>
#include <functional>

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
    private: Stream();
    /// @brief Copy Constructor: creates a new reference to an existing stream
    public: Stream( const strm::Stream< T >& p_other );
    /// @brief Move Constructor: moves all the pointers to a new Stream
    public: Stream( strm::Stream< T >&& p_other );
    /// @brief Initializer constructor: creates a new Stream filled with the parameters data
    public: Stream( const std::initializer_list< T >& data );
    
    /// @brief Frees all the allocated data
    public: virtual ~Stream();

    /// @brief Returns an iterator pointing to the first element in the stream
    public: strm::Iterator< T > begin() const;
    /// @brief Returns an iterator pointing to the past-the-end element in the stream
    public: strm::Iterator< T > end() const;

    public: bool allMatch( const std::function< bool( const T& ) >& predicate ) const;
    public: bool anyMatch( const std::function< bool( const T& ) >& predicate ) const;

    public: size_t count() const;

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
# Cpp Streams

This is a simple lightweight library inspired by the java.util.stream library available since Java 8.
It provides functional style programing for processing lists of elements.

```
At least C++14 is required for this library to work.
```

*CppStreams library is distributed under the ISC open source licence*

## Documentation

***This documentation and library are still under development***

*First note that everything in this library is inside the **strm** namespace.*

To start using CppStreams first include the CppStream.hpp file in your project.
``` cpp
#include <CppStreams.hpp>
```

### Classes
1. **strm::Stream:** this is the base class, represents a stream of data
2. **strm::Node:** instances of this class will hold the actual data inside a Stream
3. **strm::Iterator:** this class allows the user to iterate over the elements of a Stream

### strm::Stream
This is the base class. To start working with Streams, you just need to create an instance of this class passing the data you want by parameter.

*A very simple example could be*
``` cpp
strm::Stream myStream{ 10, 2, 54, 2, 34, 1, 34 }; // Instance of a Stream
std::cout << "Is any number even? " << myStream.anyMatch( [] ( auto x ) { return x % 10 == 0; } ) << std::endl;
```

#### strm::Stream: Public Methods
``` cpp
strm::Stream< T >::Stream();
strm::Stream< T >::Stream( const strm::Stream< T >& p_other );
strm::Stream< T >::Stream( strm::Stream< T >&& p_other )
strm::Stream< T >::Stream( const std::initializer_list< T >& data );
template < typename InputIterator > strm::Stream< T >::Stream( const InputIterator& first, const InputIterator& last );

strm::Stream< T >::~Stream();

strm::Iterator< T > strm::Stream< T >::begin() const;
strm::Iterator< T > strm::Stream< T >::end() const;

bool strm::Stream< T >::allMatch( const std::function< bool( const T& ) >& predicate ) const;
bool strm::Stream< T >::anyMatch( const std::function< bool( const T& ) >& predicate ) const;

strm::Stream< T > strm::Stream< T >::concat( const strm::Stream< T >& other ) const;
strm::Stream< T > strm::Stream< T >::concat( strm::Stream< T >&& other ) const;
strm::Stream< T > strm::Stream< T >::concat( const std::initializer_list< T >& data ) const;
template < typename InputIterator > strm::Stream< T > strm::Stream< T >::concat( const InputIterator& first, const InputIterator& last ) const;

const size_t& strm::Stream< T >::count() const;

strm::Stream< T > strm::Stream< T >::distinct( const std::function< bool( const T&, const T& ) >& predicate ) const

strm::Stream< T > strm::Stream< T >::filter( const std::function< bool( const T& ) >& predicate ) const;

const strm::Stream< T >& strm::Stream< T >::forEach( const std::function< void( const T& ) >& callback ) const;
const strm::Stream< T >& strm::Stream< T >::forEach( const std::function< void( const T&, const size_t& ) >& callback ) const;

strm::Stream< T > strm::Stream< T >::map( const std::function< T( const T& ) >& callback ) const;
template < typename U > strm::Stream< U > strm::Stream< T >::map( const std::function< U( const T& ) >& callback ) const;

T strm::Stream< T >::reduce( const std::function< T( const T&, const T& ) >& callback, const T& ini ) const;
template < typename U > U strm::Stream< T >::reduce( const std::function< U( const U&, const T& ) >& callback, const U& ini ) const;
```

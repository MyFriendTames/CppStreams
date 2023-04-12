# Cpp Streams

This is a simple lightweight library inspired by the java.util.stream library available since Java 8.
It provides functional style programing for processing lists of elements.

```
At least C++14 is required for this library to work.
```

*CppStreams library is distributed under the ISC open source licence*

## Documentation

*First note that everything in this library is inside the **strm** namespace.*

To start usng CppStreams first include the CppStream.hpp file in your project.
``` cpp
#include <CppStreams.hpp>
```

### Classes
1. **strm::Stream:** this is the base class, represents an stream of data
2. **strm::Node:** instances of this class will hold the actual data inside a Stream
3. **strm::Iterator:** this class allows the user to iterate over the elements of a Stream

#### 1. strm::Stream
This is the base class. To start working with Streams, you just need to create an instance of this class passing the data you want as parameter.

*A very simple example could be*
``` cpp
strm::Stream myStream{ 10, 2, 54, 2, 34, 1, 34 }; // Instance of a Stream
std::cout << "Is any number even? " << myStream.anyMatch( [] ( auto x ) { return x % 10 == 0; } ) << std::endl;
```
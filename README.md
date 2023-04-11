# Cpp Streams

This is a simple lightweight library inspired on the java.util.stream library available since Java 8.
It provides functional style programing for processing lists of elements.

**C++14+** is required for it to work.

**Cpp Streams library is distributed under the ISC open source licence**

## Documentation

*First note that everything in this library is inside the **strm** namespace.*

### Structure
* strm::Stream
* strm::StreamNode

#### strm::Stream
This is the base class. To start working with Streams, you just need to create an instance of this class

*the following code shows how to create an empty Stream (not very useful)*
``` cpp
strm::Stream myStream;
```
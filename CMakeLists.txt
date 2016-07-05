cmake_minimum_required(VERSION 3.3)
project(sbt)

set(CMAKE_CXX_FLAGS "-g -Wall -Ofast ${CMAKE_CXX_FLAGS} -std=c++14 -lz")

set(SOURCE_FILES main.cpp bloom/BloomFilter.cpp bloom/BloomFilter.h dna/Sequence.cpp dna/Sequence.h tree/Tree.cpp tree/Tree.h tree/Node.cpp tree/Node.h bloom/hash/HashFn.cpp bloom/hash/HashFn.h bloom/SimpleBloomFilter.cpp bloom/SimpleBloomFilter.h bloom/hash/SimpleHashFn.cpp bloom/hash/SimpleHashFn.h dna/SimpleSequence.cpp dna/SimpleSequence.h bloom/hash/HashFnSingleton.cpp bloom/hash/HashFnSingleton.h dna/Sequence.cpp dna/Sequence.h dna/Kmer.cpp dna/Kmer.h dna/SimpleKmer.cpp dna/SimpleKmer.h bloom/factory/BloomFilterFactory.cpp bloom/factory/BloomFilterFactory.h tree/query/QueryProcessor.cpp tree/query/QueryProcessor.h tree/query/QueryUnit.cpp tree/query/QueryUnit.h tree/query/SimpleQueryProcessor.cpp tree/query/SimpleQueryProcessor.h parser/kseq.h bloom/hash/AstralHashFn.cpp bloom/hash/AstralHashFn.h dna/AstralSequence.cpp dna/AstralSequence.h bloom/AstralBloomFilter.cpp bloom/AstralBloomFilter.h tree/query/DepthQueryProcessor.cpp tree/query/DepthQueryProcessor.h tree/query/DepthQueryUnit.cpp tree/query/DepthQueryUnit.h tree/query/SequenceDepthQueryUnit.cpp tree/query/SequenceDepthQueryUnit.h)

set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.54.0 COMPONENTS log)
find_package(Threads)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(sbt ${SOURCE_FILES})
    target_link_libraries(sbt ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
endif ()

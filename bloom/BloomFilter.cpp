//
// Created by luka on 4/27/16.
//

#include "BloomFilter.h"


BloomFilter::BloomFilter(std::vector<HashFn *> *_hashFns) : _hashFns(_hashFns) { }
//
// Created by luka on 5/5/16.
//

#include "BloomFilterFactory.h"
#include "../SimpleBloomFilter.h"
#include "../AstralBloomFilter.h"


BloomFilter *BloomFilterFactory::createBloomFilter(Sequence *sequence) {
    return new AstralBloomFilter((AstralSequence *) sequence);
}

BloomFilter *BloomFilterFactory::createBloomFilter(Sequence *sequence, std::string comment) {
    return new AstralBloomFilter((AstralSequence *) sequence);
}


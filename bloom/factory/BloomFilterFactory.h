//
// Created by luka on 5/5/16.
//

#ifndef SBT_BLOOMFILTERFACTORY_H
#define SBT_BLOOMFILTERFACTORY_H


#include "../BloomFilter.h"

class BloomFilterFactory {
public:
    BloomFilter *createBloomFilter(Sequence *sequence);
    BloomFilter *createBloomFilter(Sequence *sequence, std::string comment);

};


#endif //SBT_BLOOMFILTERFACTORY_H

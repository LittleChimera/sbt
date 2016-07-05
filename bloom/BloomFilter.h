//
// Created by luka on 4/27/16.
//

#ifndef SBT_BLOOMFILTER_H
#define SBT_BLOOMFILTER_H


#include <vector>
#include "hash/HashFn.h"
#include "../dna/Sequence.h"

class BloomFilter {
public:

    BloomFilter(std::vector<HashFn *> *_hashFns);

    virtual void merge(BloomFilter *bloomFilter) = 0;

    virtual bool matchesFilter(BloomFilter *bloomFilter) = 0;

    virtual double treshold(BloomFilter *bloomFilter) = 0;

    virtual int hammingDistance(BloomFilter *bloomFilter) = 0;

    virtual double load() = 0;

    virtual BloomFilter *copy() = 0;

    virtual double tresholdOnSequence(Sequence *bloomFilter) {
        return 0.0;
    }

    virtual bool matchesSequence(Sequence *sequence) {
        return false;
    }

    virtual long hammingDistanceForSequence(Sequence *sequence) {
        return 0;
    }

    virtual void mergeSequence(Sequence *sequence) { }

protected:

    virtual void addToFilter(unsigned long hash) = 0;

    std::vector<HashFn *> *_hashFns;

};


#endif //SBT_BLOOMFILTER_H

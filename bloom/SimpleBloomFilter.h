//
// Created by luka on 4/27/16.
//

#ifndef SBT_SIMPLEBLOOMFILTER_H
#define SBT_SIMPLEBLOOMFILTER_H
#define SIMPLE_FILTER_SIZE 800

#include <vector>
#include "BloomFilter.h"
#include "hash/SimpleHashFn.h"
#include "../dna/Sequence.h"
#include "hash/HashFnSingleton.h"
#include <boost/log/trivial.hpp>
#include <iostream>

class SimpleBloomFilter : public BloomFilter {


public:
    static const int FILTER_SIZE = SIMPLE_FILTER_SIZE;

    virtual double load();

    SimpleBloomFilter() : BloomFilter(HashFnSingleton::getHashFns()), _filter(FILTER_SIZE, false) { }

    SimpleBloomFilter(Sequence *sequence) : BloomFilter(HashFnSingleton::getHashFns()), _filter(FILTER_SIZE, false) {
        for (auto fn : *_hashFns) {
            std::vector<std::string> kmers = sequence->getKmers();
            for (auto kmer : kmers) {
//                BOOST_LOG_TRIVIAL(debug) << "hashing kmer: " << kmer;
            }
            for (auto kmer : kmers) {
                this->addToFilter(fn->hash(&kmer));
            }
        }
//        for (auto bit : _filter) {
//            std::cout << bit;
//        }
//        std::cout << std::endl;
    }

    virtual double treshold(BloomFilter *bloomFilter);

    virtual bool matchesFilter(BloomFilter *bloomFilter);

    virtual int hammingDistance(BloomFilter *bloomFilter);

    virtual void merge(BloomFilter *bloomFilter);

    virtual BloomFilter *copy();

    virtual double tresholdOnSequence(Sequence *bloomFilter) override;

    virtual bool matchesSequence(Sequence *sequence) override;

    virtual long hammingDistanceForSequence(Sequence *sequence) override;

    virtual void mergeSequence(Sequence *sequence) override;

protected:

    virtual void addToFilter(unsigned long hash);
    std::vector<bool> _filter;
    long bits = 0;

private:
};


#endif //SBT_SIMPLEBLOOMFILTER_H

//
// Created by luka on 4/27/16.
//

#include <iostream>
#include <algorithm>
#include <boost/log/trivial.hpp>
#include <libmng_types.h>
#include "SimpleBloomFilter.h"
#include <set>
#include <hdf5_hl.h>

bool SimpleBloomFilter::matchesFilter(BloomFilter *bloomFilter) {
    //TODO add error checking
    SimpleBloomFilter *simpleBloomFilter = (SimpleBloomFilter *) bloomFilter;

    for (int i = 0; i < FILTER_SIZE; ++i) {
        if (_filter[i] && !simpleBloomFilter->_filter[i]) return false;
    }
    return true;
}

int SimpleBloomFilter::hammingDistance(BloomFilter *bloomFilter) {
    //TODO add error checking
    SimpleBloomFilter *simpleBloomFilter = (SimpleBloomFilter *) bloomFilter;

    int distance = 0;
    for (int i = 0; i < FILTER_SIZE; ++i) {
        distance += abs(_filter[i] - simpleBloomFilter->_filter[i]);
    }
    return distance;
}

void SimpleBloomFilter::addToFilter(unsigned long hash) {
    int index = hash % FILTER_SIZE;
    if (!_filter[index]) {
        _filter[index] = true;
        bits++;
    }
}

void SimpleBloomFilter::merge(BloomFilter *bloomFilter) {
    int beforeMerge = std::count(_filter.begin(), _filter.end(), true);
    BOOST_LOG_TRIVIAL(debug) << "Before merge: " << beforeMerge;
    //TODO add error checking
    SimpleBloomFilter *simpleBloomFilter = (SimpleBloomFilter *) bloomFilter;

    for (int i = 0; i < FILTER_SIZE; ++i) {
        _filter[i] = _filter[i] || simpleBloomFilter->_filter[i];
    }
    int afterMerge = std::count(_filter.begin(), _filter.end(), true);
    BOOST_LOG_TRIVIAL(debug) << "After merge: " << afterMerge;
    if (beforeMerge > afterMerge) {
        throw std::invalid_argument("stupid merging");
    }
}


BloomFilter *SimpleBloomFilter::copy() {
    BOOST_LOG_TRIVIAL(debug) << "Copying Simple bloom filter";
    SimpleBloomFilter *bf = new SimpleBloomFilter();
    bf->_filter.swap(_filter);
    return bf;
}

double SimpleBloomFilter::treshold(BloomFilter *bloomFilter) {
//    return 1.0;
    //TODO add error checking
    SimpleBloomFilter *simpleBloomFilter = (SimpleBloomFilter *) bloomFilter;

//    BOOST_LOG_TRIVIAL(debug) << std::count(_filter.begin(), _filter.end(), true);
    long intersection = 0;
    long querySize = 0;
    for (int i = 0; i < FILTER_SIZE; ++i) {
        if (_filter[i] && simpleBloomFilter->_filter[i]) {
            intersection++;
        }
        if (_filter[i]) {
            querySize++;
        }
    }
    BOOST_LOG_TRIVIAL(debug) << "Query size: " << querySize;
    return intersection / (double) querySize;
//    return matchesFilter(bloomFilter) ? 1.0 : 0.0;
}

double SimpleBloomFilter::tresholdOnSequence(Sequence *sequence) {
    long intersection = 0;
    long querySize;

    std::vector<long> *hashes = sequence->getHashes();
    querySize = hashes->size();
    for (int j = 0, jLen = hashes->size(); j < jLen; j++) {
//        std::cout << hashes->size() << " : " << j << std::endl;
        std::vector<long> &hshs = *hashes;
        long index = (int)(hshs[j]) % FILTER_SIZE;
//        std::cout << (hshs[j]) << " : " << index << std::endl;
        if (_filter[index]) intersection++;
    }
    return intersection / (double) querySize;
//    return matchesFilter(bloomFilter) ? 1.0 : 0.0;
}

bool SimpleBloomFilter::matchesSequence(Sequence *sequence) {
    return tresholdOnSequence(sequence) > 0.5;
}

double SimpleBloomFilter::load() {
    return std::count(_filter.begin(), _filter.end(), true) / (double) FILTER_SIZE;
}

long SimpleBloomFilter::hammingDistanceForSequence(Sequence *sequence) {
    std::set<int> indexes;
    std::set<int> add;
    std::vector<long> hashes = *sequence->getHashes();
    for (int i = 0, len = hashes.size(); i < len; ++i) {
        int index = hashes[i] % FILTER_SIZE;
        if (_filter[index]) {
            indexes.insert(index);
        } else {
            add.insert(index);
        }
    }
    return add.size() + bits - indexes.size();
}

void SimpleBloomFilter::mergeSequence(Sequence *sequence) {
    for (auto hash : *sequence->getHashes()) {
        addToFilter(hash);
    }
}




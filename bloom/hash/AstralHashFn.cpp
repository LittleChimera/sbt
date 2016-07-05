//
// Created by luka on 5/20/16.
//

#include <stdexcept>
#include <boost/log/trivial.hpp>
#include <iostream>
#include "AstralHashFn.h"

static const int DOWN_SIZE = 'a';
static const int KMER_LENGTH = 5;

unsigned long AstralHashFn::hash(std::string *string) {

    if (string->size() != KMER_LENGTH) {
        BOOST_LOG_TRIVIAL(debug) << "hashing string of length " << string->size() << " failed";
        throw std::invalid_argument("only accepting strings of length " + KMER_LENGTH);
    }
    long kmer_hash[KMER_LENGTH];
    for (int i = 0; i < KMER_LENGTH; ++i) {
        if (string->at(i) == 'X') {
            kmer_hash[i] = 0;
        } else {
            kmer_hash[i] = string->at(i) - DOWN_SIZE;
        }
    }
    long hash = 0L;
    hash |= kmer_hash[0] << 12;
    hash |= kmer_hash[1] << 9;
    hash |= kmer_hash[2] << 6;
    hash |= kmer_hash[3] << 3;
    hash |= kmer_hash[4];
//    if (hash < 0L) {
//        std::cout << *string << "ALOOOO " << hash << std::endl;
//    }
    hash += (kmer_hash[3] >> 1);
    hash += (kmer_hash[2] >> 2);

    return hash;
}


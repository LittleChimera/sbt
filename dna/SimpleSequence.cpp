//
// Created by luka on 4/27/16.
//

#include <iostream>
#include "SimpleSequence.h"

void SimpleSequence::setSequence(std::string *sequence) {
    _sequence = *sequence;
}

std::string *SimpleSequence::getSequence() {
    return &_sequence;
}

std::vector<std::string> SimpleSequence::getKmers() {
    std::vector<std::string> kmers(_sequence.size() - KMER_SIZE + 1);
    for (long i = 0; i < _sequence.size() - KMER_SIZE + 1; ++i) {
        kmers.push_back(_sequence.substr(i, KMER_SIZE));
    }
    return kmers;
}

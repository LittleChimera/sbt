//
// Created by luka on 4/27/16.
//

#ifndef SBT_SIMPLESEQUENCE_H
#define SBT_SIMPLESEQUENCE_H


#define SIMPLE_KMER_SIZE 4

#include "Sequence.h"
#include "../bloom/SimpleBloomFilter.h"

class SimpleSequence : public Sequence {


public:
    SimpleSequence(std::string _sequence) : _sequence(_sequence) { }

    void setSequence(std::string *sequence);

    std::string *getSequence();

    std::vector<std::string> getKmers();

private:
    std::string _sequence;
    const unsigned long KMER_SIZE = SIMPLE_KMER_SIZE;
};


#endif //SBT_SIMPLESEQUENCE_H

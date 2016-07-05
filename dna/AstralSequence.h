//
// Created by luka on 5/20/16.
//

#ifndef SBT_ASTRALSEQUENCE_H
#define SBT_ASTRALSEQUENCE_H
#define KMER_SIZE 5


#include <boost/log/trivial.hpp>
#include "Sequence.h"
#include "../bloom/hash/HashFnSingleton.h"
#include "../bloom/SimpleBloomFilter.h"

class AstralSequence : public Sequence {

public:

    AstralSequence(std::string sequence, std::string comment) : sequence(sequence), comment(comment) {
//        BOOST_LOG_TRIVIAL(debug) << "Astral sequence: " << this->sequence;
//        BOOST_LOG_TRIVIAL(debug) << "Astral comment: " << this->comment;
        kmers = std::vector<std::string>(sequence.size() / KMER_SIZE);
        hashes = std::vector<long>();

//    BOOST_LOG_TRIVIAL(debug) << "astral kmers count: " << kmers.size();
        for (long i = 0; i * KMER_SIZE < sequence.size() - KMER_SIZE + 1; i++) { //not using sliding window
            std::string kmer = sequence.substr(i * KMER_SIZE, KMER_SIZE);
//        BOOST_LOG_TRIVIAL(debug) << "Astral kmer: " << kmer;
            kmers[i] = kmer;
        }
        std::vector<HashFn *> *hashFns = HashFnSingleton::getHashFns();
        for (int i = 0, iLen = hashFns->size(); i < iLen; i++) {
            for (int j = 0, jLen = kmers.size(); j < jLen; j++) {
                long value = (*hashFns)[i]->hash(&kmers[j]);
                hashes.push_back(value);
            }
        }
//    BOOST_LOG_TRIVIAL(debug) << "hashing kmer[0]: " << kmers[0];
    }

    virtual void setSequence(std::string *sequence);

    virtual std::string *getSequence();

    virtual std::vector<std::string> getKmers();

    std::string *getComment() {
        return &comment;
    }


    virtual std::vector<long> *getHashes() {
        return &hashes;
    }

private:
    std::string sequence;
    std::vector<std::string> kmers;
    std::string comment;
    std::vector<long> hashes;
};


#endif //SBT_ASTRALSEQUENCE_H

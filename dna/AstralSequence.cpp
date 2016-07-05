//
// Created by luka on 5/20/16.
//

#include "AstralSequence.h"
#define KMER_SIZE 5


void AstralSequence::setSequence(std::string *sequence) {

}

std::string *AstralSequence::getSequence() {
    return &sequence;
}

std::vector<std::string> AstralSequence::getKmers() {
    return kmers;
    static std::vector<std::string> kmers(sequence.size() / KMER_SIZE);
    static bool initialized = false;
    if (initialized) return kmers;
    initialized = true;

//    BOOST_LOG_TRIVIAL(debug) << "astral kmers count: " << kmers.size();
    for (long i = 0; i * KMER_SIZE < sequence.size() - KMER_SIZE + 1; i++) { //not using sliding window
        std::string kmer = sequence.substr(i * KMER_SIZE, KMER_SIZE);
//        BOOST_LOG_TRIVIAL(debug) << "Astral kmer: " << kmer;
        kmers[i] = kmer;
    }
//    BOOST_LOG_TRIVIAL(debug) << "hashing kmer[0]: " << kmers[0];

    return kmers;
}


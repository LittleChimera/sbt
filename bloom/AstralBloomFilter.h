//
// Created by luka on 5/20/16.
//

#ifndef SBT_ASTRALBLOOMFILTER_H
#define SBT_ASTRALBLOOMFILTER_H


#include "BloomFilter.h"
#include "SimpleBloomFilter.h"
#include "../dna/AstralSequence.h"

class AstralBloomFilter : public SimpleBloomFilter {


public:
    virtual BloomFilter *copy() override;


    AstralBloomFilter() : SimpleBloomFilter(), comment("asdf") { }

    AstralBloomFilter(AstralSequence *sequence) : SimpleBloomFilter(sequence),
                                                                        comment(*sequence->getComment()) {
//        BOOST_LOG_TRIVIAL(debug) << "astral bloom filter comment: " << getComment();
    }

    const std::string &getComment() const {
        return comment;
    }

private:
    std::string comment;
};


#endif //SBT_ASTRALBLOOMFILTER_H

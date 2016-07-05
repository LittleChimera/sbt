//
// Created by luka on 5/5/16.
//

#ifndef SBT_QUERYPROCESSOR_H
#define SBT_QUERYPROCESSOR_H


#include <queue>
#include "../Node.h"
#include "QueryUnit.h"

class QueryProcessor {
public:
    virtual BloomFilter *queryFirst(Node *node, BloomFilter *filter)=0;
    virtual std::vector<BloomFilter *> queryAll(Node *node, BloomFilter *filter)=0;
    virtual std::vector<BloomFilter *> queryAllForSequence(Node *node, Sequence *sequence)=0;

protected:
    static constexpr double INSERT_TRESHOLD = 0.5;

};


#endif //SBT_QUERYPROCESSOR_H

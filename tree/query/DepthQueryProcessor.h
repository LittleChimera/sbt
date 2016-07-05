//
// Created by luka on 5/29/16.
//

#ifndef SBT_DEPTHQUERYPROCESSOR_H
#define SBT_DEPTHQUERYPROCESSOR_H


#include "QueryProcessor.h"
#include "DepthQueryUnit.h"
#include "SequenceDepthQueryUnit.h"

class DepthQueryProcessor : public QueryProcessor {


public:
    DepthQueryProcessor(long CUTOFF_DEPTH) : CUTOFF_DEPTH(CUTOFF_DEPTH) { }

    virtual BloomFilter *queryFirst(Node *node, BloomFilter *filter) override;

    std::vector<BloomFilter *> queryAll(Node *node, BloomFilter *filter);


    std::vector<BloomFilter *> queryAllForSequence(Node *node, Sequence *sequence);

private:

    void enqueue(std::queue<DepthQueryUnit *> *queue, Node *node, BloomFilter *bloomFilter, long depth);

    long const CUTOFF_DEPTH;

    void enqueueSequence(std::queue<SequenceDepthQueryUnit *> *queue, Node *node, Sequence *sequence, long depth);
};


#endif //SBT_DEPTHQUERYPROCESSOR_H

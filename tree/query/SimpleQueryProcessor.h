//
// Created by luka on 5/5/16.
//

#ifndef SBT_SIMPLEQUERYPROCESSOR_H
#define SBT_SIMPLEQUERYPROCESSOR_H


#include "QueryProcessor.h"

class SimpleQueryProcessor : public QueryProcessor {
private:

public:
    virtual std::vector<BloomFilter *> queryAll(Node *node, BloomFilter *filter) override;

    virtual BloomFilter *queryFirst(Node *node, BloomFilter *filter) override;

    virtual std::vector<BloomFilter *> queryAllForSequence(Node *node, Sequence *sequence) {
        return std::vector<BloomFilter*>();
    }


protected:

    virtual void enqueue(std::queue<QueryUnit*> *queue, Node *node, BloomFilter *bloomFilter);
};


#endif //SBT_SIMPLEQUERYPROCESSOR_H

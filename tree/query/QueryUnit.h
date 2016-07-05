//
// Created by luka on 5/5/16.
//

#ifndef SBT_QUERYUNIT_H
#define SBT_QUERYUNIT_H


#include "../Node.h"
#include "../../bloom/BloomFilter.h"

class QueryUnit {
public:

    QueryUnit(Node *node, BloomFilter *bloomFilter) : node(node), bloomFilter(bloomFilter) { }


    Node *getNode() const {
        return node;
    }

    BloomFilter *getBloomFilter() const {
        return bloomFilter;
    }

private:
    Node *node;
    BloomFilter *bloomFilter;
};


#endif //SBT_QUERYUNIT_H

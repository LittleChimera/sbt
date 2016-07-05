//
// Created by luka on 5/29/16.
//

#ifndef SBT_DEPTHQUERYUNIT_H
#define SBT_DEPTHQUERYUNIT_H


#include "QueryUnit.h"

class DepthQueryUnit : public QueryUnit {

public:
    DepthQueryUnit(Node *node, BloomFilter *bloomFilter, long depth) : QueryUnit(node, bloomFilter), depth(depth) { }

    long getDepth() const {
        return depth;
    }

private:
    long depth;
};


#endif //SBT_DEPTHQUERYUNIT_H

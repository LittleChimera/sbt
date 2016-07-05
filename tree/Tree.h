//
// Created by luka on 4/27/16.
//

#ifndef SBT_TREE_H
#define SBT_TREE_H

#include "Node.h"
#include "../bloom/factory/BloomFilterFactory.h"
#include "query/QueryProcessor.h"
#include "query/SimpleQueryProcessor.h"
#include "query/DepthQueryProcessor.h"

class Tree {

public:
    Tree() : Tree(100000000L) {}

    Tree(long queryCutoff) : _root(new Node()) {
        qp = new DepthQueryProcessor(queryCutoff);
    }



    BloomFilter *queryFirst(Sequence *sequence);

    std::vector<BloomFilter *> queryAll(Sequence *sequence);

    void insert(Sequence *sequence);

    void print();

    void printToFile(std::string filename);

private:
    void insert(BloomFilter *filter, Node *parent);

    Node *_root;
    BloomFilterFactory *_bloomFilterFactory;
    QueryProcessor *qp;

    void insertSequence(Sequence *sequence, Node *parent);
};


#endif //SBT_TREE_H

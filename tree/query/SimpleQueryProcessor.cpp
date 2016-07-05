//
// Created by luka on 5/5/16.
//

#include <queue>
#include "SimpleQueryProcessor.h"

BloomFilter * SimpleQueryProcessor::queryFirst(Node *node, BloomFilter *filter) {
    std::queue<QueryUnit *> queue1;
    queue1.push(new QueryUnit(node, filter));

    BloomFilter *result = nullptr;

    long iterateCount = 0;
    while (!queue1.empty()) {
        iterateCount++;
        QueryUnit *qu = queue1.front();
        queue1.pop();

        if (!qu->getNode()->hasLeft() && !qu->getNode()->hasRight()) {
            if (filter->matchesFilter(qu->getNode()->getFilter())) {
                result = qu->getNode()->getFilter();
            }
        } else {
            enqueue(&queue1, qu->getNode()->getLeft(), filter);
            enqueue(&queue1, qu->getNode()->getRight(), filter);
        }
    }
    std::cout << "Query iterate count: " << iterateCount << std::endl;
    return result;
}

void SimpleQueryProcessor::enqueue(std::queue<QueryUnit *> *queue, Node *node, BloomFilter *bloomFilter) {
    if (bloomFilter->treshold(node->getFilter()) > INSERT_TRESHOLD) {
        queue->push(new QueryUnit(node, bloomFilter));
    }
}

std::vector<BloomFilter *> SimpleQueryProcessor::queryAll(Node *node, BloomFilter *filter) {
    return std::vector<BloomFilter *>();
}


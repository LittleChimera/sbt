//
// Created by luka on 5/29/16.
//

#include "DepthQueryProcessor.h"
#include "DepthQueryUnit.h"
#include "SequenceDepthQueryUnit.h"


std::vector<BloomFilter *> DepthQueryProcessor::queryAll(Node *node, BloomFilter *filter) {
    std::vector<BloomFilter*> results;
    std::queue<DepthQueryUnit *> queue1;
    queue1.push(new DepthQueryUnit(node, filter, 0L));
    long max_depth = 0L;

    long iterateCount = 0;
    while (!queue1.empty()) {
        iterateCount++;

        DepthQueryUnit *qu = queue1.front();
        queue1.pop();

        if (!qu->getNode()->hasLeft() && !qu->getNode()->hasRight()) {
            if (filter->matchesFilter(qu->getNode()->getFilter())) {
                results.push_back(qu->getNode()->getFilter());
            }
        } else if (qu->getDepth() > CUTOFF_DEPTH) {
            std::vector<BloomFilter *> nodeResults = qu->getNode()->leafs();
            results.insert(std::end(results), std::begin(nodeResults), std::end(nodeResults));
        } else {
            if (qu->getDepth() > max_depth) {
                max_depth = qu->getDepth();
            }
            enqueue(&queue1, qu->getNode()->getLeft(), filter, qu->getDepth());
            enqueue(&queue1, qu->getNode()->getRight(), filter, qu->getDepth());
        }
    }
    std::cout << "Max depth: " << max_depth << std::endl;
    std::cout << "Query iterate count: " << iterateCount << std::endl;
    return results;
}

std::vector<BloomFilter *> DepthQueryProcessor::queryAllForSequence(Node *node, Sequence *sequence) {
    std::vector<BloomFilter*> results;
    std::queue<SequenceDepthQueryUnit *> queue1;
    queue1.push(new SequenceDepthQueryUnit(node, sequence, 0L));

    long max_depth = 0l;
    long iterateCount = 0;
    while (!queue1.empty()) {
        iterateCount++;

        SequenceDepthQueryUnit *qu = queue1.front();
        queue1.pop();

        if (!qu->getNode()->hasLeft() && !qu->getNode()->hasRight()) {
            if (qu->getNode()->getFilter()->matchesSequence(sequence)) {
                results.push_back(qu->getNode()->getFilter());
            }
        } else if (qu->getDepth() > CUTOFF_DEPTH) {
            std::vector<BloomFilter *> nodeResults = qu->getNode()->leafs();
            results.insert(std::end(results), std::begin(nodeResults), std::end(nodeResults));
        } else {
            if (qu->getDepth() > max_depth) {
                max_depth = qu->getDepth();
            }
            enqueueSequence(&queue1, qu->getNode()->getLeft(), sequence, qu->getDepth());
            enqueueSequence(&queue1, qu->getNode()->getRight(), sequence, qu->getDepth());
        }
    }
    std::cout << "Max depth: " << max_depth << std::endl;
    std::cout << "False positive results: " << results.size() - 1 << std::endl;
    std::cout << "Query iterate count: " << iterateCount << std::endl;
    return results;
}

void DepthQueryProcessor::enqueue(std::queue<DepthQueryUnit *> *queue, Node *node, BloomFilter *bloomFilter, long depth) {
    if (bloomFilter->treshold(node->getFilter()) > INSERT_TRESHOLD) {
        queue->push(new DepthQueryUnit(node, bloomFilter, depth + 1));
    }
}

void DepthQueryProcessor::enqueueSequence(std::queue<SequenceDepthQueryUnit *> *queue, Node *node, Sequence *sequence, long depth) {
    if (node->getFilter()->tresholdOnSequence(sequence) > INSERT_TRESHOLD) {
        queue->push(new SequenceDepthQueryUnit(node, sequence, depth + 1));
    }
}

BloomFilter *DepthQueryProcessor::queryFirst(Node *node, BloomFilter *filter) {
    return nullptr;
}




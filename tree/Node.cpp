//
// Created by luka on 4/27/16.
//

#include <queue>
#include "Node.h"


std::vector<BloomFilter *> Node::leafs() {
    std::vector<BloomFilter *> leafs;
    std::queue<Node *> queryNodes;
    queryNodes.push(this);

    while (!queryNodes.empty()) {
        Node *queryingNode = queryNodes.front();
        queryNodes.pop();

        if (!queryingNode->hasLeft() && !queryingNode->hasRight()) {
            leafs.push_back(queryingNode->getFilter());
        }

        if (queryingNode->hasLeft()) {
            queryNodes.push(queryingNode->getLeft());
        }
        if (queryingNode->hasRight()) {
            queryNodes.push(queryingNode->getRight());
        }
    }
    return leafs;
}


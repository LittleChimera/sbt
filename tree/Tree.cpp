//
// Created by luka on 4/27/16.
//

#include <stdexcept>
#include <iostream>
#include <utility>
#include <boost/log/trivial.hpp>
#include <fstream>
#include "Tree.h"

void Tree::insert(Sequence *sequence) {
    insertSequence(sequence, _root);
}

void Tree::insert(BloomFilter *filter, Node *parent) {
    BOOST_LOG_TRIVIAL(debug) << "inserting : " << ((AstralBloomFilter*)filter)->getComment();
    if (parent->hasLeft() && !parent->hasRight() && filter->matchesFilter(parent->getLeftFilter())) {
        parent->insertRight(filter);
        BOOST_LOG_TRIVIAL(debug) << "...inserting right leaf.";

    } else if (parent->hasLeft() && parent->hasRight()) {
        insert(filter,
               parent->getLeftFilter()->hammingDistance(filter) < parent->getRightFilter()->hammingDistance(filter) ?
               parent->getLeft() : parent->getRight()
        );
        BOOST_LOG_TRIVIAL(debug) << "...recursive insert.";

    } else if (!parent->hasLeft() && !parent->hasRight()) {
        parent->insertLeft(parent->getFilter()->copy());
        parent->insertRight(filter);
//        parent->getFilter()->merge(filter);
        BOOST_LOG_TRIVIAL(debug) << "...inserting left & right leaf.";

    } else {
        throw std::invalid_argument("invalid state of tree");
    }
    parent->getFilter()->merge(filter);
}

void Tree::insertSequence(Sequence *sequence, Node *parent) {
//    BOOST_LOG_TRIVIAL(debug) << "inserting : " << ((AstralBloomFilter*)filter)->getComment();
    if (parent->hasLeft() && !parent->hasRight() && parent->getLeftFilter()->matchesSequence(sequence)) {
        parent->insertRight(_bloomFilterFactory->createBloomFilter(sequence));
        BOOST_LOG_TRIVIAL(debug) << "...inserting right leaf.";

    } else if (parent->hasLeft() && parent->hasRight()) {
//        if (parent->getLeftFilter()->hammingDistanceForSequence(sequence) != parent->getLeftFilter()->hammingDistance(_bloomFilterFactory->createBloomFilter(sequence))) {
//            std::cout << "evo ga livi" << parent->getLeftFilter()->hammingDistanceForSequence(sequence) << " " << parent->getLeftFilter()->hammingDistance(_bloomFilterFactory->createBloomFilter(sequence)) << std::endl;
//        }
//        if (parent->getRightFilter()->hampmingDistanceForSequence(sequence) != parent->getRightFilter()->hammingDistance(_bloomFilterFactory->createBloomFilter(sequence))) {
//            std::cout << "evo ga desni" << std::endl;
//        }
        insertSequence(sequence,
               parent->getLeftFilter()->hammingDistanceForSequence(sequence) < parent->getRightFilter()->hammingDistanceForSequence(sequence) ?
               parent->getLeft() : parent->getRight()
        );
        BOOST_LOG_TRIVIAL(debug) << "...recursive insert.";

    } else if (!parent->hasLeft() && !parent->hasRight()) {
        parent->insertLeft(parent->getFilter()->copy());
        parent->insertRight(_bloomFilterFactory->createBloomFilter(sequence));
//        parent->getFilter()->merge(filter);
        BOOST_LOG_TRIVIAL(debug) << "...inserting left & right leaf.";

    } else {
        throw std::invalid_argument("invalid state of tree");
    }
    parent->getFilter()->mergeSequence(sequence);
}



BloomFilter *Tree::queryFirst(Sequence *sequence) {
    return qp->queryFirst(_root, _bloomFilterFactory->createBloomFilter(sequence));
}


void Tree::print() {
    int l = 1;
    std::vector<std::vector<int>> treeMap;
    std::queue<std::pair<Node*, std::pair<int,int>>> nodeVisitor;
    nodeVisitor.push(std::make_pair(_root, std::make_pair(0, 0)));

    while (!nodeVisitor.empty()) {
        Node* node = nodeVisitor.front().first;
        int depth = nodeVisitor.front().second.first;
        int order = nodeVisitor.front().second.second;
        nodeVisitor.pop();

        if (treeMap.size() < depth + 1) {
            treeMap.push_back(std::vector<int>());
        }
        treeMap[depth].push_back(order);

        if(node->hasLeft()) {
            nodeVisitor.push(std::make_pair(node->getLeft(), std::make_pair(depth + 1, order * 2)));
        }
        if(node->hasRight()) {
            nodeVisitor.push(std::make_pair(node->getRight(), std::make_pair(depth + 1, order * 2 + 1)));
        }
    }

    int maxDepth = treeMap.size();
    for (int i = 0; i < treeMap.size(); i++) {
        for (auto n : treeMap[i]) {
            std::cout << n << " ";
        }
        std::cout << std::endl;
    }
}

void Tree::printToFile(std::string filename) {
    std::ofstream outfile(filename);
    if(!outfile.is_open()) {
        BOOST_LOG_TRIVIAL(error) << "Couldn't output tree to file";
    }

    outfile << "digraph g{" << std::endl;
    std::queue<Node*> nodeVisitor;
    nodeVisitor.push(_root);
    while (!nodeVisitor.empty()) {
        Node* node = nodeVisitor.front();
        nodeVisitor.pop();
        outfile << "   " << node->getId() << "[label=" << node->getFilter()->load() << "];" << std::endl;

        if (node->hasLeft()) {
            outfile << "   " << node->getId() << " -> " << node->getLeft()->getId() << ";" << std::endl;
            nodeVisitor.push(node->getLeft());
        }
        if (node->hasRight()) {
            outfile << "   " << node->getId() << " -> " << node->getRight()->getId() << ";" << std::endl;
            nodeVisitor.push(node->getRight());
        }
    }
    outfile << "}" << std::endl;
    outfile.close();
}

std::vector<BloomFilter *> Tree::queryAll(Sequence *sequence) {
//    return qp->queryAll(_root, _bloomFilterFactory->createBloomFilter(sequence));
    return qp->queryAllForSequence(_root, sequence);
}

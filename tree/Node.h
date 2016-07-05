//
// Created by luka on 4/27/16.
//

#ifndef SBT_NODE_H
#define SBT_NODE_H


#include <iostream>
#include <boost/log/trivial.hpp>
#include "../bloom/BloomFilter.h"
#include "../bloom/SimpleBloomFilter.h"
#include "../bloom/AstralBloomFilter.h"

class Node {

private:
    BloomFilter* _bloomFilter;
    Node* _left;
    Node* _right;
    int _id;

public:

    int getId() {
        return _id;
    }

    Node() : Node(new AstralBloomFilter()) {
    }

    Node(BloomFilter *filter) : _bloomFilter(filter), _left(nullptr), _right(nullptr) {
        static int id = 0;_id = id++;
    }

    bool hasLeft() {
        return _left != nullptr;
    }

    void insertLeft(BloomFilter *filter) {
        _left = new Node(filter);
//        BOOST_LOG_TRIVIAL(debug) << (_left->_left != nullptr ? "true" : "false" )<< " " << (_left->_right != nullptr ? "true" : "false" );
//        _left->_bloomFilter = filter;
    }

    bool hasRight() {
        return _right != nullptr;
    }

    void insertRight(BloomFilter *filter) {
        _right = new Node(filter);
//        BOOST_LOG_TRIVIAL(debug) << (_right->_left != nullptr ? "true" : "false" )<< " " << (_right->_right != nullptr ? "true" : "false" );
//        _right->_bloomFilter = filter;
    }


    BloomFilter *getLeftFilter() const {
        return _left->_bloomFilter;
    }

    BloomFilter *getRightFilter() const {
        return _right->_bloomFilter;
    }


    Node *getLeft() const {
        return _left;
    }

    Node *getRight() const {
        return _right;
    }

    BloomFilter *getFilter() {
        return _bloomFilter;
    }

    std::vector<BloomFilter *> leafs();

};


#endif //SBT_NODE_H

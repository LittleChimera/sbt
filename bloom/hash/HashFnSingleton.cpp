//
// Created by luka on 4/27/16.
//

#include "HashFnSingleton.h"
#include "SimpleHashFn.h"
#include "AstralHashFn.h"

std::vector<HashFn*> *HashFnSingleton::getHashFns() {
    static std::vector<HashFn*> _simpleFns;
    if (_simpleFns.empty()) {
        _simpleFns.push_back(new AstralHashFn());
    }
    return &_simpleFns;
}

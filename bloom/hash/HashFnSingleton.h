//
// Created by luka on 4/27/16.
//

#ifndef SBT_HASHFNSINGLETON_H
#define SBT_HASHFNSINGLETON_H


#include "HashFn.h"
#include <vector>

class HashFnSingleton {
public:
    static std::vector<HashFn*> *getHashFns();
//    static HashFnSingleton *instance() {
//        if (singleton == nullptr) {
//            singleton = new HashFnSingleton();
//        }
//        return singleton;
//    }

private:
//    HashFnSingleton() {}
//    static HashFnSingleton *singleton;

};


#endif //SBT_HASHFNSINGLETON_H

//
// Created by luka on 4/27/16.
//

#ifndef SBT_HASHFN_H
#define SBT_HASHFN_H

#include <cstdio>
#include <string>

class HashFn {
public:
    virtual unsigned long hash(std::string *string) = 0;

};


#endif //SBT_HASHFN_H

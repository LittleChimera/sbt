//
// Created by luka on 4/27/16.
//

#ifndef SBT_SIMPLEHASHFN_H
#define SBT_SIMPLEHASHFN_H


#include "HashFn.h"

class SimpleHashFn : public HashFn {

public:

    virtual unsigned long hash(std::string *string);
};


#endif //SBT_SIMPLEHASHFN_H

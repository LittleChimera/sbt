//
// Created by luka on 5/20/16.
//

#ifndef SBT_ASTRALHASHFN_H
#define SBT_ASTRALHASHFN_H


#include "HashFn.h"

class AstralHashFn : public HashFn {

public:

    virtual unsigned long hash(std::string *string);
};


#endif //SBT_ASTRALHASHFN_H

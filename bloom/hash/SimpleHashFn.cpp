//
// Created by luka on 4/27/16.
//

#include "SimpleHashFn.h"
#include <string>

unsigned long SimpleHashFn::hash(std::string *string) {
    return std::hash<std::string>()(*string);
}

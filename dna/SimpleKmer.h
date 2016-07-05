//
// Created by luka on 4/28/16.
//

#ifndef SBT_SIMPLEKMER_H
#define SBT_SIMPLEKMER_H


#include "Kmer.h"

class SimpleKmer : public Kmer {
public:
    std::string getValue();

private:
    std::string _value;
};

#endif //SBT_SIMPLEKMER_H

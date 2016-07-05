//
// Created by luka on 4/27/16.
//

#ifndef SBT_SEQUENCE_H
#define SBT_SEQUENCE_H

#include <string>
#include <vector>

class Sequence {
public:
    virtual void setSequence(std::string *sequence) = 0;

    virtual std::string *getSequence() = 0;

    virtual std::vector<long> * getHashes() {
        return nullptr;
    }

    virtual std::vector<std::string> getKmers() = 0;

};


#endif //SBT_SEQUENCE_H

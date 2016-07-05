//
// Created by luka on 6/8/16.
//

#ifndef SBT_SEQUENCEDEPTHQUERYUNIT_H
#define SBT_SEQUENCEDEPTHQUERYUNIT_H


#include "../Node.h"
#include "../../dna/Sequence.h"

class SequenceDepthQueryUnit {

public:

    SequenceDepthQueryUnit(Node *node, Sequence *sequence, long depth) : node(node), sequence(sequence), depth(depth) { }


    Node *getNode() const {
        return node;
    }

    Sequence *getSequence() const {
        return sequence;
    }

    long getDepth() const {
        return depth;
    }

private:
    long depth;
    Node *node;
    Sequence *sequence;

};


#endif //SBT_SEQUENCEDEPTHQUERYUNIT_H

#include <iostream>
#include <bitset>
#include "bloom/BloomFilter.h"
#include "bloom/SimpleBloomFilter.h"
#include "dna/SimpleSequence.h"
#include "tree/Tree.h"
#include <zlib.h>
#include <stdio.h>
#include "parser/kseq.h"
#include "dna/AstralSequence.h"
#include "bloom/AstralBloomFilter.h"
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <ctime>
#include <sstream>

namespace logging = boost::log;

KSEQ_INIT(gzFile, gzread)

void init() {
    logging::core::get()->set_filter
            (
                    logging::trivial::severity >= logging::trivial::info
            );
}

int main(int argc, char *argv[]) {

    init();

    long cutoff_depth = 100000000L;
    if (argc == 4) {
        std::istringstream ss(argv[3]);
        if (!(ss >> cutoff_depth)) {
            cutoff_depth = 100000000L;
        }
    }

    Tree *tree = new Tree(cutoff_depth);
    gzFile fp;
    kseq_t *seq;
    if (argc == 1) {
        fprintf(stderr, "Usage: %s <in.seq>\n", argv[0]);
        return 1;
    }
    int l;
    clock_t begin, end;
    double elapsed_secs;
    fp = gzopen(argv[1], "r");
    seq = kseq_init(fp);

    begin = clock();
    while ((l = kseq_read(seq)) >= 0) {
//        printf("seq: %s\n", seq->seq.s);
        std::string seqString = std::string(seq->seq.s);
        std::string com = std::string(seq->comment.s);
        AstralSequence *sequence = new AstralSequence(seqString, com);
        tree->insert(sequence);
    }
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "File reading and tree building: " << elapsed_secs << std::endl;


//    tree->printToFile("astral.gv");

    fp = gzopen(argv[2], "r");
    seq = kseq_init(fp);
    begin = clock();
    while ((l = kseq_read(seq)) >= 0) {
//        printf("seq: %s\n", seq->seq.s);
        std::string seqString = std::string(seq->seq.s);
        std::string com = std::string(seq->comment.s);
        AstralSequence *sequence = new AstralSequence(seqString, com);
        const std::vector<BloomFilter *> &results = tree->queryAll(sequence);
//    new AstralSequence(
//            //            std::string("slfeqlggqaavqavtaqfyaniqadatvatffngidmpnqtnktaaflcaalggpnawtgrnlkevhanmgvsnaqfttvighlrsaltgagvaaalveqtvavaetvrgdvvtv"),
//            std::string("adqllrkkrrifihsvgagtinalldclledevisqedmnkvrdendtvmdkarvlidlvtgkgpkscckfikhlceedpqlaskmglh"),
//            std::string("niente"))

        /*PRINT RESULTS*/
//        for (auto bf : results) {
//            AstralBloomFilter *abf = (AstralBloomFilter *) bf;
//            std::cout << "Found sequence with comment: " << abf->getComment() << std::endl;
//        }
    }
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Query time for given sequences: " << elapsed_secs << std::endl;

    kseq_destroy(seq);
    gzclose(fp);
    return 0;
}
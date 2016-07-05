//
// Created by luka on 5/20/16.
//

#include <boost/log/trivial.hpp>
#include "AstralBloomFilter.h"


BloomFilter *AstralBloomFilter::copy() {
//    BOOST_LOG_TRIVIAL(debug) << "Copying astral filter";
//    BOOST_LOG_TRIVIAL(debug) << "original before copying: " << std::count(_filter.begin(), _filter.end(), true);
    AstralBloomFilter *bf = new AstralBloomFilter();
    bf->_filter = std::vector<bool>(_filter);
//    BOOST_LOG_TRIVIAL(debug) << "original filter size: " << std::count(_filter.begin(), _filter.end(), true);
//    BOOST_LOG_TRIVIAL(debug) << "copy filter size: " << std::count(bf->_filter.begin(), bf->_filter.end(), true);
    bf->comment = comment;
    bf->bits = bits;
    return bf;

}


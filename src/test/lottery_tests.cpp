// Copyright (c) 2013-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "test/test_paicoin.h"
#include <boost/test/unit_test.hpp>
#include "uint256.h"
#include "stake/hash256prng.h"

BOOST_FIXTURE_TEST_SUITE(lottery_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(basic_prng)
{
    std::string strMsg = "Very deterministic message";
    uint256 hashMsg = Hash(strMsg.begin(), strMsg.end());
    auto prng = Hash256PRNG(hashMsg);

    for (int i = 0; i < 10000;++i)
        prng.Hash256Rand();
    
    auto stash = prng.StateHash();
    
}


BOOST_AUTO_TEST_SUITE_END()

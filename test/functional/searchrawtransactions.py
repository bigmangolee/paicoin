#!/usr/bin/env python3
# Copyright (c) 2019 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

"""Test the searchrawtransactions RPC commands on a setup having the 'addrindex' flag set
    - setup, generate coins and new addreses
    - make a few transactions
    - test the result of 'searchrawtransactions'
"""

from test_framework.test_framework import PAIcoinTestFramework
from test_framework.util import *

class SearchRawTransactionsTest(PAIcoinTestFramework):
    def set_test_params(self):
        self.setup_clean_chain = True
        self.num_nodes = 2
        self.extra_args = [['-addrindex'],[]]

    def logBalance(self):
        self.log.info([ self.nodes[i].getbalance() for i in range(self.num_nodes)])

    def run_test(self):
        #prepare
        self.nodes[0].generate(101)
        self.sync_all()
        self.nodes[1].generate(1)
        self.sync_all()

        self.logBalance()

        addrs = [ self.nodes[n].getnewaddress() for n in range(self.num_nodes) ]
        self.log.info(addrs)

        txids = [ self.nodes[0].sendtoaddress(addrs[1],i) for i in range(1,21) ]
        rawTxs = [ self.nodes[0].getrawtransaction(txid) for txid in txids ]
        decRawTxs = [ self.nodes[0].decoderawtransaction(rawTx) for rawTx in rawTxs ]

        self.sync_all()
        self.nodes[0].generate(1)
        self.sync_all()

        self.logBalance()

        res = self.nodes[0].searchrawtransactions(addrs[1], 1, 0)
        assert_equal(len(res), len(txids))

        res = self.nodes[0].searchrawtransactions(addrs[1], 1, 5, 2)
        assert_equal(len(res), 2)

        res = self.nodes[0].searchrawtransactions(addrs[1], 1, 19, 1)
        assert_equal(len(res), 1)
        # check if it returns the same txid as in our list 
        assert_equal(res[0]["txid"], txids[-1])
        # check several attributes to be as in our decoded element
        assert_equal(res[0]["txid"], decRawTxs[-1]["txid"])
        assert_equal(res[0]["version"], decRawTxs[-1]["version"])
        assert_equal(res[0]["size"], decRawTxs[-1]["size"])
        assert_equal(res[0]["locktime"], decRawTxs[-1]["locktime"])
        assert_equal(res[0]["vin"], decRawTxs[-1]["vin"])
        assert_equal(res[0]["vout"], decRawTxs[-1]["vout"])
        
        res = self.nodes[0].searchrawtransactions(addrs[1], 0, 2, 2)
        assert_equal(len(res), 2)

        res = self.nodes[0].searchrawtransactions(addrs[1], 0, 2)
        assert_equal(len(res), 18)

        res = self.nodes[0].searchrawtransactions(addrs[1], 0, 19, 1)
        assert_equal(len(res), 1)
        assert_equal(res[0], rawTxs[-1])

if __name__ == "__main__":
    SearchRawTransactionsTest().main()
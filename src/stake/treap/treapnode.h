#ifndef PAICOIN_STAKE_TREAPNODE_H
#define PAICOIN_STAKE_TREAPNODE_H

#include <tuple>
#include "stake/treap/value.h"
#include "uint256.h"

class TreapNode final
{
public:
    // Creates a node from the given key, value, and priority. The node is not initially linked to any others.
    TreapNode(const uint256& key, Value* value, uint32_t priority);

public:
    // Returns the (Key, Value) at the given position.
    std::tuple<uint256, Value*> getByIndex(int idx);
    // Tests whether the treap meets the min-heap invariant.
    bool isHeap();
    // Returns the size of the subtree on the left-hand side, and zero if there is no tree present there.
    uint32_t leftSize();
    // Returns the size of the subtree on the right-hand side, and zero if there is no tree present there.
    uint32_t rightSize();

private:
    uint256 key;
    Value* value;
    uint32_t priority;
    uint32_t size; // Count of items within this treap - the node itself counts as 1.
    TreapNode* left;
    TreapNode* right;
};

#endif // PAICOIN_STAKE_TREAPNODE_H

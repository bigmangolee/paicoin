#include "stake/treap/treapnode.h"


TreapNode::TreapNode(const uint256& key, Value* value, uint32_t priority) :
    key(key),
    value(value),
    priority(priority),
    size(1),
    left(nullptr),
    right(nullptr)
{
}

std::tuple<uint256, Value*> TreapNode::getByIndex(int idx)
{
//    if (idx < 0 || idx > int(t.size))
//    {
//        panic(fmt.Sprintf("getByIndex(%v) index out of bounds", idx));
//    }
//    node := t
//    for
//    {
//        if (node.left == nil)
//        {
//            if (idx == 0)
//            {
//                return node.key, node.value
//            }
//            node, idx = node.right, idx - 1
//        }
//        else
//        {
//            if (idx < int(node.left.size))
//            {
//                node = node.left
//            }
//            else if (idx == int(node.left.size))
//            {
//                return node.key, node.value
//            }
//            else
//            {
//                node, idx = node.right, idx - int(node.left.size) - 1
//            }
//        }
//    }
    return { {}, nullptr };
}

bool TreapNode::isHeap()
{
    return false;
}

uint32_t TreapNode::leftSize()
{
    return 0;
}

uint32_t TreapNode::rightSize()
{
    return 0;
}

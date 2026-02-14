# pragma once

#include <unordered_map>
namespace JaneZ {
class Stack {
public:
    int stackSize = 0;
    std::unordered_map<int, int> stackMap;

    int allocate(int size = 4) {
        stackSize += size;
        return -stackSize;
    }
};
}
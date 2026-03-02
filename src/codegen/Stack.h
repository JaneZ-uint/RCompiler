# pragma once

#include <unordered_map>
namespace JaneZ {
class Stack {
public:
    int stackSize = 0;
    std::unordered_map<int, int> stackMap;

    int allocate(int regId) {
        stackSize += 4;
        stackMap[regId] = -stackSize;
        return -stackSize;
    }

    int getOffset(int regId) {
        return stackMap[regId];
    }
};
}
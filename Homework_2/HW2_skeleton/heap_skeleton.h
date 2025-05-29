#pragma once

#include <vector>

template <typename E>
struct Comparator {
    bool operator()(const E& a, const E& b) const {
        return a < b;
    }
};

template <typename E>
class VectorCompleteTree {
private:
    std::vector<E> V; 
    .....
};

template <typename E, typename C>
class HeapPriorityQueue {
public:
    .....
};


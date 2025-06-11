#pragma once

#include <iostream>
#include <list>
#include <vector>

struct stringHash {
    std::size_t operator()(const std::string& key) const {
        std::size_t hash = 0;
        for (char c : key) {
            hash = (hash * 31) + c;
        }
        return hash;
    }
};

template <typename K, typename V>
class Entry {
...
};

template <typename K, typename V, typename H>
class HashMap {
...
};
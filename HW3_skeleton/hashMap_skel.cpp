#include "hashMap_skel.h"

#include <iostream>
#include <list>
#include <vector>

template <typename K, typename V, typename H>
HashMap<K, V, H>::HashMap(int capacity) : n(0), B(capacity) {}

...

template class HashMap<std::string, int, stringHash>;

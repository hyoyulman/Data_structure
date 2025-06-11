#include "hashMap.h" // Includes the definition of the HashMap class.

#include <iostream> // Includes iostream for standard input/output operations.
#include <list>     // Includes the std::list container.
#include <vector>   // Includes the std::vector container.

// HashMap constructor implementation: 
// Initializes the bucket array B with the given capacity and sets the number of entries n to 0. 
template <typename K, typename V, typename H>
HashMap<K, V, H>::HashMap(int capacity) : n(0), B(capacity) {} 

// size() function implementation: 
// Returns the current number of entries (n) in the HashMap. 
template <typename K, typename V, typename H>
int HashMap<K, V, H>::size() const { return n; } 

// empty() function implementation: 
// Checks if the HashMap is empty (i.e., if the number of entries is 0). 
template <typename K, typename V, typename H>
bool HashMap<K, V, H>::empty() const { return size() == 0; } 

// Iterator::operator*() implementation: 
// Returns a reference to the Entry object pointed to by the iterator. 
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Entry&
HashMap<K, V, H>::Iterator::operator*() const {
    return *ent; // Dereferences the internal entry iterator (ent) and returns the value. 
}

// Iterator::operator==() implementation: 
// Compares if two Iterator objects point to the same location. 
template <typename K, typename V, typename H>
bool HashMap<K, V, H>::Iterator::operator==(const Iterator& p) const {
    // If the bucket array pointer (ba) or the bucket iterator (bkt) are different, the iterators are not equal. 
    if (ba != p.ba || bkt != p.bkt) return false;
    // If both iterators are at the end of the bucket array, they are considered equal. 
    else if (bkt == ba->end()) return true;
    // Otherwise, equality is determined by comparing the internal entry iterators (ent). 
    else return (ent == p.ent);
}

// Iterator::operator++() implementation: 
// Advances the iterator to the next entry. 
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator& HashMap<K, V, H>::Iterator::operator++() {
    ++ent; // Move to the next entry within the current bucket. 
    if (endOfBkt(*this)) { // Check if the end of the current bucket has been reached. 
        ++bkt; // Move to the next bucket in the bucket array. 
        while (bkt != ba->end() && bkt->empty()) // Find the next non-empty bucket. 
            ++bkt;
        if (bkt == ba->end()) return *this; // If the end of the bucket array is reached, return the current iterator. 
        ent = bkt->begin(); // Set the entry iterator to the beginning of the newly found non-empty bucket. 
    }
    return *this; // Return the modified iterator itself. 
}

// end() function implementation: 
// Returns an iterator pointing to the end (past-the-end) of the HashMap. 
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::end() {
    return Iterator(B, B.end()); // Creates and returns an iterator pointing to the end of the bucket array (B). 
}

// begin() function implementation: 
// Returns an iterator pointing to the first entry in the HashMap. 
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::begin() {
    if (empty()) return end(); // If the HashMap is empty, return the end() iterator. 
    Bltor bkt = B.begin();     // Start searching from the beginning of the bucket array. 
    while (bkt->empty()) ++bkt; // Find the first non-empty bucket. 
    return Iterator(B, bkt, bkt->begin()); // Create and return an iterator pointing to the first entry of the found bucket. 
}

// finder() function implementation: 
// Finds the entry corresponding to the given key (k) and returns an iterator to its position. 
// If the key is not found, it returns an iterator to the end of the respective bucket (endOfBkt). 
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::finder(const K& k) {
    int i = hash(k) % B.size();       // Calculate the hash index (i) for the key (k) by modulo with bucket array size. 
    Bltor bkt = B.begin() + i;        // Get an iterator to the i-th bucket. 
    Iterator p(B, bkt, bkt->begin()); // Create an iterator (p) pointing to the beginning of the i-th bucket. 
    // Search for key (k) by iterating through the bucket until the end of the bucket is reached or the key is found. 
    while (!endOfBkt(p) && (*p).key() != k)
        nextEntry(p); // Advance iterator p to the next entry. 
    return p; // Return the final position (either the entry or the end of the bucket). 
}

// find() function implementation: 
// Finds the entry for the given key (k) and returns an iterator to it. 
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::find(const K& k) {
    Iterator p = finder(k); // Use the finder utility function to look for key (k). 
    if (endOfBkt(p))         // If the key was not found (i.e., p points to the end of a bucket), 
        return end();        // Return the HashMap's end() iterator. 
    else
        return p; // If the key was found, return the iterator (p) to its position. 
}

// inserter() function implementation: 
// Inserts a new entry (e) at the position pointed to by the iterator (p). 
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::inserter(const Iterator& p, const Entry& e) {
    Eltor ins = p.bkt->insert(p.ent, e); // Insert the new entry (e) before the position p.ent in p.bkt (current bucket). 
    n++; // Increment the count of entries in the HashMap by 1. 
    return Iterator(B, p.bkt, ins); // Create and return an iterator pointing to the newly inserted entry. 
}

// put() function implementation: 
// Inserts a (k, v) pair into the HashMap, or replaces the value if key (k) already exists. 
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::put(const K& k, const V& v) {
    Iterator p = finder(k); // Search for key (k) using the finder utility function. 
    if (endOfBkt(p)) { // If key (k) was not found (i.e., p points to the end of a bucket), 
        return inserter(p, Entry(k, v)); // Insert a new entry (k, v) at the end of the bucket and return its position. 
    } else { // If key (k) was found, 
        p.ent->setValue(v); // Replace the value of the existing entry (pointed to by p.ent) with the new value (v). 
        return p; // Return the position of the updated entry. 
    }
}

// eraser() function implementation: 
// Removes the entry pointed to by the iterator (p) from its bucket. 
template <typename K, typename V, typename H>
void HashMap<K, V, H>::eraser(const Iterator& p) {
    p.bkt->erase(p.ent); // Erase the entry pointed to by p.ent from its bucket (p.bkt). 
    n--; // Decrement the number of entries in the HashMap by 1. 
}

// erase(const Iterator& p) function implementation: 
// Deletes the entry pointed to by iterator p. Internally calls the eraser utility. 
template <typename K, typename V, typename H>
void HashMap<K, V, H>::erase(const Iterator& p) {
    eraser(p); // Calls the eraser function to perform the actual deletion. 
}

// erase(const K& k) function implementation: 
// Deletes the entry corresponding to the given key (k) from the map. 
template <typename K, typename V, typename H>
void HashMap<K, V, H>::erase(const K& k) {
    Iterator p = finder(k); // Find the key (k) to be erased using the finder utility function. 
    if (endOfBkt(p))         // If the key was not found (i.e., p points to the end of a bucket), 
        // throw NonexistentElement("Erase of nonexistent"); // A throw could be added here for erasing a non-existent element. (Currently commented out) 
        return; // The assignment example seems to do nothing instead of throwing an error.
    eraser(p); // If the key was found, call the eraser function to remove the entry. 
}

// Explicit instantiation of the HashMap template for std::string keys, int values, and stringHash. 
// This ensures that the code for this specific template specialization is generated,
// allowing it to be used without linking errors when the template definition is in a .cpp file.
template class HashMap<std::string, int, stringHash>; 
#pragma once // Ensures this header file is included only once.

#include <iostream> // Includes iostream for standard input/output operations.
#include <list>     // Includes std::list, which will be used for buckets in the hash table.
#include <vector>   // Includes std::vector, which will be used for the array of buckets.

// Defines a hash function structure for strings.
struct stringHash {
    // Overloads the function call operator to allow the struct to be used like a function.
    std::size_t operator()(const std::string& key) const {
        std::size_t hash = 0; // Initializes a variable to store the hash value.
        for (char c : key) { // Iterates through each character in the input key.
            hash = (hash * 31) + c; // Calculates the hash value using a simple algorithm.
        }
        return hash; // Returns the calculated hash value.
    }
};

// Template class Entry to store a key-value pair.
template <typename K, typename V>
class Entry {
public:
    // Constructor: Initializes an Entry object with a key (k) and a value (v).
    Entry(const K& k = K(), const V& v = V())
        : _key(k), _value(v) { } // Uses a member initializer list to initialize _key and _value.

    // Constant member function to return the key.
    const K& key() const { return _key; }

    // Constant member function to return the value.
    const V& value() const { return _value; }

    // Member function to set the key.
    void setKey(const K& k) { _key = k; }

    // Member function to set the value.
    void setValue(const V& v) { _value = v; }

private:
    K _key;   // Member variable to store the key of the Entry.
    V _value; // Member variable to store the value of the Entry.
};

// Template class HashMap. Takes key type (K), value type (V), and hash function type (H).
template <typename K, typename V, typename H>
class HashMap {
public:
    typedef Entry<const K, V> Entry; // Defines Entry type to represent a (key,value) pair. 

    // Declaration of the inner Iterator class for HashMap. 
    class Iterator;

public:
    // Constructor: Sets the initial capacity of the hash map's buckets. Default is 100. 
    HashMap(int capacity = 100);

    // Returns the number of entries (key-value pairs) currently stored in the hash map. 
    int size() const;

    // Returns true if the map is empty. 
    bool empty() const;

    // Finds an entry with key k and returns an iterator to it. 
    Iterator find(const K& k);

    // Inserts or replaces a (k,v) pair in the map. 
    Iterator put(const K& k, const V& v);

    // Removes an entry with key k. 
    void erase(const K& k);

    // Erases the entry at position p. 
    void erase(const Iterator& p);

    // Returns an iterator to the first entry in the map. 
    Iterator begin();

    // Returns an iterator to the end entry (past-the-end) of the map. 
    Iterator end();

protected:
    typedef std::list<Entry> Bucket;     // Defines 'Bucket' as a list to hold entries. 
    typedef std::vector<Bucket> BktArray; // Defines 'BktArray' as a vector to hold buckets. 

    // Utility functions for HashMap operations. 
    Iterator finder(const K& k);                     // Internal utility function to find a given key (k). 
    Iterator inserter(const Iterator& p, const Entry& e); // Internal utility function to insert an entry (e) before position (p). 
    void eraser(const Iterator& p);                   // Internal utility function to remove the entry pointed to by iterator (p). 

    typedef typename BktArray::iterator Bltor; // Defines Bltor as an iterator type for the bucket array. 
    typedef typename Bucket::iterator Eltor;   // Defines Eltor as an iterator type for a bucket (list). 

    // Static utility function to advance an iterator (p) to the next entry within a bucket. 
    static void nextEntry(Iterator& p) { ++p.ent; }
    // Static utility function to check if an iterator (p) has reached the end of its current bucket. 
    static bool endOfBkt(const Iterator& p) { return p.ent == p.bkt->end(); }

private:
    int n;          // The number of entries currently stored in the hash map. 
    H hash;         // The hash function object used to compare keys. 
    BktArray B;     // The bucket array where the actual data is stored. 

public:
    // Definition of the HashMap::Iterator class. 
    class Iterator {
    private:
        Eltor ent;             // The position of the entry within its bucket. 
        Bltor bkt;             // The position of the bucket within the bucket array. 
        const BktArray* ba;    // A pointer to the bucket array this iterator belongs to. 

    public:
        // Iterator constructor: Initializes the iterator with references to the bucket array (a),
        // bucket position (b), and entry position (q). 
        Iterator(const BktArray& a, const Bltor& b, const Eltor& q = Eltor())
            : ent(q), bkt(b), ba(&a) { }

        // Overloads the dereference operator to return a reference to the Entry pointed to by the iterator. 
        Entry& operator*() const;
        // Overloads the equality operator to compare if two Iterator objects point to the same location. 
        bool operator==(const Iterator& p) const;
        // Overloads the pre-increment operator to advance the iterator to the next entry. 
        Iterator& operator++();

        friend class HashMap; // Grants the HashMap class access to the private members of Iterator. 
    };
};
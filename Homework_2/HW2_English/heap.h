#pragma once // Ensures this header file is included only once per compilation unit

#include <vector> 

// Comparator template structure
template <typename E>
struct Comparator {
    // Overloads the function call operator to compare two elements.
    // Returns true if a should have higher priority than b (for a min-heap, if a < b).
    bool operator()(const E& a, const E& b) const {
        return a < b; 
    }
};

// Class representing a complete binary tree using a std::vector for storage.
template <typename E>
class VectorCompleteTree {
public:
    // Publicly accessible type alias for an iterator to elements in the tree.
    typedef typename std::vector<E>::iterator PositionIterator;
    // Publicly accessible type alias for a const_iterator to elements in the tree.
    typedef typename std::vector<E>::const_iterator ConstPositionIterator;

    // It encapsulates a PositionIterator.
    class Position {
    public:
        PositionIterator iter; // The underlying iterator

        // Constructor: Initializes the Position with a given iterator.
        Position(PositionIterator _iter) : iter(_iter) {}

        // Dereference operator: Returns a reference to the element at this position.
        E& operator*() const { return *iter; }

        // Equality operator: Checks if this Position is the same as another.
        bool operator==(const Position& other) const { return iter == other.iter; }
        // Inequality operator: Checks if this Position is different from another.
        bool operator!=(const Position& other) const { return iter != other.iter; }
    };

private:
    std::vector<E> V; // The std::vector used to store tree elements.

protected:
    // Protected utility function to map an index to a Position object.
    Position pos(int i) {
        return Position(V.begin() + i);
    }

    // Protected utility function to map a Position object back to an index.
    int idx(const Position& p) const {
        return p.iter - V.begin();
    }

public:
    // Constructor: Initializes the vector V with one element
    // This allows for 1-based indexing of heap elements, where the root is at index 1.
    VectorCompleteTree() : V(1) {}

    // Returns the number of actual elements in the tree
    int size() const {
        return V.size() - 1;
    }

    // Checks if the tree is empty.
    bool empty() const {
        return size() == 0;
    }

    // Returns the Position of the left child of a given position p.
    Position left(const Position& p) {
        return pos(2 * idx(p));
    }

    // Returns the Position of the right child of a given position p.
    Position right(const Position& p) {
        return pos(2 * idx(p) + 1);
    }

    // Returns the Position of the parent of a given position p.
    Position parent(const Position& p) {
        // Assumes idx(p)/2 is a valid index (root's parent would be index 0).
        return pos(idx(p) / 2);
    }

    // Checks if the node at position p has a left child.
    bool hasLeft(const Position& p) const {
        return 2 * idx(p) <= size();
    }

    // Checks if the node at position p has a right child.
    bool hasRight(const Position& p) const {
        return 2 * idx(p) + 1 <= size();
    }

    // Checks if the node at position p is the root of the tree.
    bool isRoot(const Position& p) const {
        return idx(p) == 1; // Root is at index 1
    }

    // Returns the Position of the root element.
    Position root() {
        return pos(1); // Root is at index 1
    }

    // Returns the Position of the last element in the tree (in level-order).
    Position last() {
        return pos(size()); // Last element is at index 'size()'
    }

    // Adds an element 'e' to the end of the tree, maintaining completeness.
    void addLast(const E& e) {
        V.push_back(e);
    }

    // Removes the last element from the tree.
    void removeLast() {
        V.pop_back();
    }

    // Swaps the elements at two given positions p and q.
    void swap(const Position& p, const Position& q) {
        E tempVal = *p; // Dereference p to get the element's value
        *p = *q;    // Assign q's element value to p's element
        *q = tempVal; // Assign original p's element value to q's element
    }
};

// Class implementing a heap-based priority queue.
// E is the element type, C is the comparator type.
template <typename E, typename C>
class HeapPriorityQueue {
public:
    // Returns the number of elements in the priority queue.
    int size() const;

    // Checks if the priority queue is empty.
    bool empty() const;

    // Inserts an element 'e' into the priority queue.
    void insert(const E& e);

    // Returns a const reference to the minimum element (highest priority).
    const E& min();

    // Removes the minimum element (highest priority) from the queue.
    void removeMin();

private:
    VectorCompleteTree<E> T; // The underlying complete binary tree used to store heap elements.
    C isLess;                // The comparator object to determine priority 

    // Type alias for a position in the underlying tree, for convenience.
    typedef typename VectorCompleteTree<E>::Position Position;
};
#include "heap.h" // Include the header file for HeapPriorityQueue and VectorCompleteTree

// Returns the number of elements in the priority queue.
template <typename E, typename C>
int HeapPriorityQueue<E, C>::size() const {
    return T.size(); 
}

// Checks if the priority queue is empty.
template <typename E, typename C>
bool HeapPriorityQueue<E, C>::empty() const {
    return T.empty();  
}

// Returns a const reference to the minimum element in the priority queue.
// For a min-heap, this is the element at the root.
template <typename E, typename C>
const E& HeapPriorityQueue<E, C>::min() {
    return *(T.root()); 
}

// Inserts an element 'e' into the priority queue and maintains the heap property.
template <typename E, typename C>
void HeapPriorityQueue<E, C>::insert(const E& e) {
    T.addLast(e);                     // Add the new element to the end of the complete tree.
    Position v = T.last();            // Get the Position of the newly added element.

    // While the current node 'v' is not the root and 'v' has higher priority
    // (is less than, for a min-heap) than its parent 'u', swap 'v' with 'u'
    // and move 'v' up to 'u's original position.
    while (!T.isRoot(v)) {
        Position u = T.parent(v);   // Get the parent of v.
        if (!isLess(*v, *u)) {    // If v is not "less than" its parent (heap order is satisfied at this edge)
            break;                  // ...stop the up-heap bubbling.
        }
        T.swap(v, u);               // Otherwise, swap the elements at v and u.
        v = u;                      // Move to the parent's position to continue bubbling up.
    }
}

// Removes the minimum element (highest priority) from the priority queue
// and maintains the heap property.
// though the T.removeLast() or T.root() might handle some cases or throw.
template <typename E, typename C>
void HeapPriorityQueue<E, C>::removeMin() {
    // If there's only one element, simply remove it.
    if (size() == 1) {
        T.removeLast();
    } else {
        Position rootPos = T.root();    // Get the Position of the root (the element to be removed).
        T.swap(rootPos, T.last());      // Swap the root element with the last element in the heap.
        T.removeLast();                 // Remove the (original) root, which is now at the last position.

        // Down-heap bubbling process:
        // The new root (which was the last element) might violate the heap property.
        // Restore the heap property by repeatedly swapping this element ('u')
        // with its child of higher priority ('v') until 'u' is in its correct place
        // or it becomes a leaf.
        Position u = T.root();          // Start down-heap bubbling from the new root.
        while (T.hasLeft(u)) {        // While 'u' has at least a left child:
            Position v = T.left(u);     // Assume the left child 'v' is the one with higher priority.
            if (T.hasRight(u) && isLess(*(T.right(u)), *v)) { // If 'u' also has a right child, and that right child
                                                              // has higher priority than the left child.
                v = T.right(u);         // then 'v' becomes the right child.
            }

            // If the chosen child 'v' has higher priority than 'u' (violating heap order)
            if (isLess(*v, *u)) {
                T.swap(u, v);           // swap 'u' and 'v'.
                u = v;                  // Move 'u' down to 'v's original position and continue bubbling.
            } else {
                break;                  // Otherwise, 'u' is in a valid heap position relative to its children; stop.
            }
        }
    }
}

// These lines ensure that the compiler generates code for HeapPriorityQueue
// with these specific template arguments (int and char elements, with the default Comparator).
template class HeapPriorityQueue<int, Comparator<int>>;
template class HeapPriorityQueue<char, Comparator<char>>;
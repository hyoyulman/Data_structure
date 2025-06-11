#include "CDList.h"

// Constructor: Initializes the list as empty by setting cursor to nullptr
CDList::CDList() : cursor(nullptr) {}

// Destructor: Deletes all nodes in the list to prevent memory leaks
CDList::~CDList() {
    while (!empty()) {
        CDNode* old = cursor->next;  // Node to delete (the one after cursor)
        if (old == cursor) {         // Only one node exists
            delete old;
            cursor = nullptr;
        } else {
            // Re-link the list to bypass the node being deleted
            cursor->next = old->next;
            old->next->prev = cursor;
            delete old;
        }
    }
}

// Checks if the list is empty (cursor is null)
bool CDList::empty() const {
    return cursor == nullptr;
}

// Returns the element at the front (right after the cursor)
const Elem& CDList::front() const {
    return cursor->next->elem;
}

// Returns the element at the back (at the cursor)
const Elem& CDList::back() const {
    return cursor->elem;
}

// Moves the cursor one node forward (clockwise direction)
void CDList::forward() {
    if (!empty()) cursor = cursor->next;
}

// Moves the cursor one node backward (counterclockwise direction)
void CDList::backward() {
    if (!empty()) cursor = cursor->prev;
}

// Inserts a new node with element e immediately after the cursor
void CDList::add(const Elem& e) {
    CDNode* v = new CDNode(e);  // Create a new node with the given element
    if (cursor == nullptr) {
        // If the list is empty, the new node points to itself
        v->next = v;
        v->prev = v;
        cursor = v;  // Cursor points to the new node
    } else {
        // Link new node between cursor and cursor->next
        v->next = cursor->next;
        v->prev = cursor;
        cursor->next->prev = v;
        cursor->next = v;
    }
}

// Removes the node immediately after the cursor
void CDList::remove() {
    if (empty()) {
        std::cout << "ERROR: cannot remove from an empty" << std::endl;
        return;
    }

    CDNode* old = cursor->next;  // Node to be deleted
    if (old == cursor) {
        // If the list has only one node, delete it and empty the list
        delete old;
        cursor = nullptr;
    } else {
        // Re-link to remove old node from the list
        cursor->next = old->next;
        old->next->prev = cursor;
        delete old;
    }
}

// Overloaded << operator to print the list in both forward and backward directions
ostream& operator<<(ostream& out, const CDList& c) {
    if (c.empty()) {
        out << "ERROR: cannot print. The list is empty" << std::endl << std::endl;
        return out;
    }

    // === Forward hopping ===
    out << "Forward hopping: ";
    CDNode* v = c.cursor->next;  // Start from the node after cursor
    do {
        if (v == c.cursor) out << v->elem << "*";  // Mark cursor position
        else out << v->elem;
        v = v->next;
        if (v != c.cursor->next) out << "->";  // Arrow between nodes
    } while (v != c.cursor->next);
    out << std::endl;

    // === Backward hopping ===
    out << "Backward hopping: ";
    v = c.cursor->prev;          // Start from the node before cursor
    CDNode* stop = v;            // Stopping point for backward traversal
    do {
        if (v == c.cursor) out << v->elem << "*";  // Mark cursor position
        else out << v->elem;
        v = v->prev;
        if (v != stop) out << "->";  // Arrow between nodes
    } while (v != stop);
    out << std::endl << std::endl;

    return out;
}

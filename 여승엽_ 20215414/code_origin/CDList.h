//--------------------<<Provided (head)>>----------------------------------
#ifndef CDLIST_H        // Prevents multiple inclusion of this header file
#define CDLIST_H

#include <iostream>     // For input/output streams
#include <string>       // For using the string type

using std::string;      // Allows using 'string' instead of 'std::string'
using std::ostream;     // Allows using 'ostream' instead of 'std::ostream'

typedef string Elem;    // Defines 'Elem' as an alias for string (easy to change type later)

//--------------------<<Provided (tail)>>----------------------------------


// Structure definition for a node in the doubly linked list
struct CDNode {
    Elem elem;          // Data stored in the node
    CDNode* next;       // Pointer to the next node
    CDNode* prev;       // Pointer to the previous node

    // Constructor to initialize a node with a given element
    CDNode(const Elem& e) : elem(e), next(nullptr), prev(nullptr) {}
};


// Class definition for a Circular Doubly Linked List
class CDList {
private:
    CDNode* cursor;     // Pointer to the current position in the list

public:
    CDList();           // Constructor: creates an empty list
    ~CDList();          // Destructor: deallocates all nodes

    bool empty() const;             // Checks if the list is empty
    const Elem& front() const;      // Returns the element after the cursor
    const Elem& back() const;       // Returns the element at the cursor

    void forward();                 // Moves the cursor forward by one node
    void backward();                // Moves the cursor backward by one node

    void add(const Elem& e);        // Inserts a new node after the cursor
    void remove();                  // Deletes the node after the cursor

    // Overloaded output operator for printing the entire list
    // Declared as a friend to allow access to private members
    friend ostream& operator<<(ostream& out, const CDList& c);
};

#endif  // CDLIST_H

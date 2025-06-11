#include "CDList_plus.h"

CDList::CDList() : cursor(nullptr) {}

CDList::~CDList() {
    while (!empty()) {
        CDNode* old = cursor->next;
        if (old == cursor) {
            delete old;
            cursor = nullptr;
        } else {
            cursor->next = old->next;
            old->next->prev = cursor;
            delete old;
        }
    }
}

bool CDList::empty() const {
    return cursor == nullptr;
}

const Elem& CDList::front() const {
    return cursor->next->elem;
}

const Elem& CDList::back() const {
    return cursor->elem;
}

void CDList::forward() {
    if (!empty()) cursor = cursor->next;
}

void CDList::backward() {
    if (!empty()) cursor = cursor->prev;
}

void CDList::add(const Elem& e) {
    CDNode* v = new CDNode(e);
    if (cursor == nullptr) {
        v->next = v;
        v->prev = v;
        cursor = v;
    } else {
        v->next = cursor->next;
        v->prev = cursor;
        cursor->next->prev = v;
        cursor->next = v;
    }
}

void CDList::addByInput() {
    std::string input;
    std::cout << "Enter an element to add: ";
    std::cin >> input;

    add(input);  
    std::cout << input << " has been added to the playlist." << std::endl << std::endl;
}

void CDList::remove() {
    if (empty()) {
        std::cout << "ERROR: cannot remove from an empty" << std::endl;
        return;
    }

    CDNode* old = cursor->next;
    if (old == cursor) {
        delete old;
        cursor = nullptr;
    } else {
        cursor->next = old->next;
        old->next->prev = cursor;
        delete old;
    }
}

bool CDList::contains(const Elem& e) const {
    if (empty()) return false;
    CDNode* v = cursor;
    do {
        if (v->elem == e) return true;
        v = v->next;
    } while (v != cursor);
    return false;
}

int CDList::length() const {
    if (empty()) return 0;
    int count = 0;
    CDNode* v = cursor;
    do {
        ++count;
        v = v->next;
    } while (v != cursor);
    return count;
}

void CDList::clear() {
    while (!empty()) {
        CDNode* old = cursor->next;
        if (old == cursor) {
            delete old;
            cursor = nullptr;
        } else {
            cursor->next = old->next;
            old->next->prev = cursor;
            delete old;
        }
    }
    return;
}

void CDList::checkByInput() {
    std::string input;
    std::cout << "Enter an element to check if it exists in the list: ";
    std::cin >> input;

    if (contains(input)) {
        std::cout << input << " is in the playlist." << std::endl;
    } else {
        std::cout << input << " is NOT in the playlist." << std::endl;
    }

    std::cout << "Current playlist length: " << length() << std::endl << std::endl;
}

ostream& operator<<(ostream& out, const CDList& c) {
    if (c.empty()) {
        out << "ERROR: cannot print. The list is empty" << std::endl << std::endl;
        return out;
    }

    // === Forward hopping ===
    out << "Forward hopping: ";
    CDNode* v = c.cursor->next;
    do {
        if (v == c.cursor) out << v->elem << "*";
        else out << v->elem;
        v = v->next;
        if (v != c.cursor->next) out << "->";
    } while (v != c.cursor->next);
    out << std::endl;

    // === Backward hopping ===
    out << "Backward hopping: ";
    v = c.cursor->prev;
    CDNode* stop = v;
    do {
        if (v == c.cursor) out << v->elem << "*";
        else out << v->elem;
        v = v->prev;
        if (v != stop) out << "->";
    } while (v != stop);
    out << std::endl << std::endl;

    return out;
}

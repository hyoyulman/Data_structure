#include "hashMap.h" // Includes the HashMap class definition.

#include <iostream> // Includes iostream for standard input/output operations.

int main() {
    HashMap<std::string, int, stringHash> map; // Creates a HashMap object using stringHash as its hash function.

    typedef HashMap<std::string, int, stringHash>::Iterator hashIter; // Defines hashIter as an alias for HashMap's Iterator type.

    map.put("apple", 100); // Inserts the key "apple" with value 100 into the map. 
    map.put("banana", 150); // Inserts the key "banana" with value 150 into the map. 
    map.put("cherry", 200); // Inserts the key "cherry" with value 200 into the map. 

    hashIter iter = map.begin(); // Gets an iterator pointing to the beginning of the map. 
    while (1) { // Starts an infinite loop. 
        if (iter == map.end()) break; // If the iterator reaches the end of the map, break the loop. 
        std::cout << (*iter).key() << ": " << (*iter).value() << ", "; // Prints the key and value pointed to by the current iterator. 
        ++iter; // Advances the iterator to the next entry. 
    }
    std::cout << std::endl; // Prints a newline character. 

    map.erase("apple"); // Deletes the entry with the key "apple" from the map. 

    iter = map.begin(); // Gets an iterator pointing to the beginning of the map again. 
    while (1) { // Starts an infinite loop. 
        if (iter == map.end()) break; // If the iterator reaches the end of the map, break the loop. 
        std::cout << (*iter).key() << ": " << (*iter).value() << ", "; // Prints the key and value pointed to by the current iterator. 
        ++iter; // Advances the iterator to the next entry. 
    }
    std::cout << std::endl; // Prints a newline character. 

    map.put("cherry", 300); // Updates the value for the key "cherry" to 300.  (If key exists, its value is replaced.)

    iter = map.begin(); // Gets an iterator pointing to the beginning of the map again. 
    while (1) { // Starts an infinite loop. 
        if (iter == map.end()) break; // If the iterator reaches the end of the map, break the loop. 
        std::cout << (*iter).key() << ": " << (*iter).value() << ", "; // Prints the key and value pointed to by the current iterator. 
        ++iter; // Advances the iterator to the next entry. 
    }
    std::cout << std::endl; // Prints a newline character. 

    iter = map.find("cherry"); // Finds the entry with the key "cherry" and gets an iterator to it. 
    map.erase(iter); // Deletes the entry pointed to by the iterator (the "cherry" entry). 
    iter = map.begin(); // Gets an iterator pointing to the beginning of the map again. 
    while (1) { // Starts an infinite loop. 
        if (iter == map.end()) break; // If the iterator reaches the end of the map, break the loop. 
        std::cout << (*iter).key() << ": " << (*iter).value() << ", "; // Prints the key and value pointed to by the current iterator. 
        ++iter; // Advances the iterator to the next entry. 
    }
    std::cout << std::endl; // Prints a newline character. 

    map.erase("banana"); // Deletes the entry with the key "banana" from the map. 
    if (map.empty()) // Checks if the map is empty. 
        std::cout << "map is empty" << std::endl; // If the map is empty, prints this message. 

    getchar(); // Pauses the console window, waiting for user input before closing.

    return 0; // Indicates successful program execution.
}
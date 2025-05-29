#include <iostream>
#include "CDList.h"

int main() {
    CDList playList;  // Create a circular doubly linked list

    std::cout << "add(SA)" << std::endl;
    playList.add("SA");               // Add "SA" to the list
    std::cout << playList << std::endl;

    std::cout << "add(LF)" << std::endl;
    playList.add("LF");               // Add "LF" to the list
    std::cout << playList << std::endl;

    std::cout << "add(JT)" << std::endl;
    playList.add("JT");               // Add "JT" to the list
    std::cout << playList << std::endl;

    std::cout << "forward()" << std::endl;
    playList.forward();               // Move the cursor one node forward
    std::cout << playList << std::endl;

    std::cout << "forward()" << std::endl;
    playList.forward();               // Move the cursor forward again
    std::cout << playList << std::endl;

    std::cout << "remove()" << std::endl;
    playList.remove();                // Remove the node right after the cursor
    std::cout << playList << std::endl;

    std::cout << "add(DI)" << std::endl;
    playList.add("DI");               // Add "DI" to the list
    std::cout << playList << std::endl;

    std::cout << "backward()" << std::endl;
    playList.backward();              // Move the cursor one node backward
    std::cout << playList << std::endl;

    std::cout << "backward()" << std::endl;
    playList.backward();              // Move the cursor backward again
    std::cout << playList << std::endl;

    std::cout << "remove()" << std::endl;
    playList.remove();                // Remove the node after the cursor
    std::cout << playList << std::endl;

    std::cout << "remove()" << std::endl;
    playList.remove();                // Remove another node
    std::cout << playList << std::endl;

    std::cout << "remove()" << std::endl;
    playList.remove();                // Remove another node
    std::cout << playList << std::endl;

    std::cout << "remove()" << std::endl;
    playList.remove();                // Remove the last remaining node (empty list)
    std::cout << playList << std::endl;

    getchar();  // Wait for key press before exiting

    return EXIT_SUCCESS;
}

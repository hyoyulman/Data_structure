#include <iostream>
#include "CDList_plus.h"
#include <limits>

int main() {
	CDList playList;

	std::cout << "add(SA)" << std::endl;
	playList.add("SA");
	std::cout << playList << std::endl;

	std::cout << "add(LF)" << std::endl;
	playList.add("LF");
	std::cout << playList << std::endl;

	std::cout << "add(JT)" << std::endl;
	playList.add("JT");
	std::cout << playList << std::endl;

	std::cout << "forward()" << std::endl;
	playList.forward();
	std::cout << playList << std::endl;

	std::cout << "forward()" << std::endl;
	playList.forward();
	std::cout << playList << std::endl;

	std::cout << "remove()" << std::endl;
	playList.remove();
	std::cout << playList << std::endl;

	std::cout << "add(DI)" << std::endl;
	playList.add("DI");
	std::cout << playList << std::endl;

	std::cout << "backward()" << std::endl;
	playList.backward();
	std::cout << playList << std::endl;

	std::cout << "backward()" << std::endl;
	playList.backward();
	std::cout << playList << std::endl;

	std::cout << "remove()" << std::endl;
	playList.remove();
	std::cout << playList << std::endl;

	std::cout << "remove()" << std::endl;
	playList.remove();
	std::cout << playList << std::endl;

	std::cout << "remove()" << std::endl;
	playList.remove();
	std::cout << playList << std::endl;

	std::cout << "remove()" << std::endl;
	playList.remove();
	std::cout << playList << std::endl;

	playList.addByInput();
	playList.addByInput();
	playList.addByInput();

	playList.checkByInput();

	playList.clear();
	std::cout << "After clear:" << std::endl;
	std::cout << playList << std::endl;

	std::cout << "Press Enter to exit...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();

	return EXIT_SUCCESS;
}
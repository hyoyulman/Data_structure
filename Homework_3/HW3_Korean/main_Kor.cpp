#include "hashMap_Kor.h" // HashMap 클래스 정의를 포함합니다. 

#include <iostream> // 표준 입출력 스트림을 사용하기 위해 포함합니다.

int main() {
    HashMap<std::string, int, stringHash> map; // stringHash 해시 함수를 사용하는 HashMap 객체를 생성합니다. 

    typedef HashMap<std::string, int, stringHash>::Iterator hashIter; // HashMap의 Iterator 타입을 hashIter로 정의합니다. 

    map.put("apple", 100); // "apple" 키에 100 값을 삽입합니다. 
    map.put("banana", 150); // "banana" 키에 150 값을 삽입합니다. 
    map.put("cherry", 200); // "cherry" 키에 200 값을 삽입합니다. 

    hashIter iter = map.begin(); // 맵의 시작을 가리키는 이터레이터를 얻습니다. 
    while (1) { // 무한 루프를 시작합니다. 
        if (iter == map.end()) break; // 이터레이터가 맵의 끝에 도달하면 루프를 종료합니다. 
        std::cout << (*iter).key() << ": " << (*iter).value() << ", "; // 현재 이터레이터가 가리키는 키와 값을 출력합니다. 
        ++iter; // 이터레이터를 다음 엔트리로 이동시킵니다. 
    }
    std::cout << std::endl; // 줄 바꿈을 출력합니다. 

    map.erase("apple"); // "apple" 키에 해당하는 엔트리를 맵에서 삭제합니다. 

    iter = map.begin(); // 맵의 시작을 가리키는 이터레이터를 다시 얻습니다. 
    while (1) { // 무한 루프를 시작합니다. 
        if (iter == map.end()) break; // 이터레이터가 맵의 끝에 도달하면 루프를 종료합니다. 
        std::cout << (*iter).key() << ": " << (*iter).value() << ", "; // 현재 이터레이터가 가리키는 키와 값을 출력합니다. 
        ++iter; // 이터레이터를 다음 엔트리로 이동시킵니다. 
    }
    std::cout << std::endl; // 줄 바꿈을 출력합니다. 

    map.put("cherry", 300); // "cherry" 키의 값을 300으로 업데이트합니다. (기존 값이 있으면 교체) 

    iter = map.begin(); // 맵의 시작을 가리키는 이터레이터를 다시 얻습니다. 
    while (1) { // 무한 루프를 시작합니다. 
        if (iter == map.end()) break; // 이터레이터가 맵의 끝에 도달하면 루프를 종료합니다. 
        std::cout << (*iter).key() << ": " << (*iter).value() << ", "; // 현재 이터레이터가 가리키는 키와 값을 출력합니다. 
        ++iter; // 이터레이터를 다음 엔트리로 이동시킵니다. 
    }
    std::cout << std::endl; // 줄 바꿈을 출력합니다. 

    iter = map.find("cherry"); // "cherry" 키에 해당하는 엔트리를 찾아 이터레이터를 얻습니다. 
    map.erase(iter); // "cherry" 키에 해당하는 엔트리를 이터레이터를 통해 삭제합니다. 
    iter = map.begin(); // 맵의 시작을 가리키는 이터레이터를 다시 얻습니다. 
    while (1) { // 무한 루프를 시작합니다. 
        if (iter == map.end()) break; // 이터레이터가 맵의 끝에 도달하면 루프를 종료합니다. 
        std::cout << (*iter).key() << ": " << (*iter).value() << ", "; // 현재 이터레이터가 가리키는 키와 값을 출력합니다. 
        ++iter; // 이터레이터를 다음 엔트리로 이동시킵니다. 
    }
    std::cout << std::endl; // 줄 바꿈을 출력합니다. 

    map.erase("banana"); // "banana" 키에 해당하는 엔트리를 맵에서 삭제합니다. 
    if (map.empty()) // 맵이 비어있는지 확인합니다. 
        std::cout << "map is empty" << std::endl; // 맵이 비어있으면 해당 메시지를 출력합니다. 

    getchar(); // 프로그램이 즉시 종료되지 않도록 사용자 입력을 기다립니다.

    return 0; // 프로그램이 성공적으로 종료되었음을 나타냅니다. 
}
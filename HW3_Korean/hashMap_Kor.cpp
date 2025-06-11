#include "hashMap_Kor.h" // HashMap 클래스 정의를 포함합니다.

#include <iostream> // 표준 입출력 스트림을 사용하기 위해 포함합니다.
#include <list>     // std::list 컨테이너를 사용하기 위해 포함합니다.
#include <vector>   // std::vector 컨테이너를 사용하기 위해 포함합니다.

// HashMap 생성자 구현:
// 주어진 용량(capacity)으로 버킷 배열 B를 초기화하고, 엔트리 개수 n을 0으로 설정합니다.
template <typename K, typename V, typename H>
HashMap<K, V, H>::HashMap(int capacity) : n(0), B(capacity) {}

// size() 함수 구현:
// 현재 해시 맵에 저장된 엔트리 개수(n)를 반환합니다.
template <typename K, typename V, typename H>
int HashMap<K, V, H>::size() const { return n; }

// empty() 함수 구현:
// 해시 맵이 비어있는지 (엔트리 개수가 0인지) 확인합니다.
template <typename K, typename V, typename H>
bool HashMap<K, V, H>::empty() const { return size() == 0; }

// Iterator::operator*() 구현:
// 이터레이터가 가리키는 Entry 객체를 참조로 반환합니다.
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Entry&
HashMap<K, V, H>::Iterator::operator*() const {
    return *ent; // 내부 엔트리 이터레이터(ent)가 가리키는 값을 역참조하여 반환합니다.
}

// Iterator::operator==() 구현:
// 두 Iterator 객체가 같은 위치를 가리키는지 비교합니다.
template <typename K, typename V, typename H>
bool HashMap<K, V, H>::Iterator::operator==(const Iterator& p) const {
    // 버킷 배열 포인터(ba)나 버킷 이터레이터(bkt)가 서로 다르면 다른 이터레이터입니다.
    if (ba != p.ba || bkt != p.bkt) return false;
    // 두 이터레이터 모두 버킷 배열의 끝을 가리키면 같은 이터레이터로 간주합니다.
    else if (bkt == ba->end()) return true;
    // 그렇지 않으면, 내부 엔트리 이터레이터(ent)가 같은지 비교하여 결정합니다.
    else return (ent == p.ent);
}

// Iterator::operator++() 구현:
// 이터레이터를 다음 엔트리로 전진시킵니다.
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator& HashMap<K, V, H>::Iterator::operator++() {
    ++ent; // 현재 버킷 내에서 다음 엔트리로 이동합니다.
    if (endOfBkt(*this)) { // 현재 버킷의 끝에 도달했는지 확인합니다.
        ++bkt; // 현재 버킷 배열에서 다음 버킷으로 이동합니다.
        while (bkt != ba->end() && bkt->empty()) // 다음 버킷이 비어있지 않거나 버킷 배열의 끝이 아닐 때까지 반복합니다.
            ++bkt; // 비어있지 않은 다음 버킷을 찾습니다.
        if (bkt == ba->end()) return *this; // 버킷 배열의 끝에 도달했으면 현재 이터레이터를 반환합니다.
        ent = bkt->begin(); // 새로 찾은 비어있지 않은 버킷의 첫 번째 엔트리로 엔트리 이터레이터를 설정합니다.
    }
    return *this; // 변경된 이터레이터 자신을 반환합니다.
}

// end() 함수 구현:
// 해시 맵의 끝(마지막 엔트리 다음)을 가리키는 이터레이터를 반환합니다.
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::end() {
    return Iterator(B, B.end()); // 버킷 배열(B)의 끝을 가리키는 이터레이터를 생성하여 반환합니다.
}

// begin() 함수 구현:
// 해시 맵의 첫 번째 엔트리를 가리키는 이터레이터를 반환합니다.
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::begin() {
    if (empty()) return end(); // 해시 맵이 비어있으면 end() 이터레이터를 반환합니다.
    Bltor bkt = B.begin();     // 버킷 배열의 시작부터 검색을 시작합니다.
    while (bkt->empty()) ++bkt; // 첫 번째 비어있지 않은 버킷을 찾을 때까지 버킷을 이동합니다.
    return Iterator(B, bkt, bkt->begin()); // 찾은 버킷의 첫 번째 엔트리를 가리키는 이터레이터를 생성하여 반환합니다.
}

// finder() 함수 구현:
// 주어진 키(k)에 해당하는 엔트리를 찾아 그 위치를 가리키는 이터레이터를 반환합니다.
// 키를 찾지 못하면 해당 버킷의 끝(endOfBkt)을 가리키는 이터레이터를 반환합니다.
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::finder(const K& k) {
    int i = hash(k) % B.size();       // 키(k)의 해시 값을 계산하고 버킷 배열 크기로 나눠 인덱스(i)를 얻습니다.
    Bltor bkt = B.begin() + i;        // 계산된 인덱스(i)에 해당하는 버킷을 가리키는 이터레이터를 얻습니다.
    Iterator p(B, bkt, bkt->begin()); // 해당 버킷의 시작 엔트리를 가리키는 이터레이터(p)를 생성합니다.
    // 현재 엔트리가 버킷의 끝이 아니거나 키(k)와 다르면 다음 엔트리로 이동하며 검색합니다.
    while (!endOfBkt(p) && (*p).key() != k)
        nextEntry(p); // 이터레이터 p를 다음 엔트리로 전진시킵니다.
    return p; // 최종적으로 찾은 위치(엔트리 또는 버킷의 끝)를 반환합니다.
}

// find() 함수 구현:
// 주어진 키(k)에 해당하는 엔트리를 찾아 이터레이터를 반환합니다.
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::find(const K& k) {
    Iterator p = finder(k); // finder 유틸리티 함수를 사용하여 키(k)를 찾습니다.
    if (endOfB(p))         // finder가 버킷의 끝을 반환했다면, 키를 찾지 못한 것입니다.
        return end();        // 이 경우, 해시 맵의 end() 이터레이터를 반환합니다.
    else
        return p; // 키를 찾았다면, 해당 엔트리를 가리키는 이터레이터(p)를 반환합니다.
}

// inserter() 함수 구현:
// 주어진 이터레이터(p) 위치에 새로운 엔트리(e)를 삽입합니다.
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::inserter(const Iterator& p, const Entry& e) {
    Eltor ins = p.bkt->insert(p.ent, e); // p.bkt(현재 버킷)의 p.ent(현재 엔트리) 앞에 새로운 엔트리(e)를 삽입합니다.
    n++; // 해시 맵의 엔트리 개수를 1 증가시킵니다.
    return Iterator(B, p.bkt, ins); // 새로 삽입된 엔트리를 가리키는 이터레이터를 생성하여 반환합니다.
}

// put() 함수 구현:
// (k, v) 쌍을 해시 맵에 삽입하거나, 키(k)가 이미 존재하면 값을(v)로 교체합니다.
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::put(const K& k, const V& v) {
    Iterator p = finder(k); // finder 유틸리티 함수를 사용하여 키(k)를 검색합니다.
    if (endOfBkt(p)) { // 키(k)를 찾지 못했다면 (즉, p가 버킷의 끝을 가리킨다면)
        return inserter(p, Entry(k, v)); // 새로운 엔트리(k, v)를 삽입하고 그 위치를 반환합니다.
    } else { // 키(k)를 찾았다면
        p.ent->setValue(v); // 해당 엔트리(p가 가리키는)의 값을 새로운 값(v)으로 교체합니다.
        return p; // 업데이트된 엔트리의 위치를 반환합니다.
    }
}

// eraser() 함수 구현:
// 주어진 이터레이터(p)가 가리키는 엔트리를 버킷에서 제거합니다.
template <typename K, typename V, typename H>
void HashMap<K, V, H>::eraser(const Iterator& p) {
    p.bkt->erase(p.ent); // 이터레이터 p가 속한 버킷(p.bkt)에서 p.ent가 가리키는 엔트리를 제거합니다.
    n--; // 해시 맵의 엔트리 개수를 1 감소시킵니다.
}

// erase(const Iterator& p) 함수 구현:
// 이터레이터 p가 가리키는 엔트리를 삭제합니다. 내부적으로 eraser 유틸리티를 호출합니다.
template <typename K, typename V, typename H>
void HashMap<K, V, H>::erase(const Iterator& p) {
    eraser(p); // eraser 함수를 호출하여 실제 삭제를 수행합니다.
}

// erase(const K& k) 함수 구현:
// 주어진 키(k)에 해당하는 엔트리를 맵에서 삭제합니다.
template <typename K, typename V, typename H>
void HashMap<K, V, H>::erase(const K& k) {
    Iterator p = finder(k); // finder 유틸리티 함수를 사용하여 삭제할 키(k)를 찾습니다.
    if (endOfBkt(p))         // 키를 찾지 못했다면 (p가 버킷의 끝을 가리킨다면)
        // throw NonexistentElement("Erase of nonexistent"); // 존재하지 않는 요소 삭제 시 예외를 던질 수 있습니다. (현재는 주석 처리됨)
        return; // 과제 예시에서는 에러를 던지는 대신 아무것도 하지 않는 것으로 보입니다.
    eraser(p); // 키를 찾았다면, eraser 함수를 호출하여 해당 엔트리를 제거합니다.
}

// HashMap<std::string, int, stringHash> 템플릿 명시적 인스턴스화:
// 컴파일러가 std::string 키와 int 값을 사용하는 HashMap과 stringHash 해시 함수를 위한 코드를 생성하도록 명시적으로 지시합니다.
// 이를 통해 템플릿 정의가 .cpp 파일에 있어도 링크 에러 없이 사용할 수 있게 됩니다.
template class HashMap<std::string, int, stringHash>;
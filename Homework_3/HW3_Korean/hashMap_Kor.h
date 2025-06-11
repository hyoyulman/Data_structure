#pragma once // 이 헤더 파일이 한 번만 포함되도록 합니다.

#include <iostream> // 표준 입출력 스트림을 사용하기 위해 포함합니다.
#include <list>     // 해시 테이블의 버킷으로 사용될 std::list를 포함합니다.
#include <vector>   // 해시 테이블의 버킷 배열로 사용될 std::vector를 포함합니다.

// 문자열을 해시 값으로 변환하는 해시 함수 구조체입니다.
struct stringHash {
    // 함수 호출 연산자 오버로딩을 통해 함수처럼 동작하게 합니다.
    std::size_t operator()(const std::string& key) const {
        std::size_t hash = 0; // 해시 값을 저장할 변수를 초기화합니다.
        for (char c : key) { // 입력 키의 각 문자를 순회합니다.
            hash = (hash * 31) + c; // 간단한 해시 알고리즘을 사용하여 해시 값을 계산합니다.
        }
        return hash; // 계산된 해시 값을 반환합니다.
    }
};

// 키(K)와 값(V) 쌍을 저장하는 Entry 클래스 템플릿입니다.
template <typename K, typename V>
class Entry {
public:
    // 생성자: 키(k)와 값(v)으로 Entry 객체를 초기화합니다.
    Entry(const K& k = K(), const V& v = V())
        : _key(k), _value(v) { } // 멤버 초기화 리스트를 사용하여 _key와 _value를 초기화합니다.

    // 키를 반환하는 상수 멤버 함수입니다.
    const K& key() const { return _key; }

    // 값을 반환하는 상수 멤버 함수입니다.
    const V& value() const { return _value; }

    // 키를 설정하는 멤버 함수입니다.
    void setKey(const K& k) { _key = k; }

    // 값을 설정하는 멤버 함수입니다.
    void setValue(const V& v) { _value = v; }

private:
    K _key;   // Entry의 키를 저장하는 멤버 변수입니다.
    V _value; // Entry의 값을 저장하는 멤버 변수입니다.
};

// 해시 맵 HashMap 클래스 템플릿입니다. 키(K), 값(V), 해시 함수(H) 타입을 받습니다.
template <typename K, typename V, typename H>
class HashMap {
public:
    typedef Entry<const K, V> Entry; // (키, 값) 쌍을 나타내는 Entry 타입을 정의합니다.

    // HashMap의 내부 이터레이터 클래스 선언입니다.
    class Iterator;

public:
    // 생성자: 해시 맵의 초기 버킷 용량을 설정합니다. 기본값은 100입니다.
    HashMap(int capacity = 100);

    // 해시 맵에 저장된 엔트리(키-값 쌍)의 개수를 반환합니다.
    int size() const;

    // 해시 맵이 비어있는지 여부를 반환합니다.
    bool empty() const;

    // 주어진 키(k)에 해당하는 엔트리를 찾아 이터레이터를 반환합니다.
    Iterator find(const K& k);

    // (k, v) 쌍을 삽입하거나, 키(k)가 이미 존재하면 값을(v)로 교체합니다.
    Iterator put(const K& k, const V& v);

    // 주어진 키(k)에 해당하는 엔트리를 삭제합니다.
    void erase(const K& k);

    // 주어진 이터레이터(p)가 가리키는 엔트리를 삭제합니다.
    void erase(const Iterator& p);

    // 해시 맵의 첫 번째 엔트리를 가리키는 이터레이터를 반환합니다.
    Iterator begin();

    // 해시 맵의 끝을 가리키는 이터레이터를 반환합니다. (범위를 벗어난 이터레이터)
    Iterator end();

protected:
    typedef std::list<Entry> Bucket;     // 엔트리들을 담는 리스트인 '버킷' 타입을 정의합니다.
    typedef std::vector<Bucket> BktArray; // 버킷들을 담는 벡터인 '버킷 배열' 타입을 정의합니다.

    // HashMap 내부에서 사용되는 유틸리티 함수들입니다.
    Iterator finder(const K& k);                     // 주어진 키(k)를 찾는 내부 유틸리티 함수입니다.
    Iterator inserter(const Iterator& p, const Entry& e); // 주어진 이터레이터(p) 위치에 엔트리(e)를 삽입하는 내부 유틸리티 함수입니다.
    void eraser(const Iterator& p);                   // 주어진 이터레이터(p)가 가리키는 엔트리를 삭제하는 내부 유틸리티 함수입니다.

    typedef typename BktArray::iterator Bltor; // 버킷 배열의 이터레이터 타입을 정의합니다.
    typedef typename Bucket::iterator Eltor;   // 버킷(list)의 이터레이터 타입을 정의합니다.

    // 이터레이터(p)를 다음 엔트리로 이동시키는 정적 유틸리티 함수입니다.
    static void nextEntry(Iterator& p) { ++p.ent; }
    // 이터레이터(p)가 현재 버킷의 끝에 도달했는지 확인하는 정적 유틸리티 함수입니다.
    static bool endOfBkt(const Iterator& p) { return p.ent == p.bkt->end(); }

private:
    int n;          // 해시 맵에 현재 저장된 엔트리의 개수입니다.
    H hash;         // 키를 해시 값으로 변환하는 해시 함수 객체입니다.
    BktArray B;     // 실제 데이터가 저장되는 버킷 배열입니다.

public:
    // HashMap::Iterator 클래스 정의입니다.
    class Iterator {
    private:
        Eltor ent;             // 현재 이터레이터가 가리키는 버킷 내의 엔트리 위치입니다.
        Bltor bkt;             // 현재 이터레이터가 속한 버킷의 위치입니다.
        const BktArray* ba;    // 이 이터레이터가 속한 버킷 배열의 포인터입니다.

    public:
        // Iterator 생성자: 버킷 배열(a), 버킷(b), 엔트리(q) 위치를 받아 이터레이터를 초기화합니다.
        Iterator(const BktArray& a, const Bltor& b, const Eltor& q = Eltor())
            : ent(q), bkt(b), ba(&a) { }

        // 이터레이터가 가리키는 엔트리를 참조로 반환합니다.
        Entry& operator*() const;
        // 두 이터레이터가 같은 위치를 가리키는지 비교합니다.
        bool operator==(const Iterator& p) const;
        // 이터레이터를 다음 엔트리로 전진시킵니다.
        Iterator& operator++();

        friend class HashMap; // HashMap 클래스가 Iterator의 private 멤버에 접근할 수 있도록 허용합니다.
    };
};
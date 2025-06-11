#pragma once

#include <vector>

// 비교자 템플릿 (제공된 대로)
template <typename E>
struct Comparator {
    bool operator()(const E& a, const E& b) const {
        return a < b; // 최소 힙을 위한 표준 "보다 작음" 비교 
    }
};

// VectorCompleteTree 클래스
template <typename E>
class VectorCompleteTree {
public:
    // 공개적으로 접근 가능한 타입
    typedef typename std::vector<E>::iterator PositionIterator; // 위치를 위한 반복자
    typedef typename std::vector<E>::const_iterator ConstPositionIterator; // 위치를 위한 const 반복자

    // Position을 위한 중첩 구조체 또는 클래스 사용 (반복자 캡슐화)
    // 이를 통해 Position이 트리 내 특정 개념임을 명확히 함
    class Position {
    public:
        PositionIterator iter; // PositionIterator는 std::vector<E>::iterator 입니다.
        Position(PositionIterator _iter) : iter(_iter) {}

        // 이 부분을 수정합니다: operator*()를 const 멤버 함수로 만듭니다.
        // Position 객체가 const일 때도 호출 가능하며,
        // iter가 가리키는 값에 대한 참조(E&)를 반환합니다.
        E& operator*() const { return *iter; } // const 추가

        bool operator==(const Position& other) const { return iter == other.iter; }
        bool operator!=(const Position& other) const { return iter != other.iter; }
    };

private:
    std::vector<E> V; // 트리 요소를 저장하는 벡터 

protected:
    // 보호된 유틸리티 함수
    // 인덱스를 Position 객체로 매핑
    Position pos(int i) { 
        // PDF는 V(1) 생성자가 초기에 크기 1 (더미 노드)을 의미하는 것으로 보임.
        // 실제 데이터 범위 밖에 있는 i인 경우 오류 또는 특별 처리를 보장.
        return Position(V.begin() + i);
    }

    // Position 객체를 인덱스로 매핑
    int idx(const Position& p) const { 
        return p.iter - V.begin();
    }

public:
    // 생성자: 1기반 인덱싱을 따르는 경우 인덱스 0에 더미 요소로 초기화
    VectorCompleteTree() : V(1) {} // V[0]은 더미 노드, 트리 요소는 인덱스 1에서 시작 

    // 트리의 실제 요소 수
    int size() const {
        return V.size() - 1; // 인덱스 0의 더미 노드 제외 
    }

    // 트리가 비어있는지 확인
    bool empty() const {
        return size() == 0;
    }

    // 왼쪽 자식의 위치 가져오기
    Position left(const Position& p) { 
        return pos(2*idx(p));
    }

    // 오른쪽 자식의 위치 가져오기
    Position right(const Position& p) { 
        return pos(2*idx(p) + 1);
    }

    // 부모의 위치 가져오기
    Position parent(const Position& p) { 
        return pos(idx(p) / 2);
    }

    // 노드에 왼쪽 자식이 있는지 확인
    bool hasLeft(const Position& p) const { 
        return 2 * idx(p) <= size();
    }

    // 노드에 오른쪽 자식이 있는지 확인
    bool hasRight(const Position& p) const { 
        return 2 * idx(p) + 1 <= size();
    }

    // 노드가 루트인지 확인
    bool isRoot(const Position& p) const { 
        return idx(p) == 1;
    }

    // 루트 요소의 위치 가져오기
    Position root() { 
        return pos(1); // 루트는 인덱스 1에 위치
    }

    // 마지막 요소의 위치 가져오기
    Position last() { 
        return pos(size()); // 마지막 요소는 인덱스 size()에 위치
    }

    // 트리 끝에 요소 추가 (완전성 유지)
    void addLast(const E& e) { 
        V.push_back(e);
    }

    // 트리에서 마지막 요소 제거
    void removeLast() {
        V.pop_back();
    }

    // 주어진 두 위치의 요소 교환
    void swap(const Position& p, const Position& q) { 
        E e = *p;
        *p = *q;
        *q = e;
    }
};

// HeapPriorityQueue 클래스
template <typename E, typename C>
class HeapPriorityQueue {
public:
    // 우선순위 큐의 요소 수
    int size() const; 

    // 우선순위 큐가 비어있는지 확인
    bool empty() const; 

    // 우선순위 큐에 요소 삽입
    void insert(const E& e); 

    // 최소 요소 가져오기 (최소 힙의 경우 가장 높은 우선순위)
    const E& min(); 

    // 최소 요소 제거
    void removeMin(); 

private:
    VectorCompleteTree<E> T; // 힙 요소를 저장하는 완전 이진 트리 
    C isLess;                // 우선순위를 정의하는 비교자 (예: 최소 힙의 경우 "보다 작음") 

    // 트리 위치 타입을 위한 바로가기
    typedef typename VectorCompleteTree<E>::Position Position; 
};
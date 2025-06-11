#include "heap.h"

// 우선순위 큐의 요소 수를 반환합니다.
template <typename E, typename C>
int HeapPriorityQueue<E, C>::size() const { 
    return T.size(); // 내부 VectorCompleteTree의 size에 위임
}

// 우선순위 큐가 비어 있으면 true, 그렇지 않으면 false를 반환합니다.
template <typename E, typename C>
bool HeapPriorityQueue<E, C>::empty() const { // 
    return T.empty(); // 또는 return size() == 0;
}

// 우선순위 큐에서 최소 요소에 대한 상수 참조를 반환합니다.
template <typename E, typename C>
const E& HeapPriorityQueue<E, C>::min() { // 
    // 최소 힙에서 최소 요소는 항상 루트에 있습니다.
    return *(T.root()); // 루트 요소에 대한 참조 반환 
}

// 우선순위 큐에 요소를 삽입하고 힙 속성을 유지합니다.
template <typename E, typename C>
void HeapPriorityQueue<E, C>::insert(const E& e) { // 
    T.addLast(e);                     // 새 요소를 트리의 끝에 추가 
    Position v = T.last();            // 새로 추가된 요소의 위치 가져오기 


    // 상향식 힙 재구성 (up-heap bubbling):
    // 현재 노드 v가 루트가 아니고 v가 부모보다 작으면 (최소 힙의 경우)
    // v를 부모와 교환하고 위로 이동합니다.
    while (!T.isRoot(v)) { // 
        Position u = T.parent(v);   // v의 부모 가져오기 
        if (!isLess(*v, *u)) {    // v가 부모보다 작지 않으면 (힙 순서 만족) 
            break;                  // 상향식 재구성 중지
        }
        T.swap(v, u);               // 그렇지 않으면 v와 부모 교환 
        v = u;                      // 부모 위치로 이동하여 계속
    }
}

// 우선순위 큐에서 최소 요소를 제거하고 힙 속성을 유지합니다.
// 큐가 비어 있으면 std::logic_error를 발생시킵니다.
template <typename E, typename C>
void HeapPriorityQueue<E, C>::removeMin() { // 
    if (size() == 1) { // [cite: 30]
        T.removeLast(); // 요소가 하나만 있으면 그냥 제거 
    } else {
        Position rootPos = T.root();    // 루트 위치 가져오기 
        T.swap(rootPos, T.last());      // 루트를 마지막 요소와 교환 
        T.removeLast();                 // (원래) 루트였던 마지막 요소 제거 

        // 하향식 힙 재구성 (down-heap bubbling):
        Position u = T.root();          // 새 루트에서 하향식 재구성 시작
        while (T.hasLeft(u)) {        // u에 적어도 왼쪽 자식이 있는 동안 
            Position v = T.left(u);     // 왼쪽 자식이 더 작다고 가정 
            if (T.hasRight(u) && isLess(*(T.right(u)), *v)) { // 오른쪽 자식이 존재하고 더 작으면 
                v = T.right(u);         // 오른쪽 자식 선택 
            }

            // 더 작은 자식 v가 u보다 작으면 (힙 순서 위반)
            if (isLess(*v, *u)) {     // 
                T.swap(u, v);           // u와 v 교환 
                u = v;                  // v의 위치로 내려가서 계속 재구성 
            } else {
                break;                  // 힙 순서 만족, 하향식 재구성 중지 
            }
        }
    }
}

// 명시적 템플릿 인스턴스화 (원본 파일에 제공된 대로)
template class HeapPriorityQueue<int, Comparator<int>>; 
template class HeapPriorityQueue<char, Comparator<char>>; 
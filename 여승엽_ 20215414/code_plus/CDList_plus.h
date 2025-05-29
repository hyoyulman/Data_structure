#ifndef CDLIST_H       
#define CDLIST_H

#include <iostream>     
#include <string>       

using std::string;      
using std::ostream;     

typedef string Elem;    


struct CDNode {
    Elem elem;          
    CDNode* next;       
    CDNode* prev;       
    CDNode(const Elem& e) : elem(e), next(nullptr), prev(nullptr) {}
};

class CDList {
private:
    CDNode* cursor;     

public:
    CDList();           
    ~CDList();          

    bool empty() const;            
    const Elem& front() const;      
    const Elem& back() const;      

    void forward();                 
    void backward();                 

    void add(const Elem& e);        
    void remove();                  


    void addByInput();
    void checkByInput();
    bool contains(const Elem& e) const;
    int length() const;
    void clear();


    friend ostream& operator<<(ostream& out, const CDList& c);
};

#endif  

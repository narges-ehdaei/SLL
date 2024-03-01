#ifndef SLL_H
#define SLL_H

#include <stdexcept>
#include <cstdlib>      
#include <ctime>        
#include <vector>
#include <iostream>

// class prototype
template <typename T>
class SLL;

template <typename T>
class Iterator;

// Class Node
template <typename T>
class Node {
public:
    Node() {
        next = nullptr;
    }
    Node(T info, Node<T>* link = nullptr) {
        data = info;
        next = link;
    }
    /* Class SLL and Iterator can access all private data members and functions of Node*/
    friend class SLL<T>;
    friend class Iterator<T>;
private:
    T data;
    Node <T>* next;
};

// class Iterator
template<typename T>
class Iterator {
public:
    Iterator(Node<T>* p) {
        current = p;
    }
    Iterator next() {
        current = current->next;
        return *this;
    }
    T content() {
        return current->data;
    }
    bool isEqual(const Iterator<T>& itr) const {
        return current == itr.current;
    }

    bool operator==(const Iterator<T>& itr) const {
        return isEqual(itr);
    }

    bool operator!=(const Iterator<T>& itr) const {
        return !isEqual(itr);
    }

    Iterator operator++() {
        return next();
    }

    T& operator*() {
        return current->data;
    }
    Node<T>* getNext() const {
        return current->next;
    }
    /* Class SLL can access all private and protected items of Iterator */
    friend class SLL<T>;
private:
    Node<T>* current;
};

// class SLL
template<typename T>
class SLL {
public:
    SLL() {
        head = tail = nullptr;
        size = 0;

        unsigned seed = time(NULL);     // assigns current time to seed
        srand(seed);                    // seed random number generator
    }
    ~SLL() {
        for (Node<T>* tmp; head != nullptr; ) {
            tmp = head;
            head = head->next;
            delete tmp;
            tmp = nullptr;
        }
    }
    void addFirst(T info);
    void addLast(T info);
    void add(Iterator<T> p, T info);
    T removeFirst() throw (std::runtime_error);
    T removeLast() throw (std::runtime_error);
    bool remove(T target) throw (std::runtime_error);
    void remove(Iterator<T> p) throw (std::runtime_error);   
    bool contains(T target) const throw (std::runtime_error);  
    Node<T> getObject(int i) const throw (std::runtime_error);
    T getInfo(int i) const throw (std::runtime_error);
    long getSize() const;
    Iterator<T> begin()const;
    Iterator<T> end()const;
    void setHead(Node<T>* h);
    void setTail(Node<T>* t);

    friend class Iterator<T>;
private:
    Node<T>* head;
    Node<T>* tail;
    long size;
};
template<typename T>
long SLL<T>::getSize() const {               // changed to const, as it is a getter function
    return size;
}

template<typename T>
void SLL<T>::addFirst(T info) {
    size++;
    Node<T>* temp;
    if (head == nullptr) { //special case
        temp = new Node<T>(info, nullptr);
        head = tail = temp;
    }
    else {
        temp = new Node<T>(info, head);
        head = temp;
    }
}

template<typename T>
void SLL<T>::addLast(T info) {
    Node<T>* temp = new Node<T>(info, nullptr);
    if (head == nullptr) //special case
        head = tail = temp;
    else {
        tail->next = temp;
        tail = temp;
    }
    size++;
}

//inserts a node after the given node
template<typename T>
void SLL<T>::add(Iterator<T> p, T info) {
    if (p.isEqual(tail))
        addLast(info);
    else {
        Node<T>* next = (p.current)->next;
        Node<T>* newNode = new Node<T>(info, next);
        (p.current)->next = newNode;
        size++;
    }
}

template<typename T>
T SLL<T>::removeFirst() throw (std::runtime_error) {
    if (head == nullptr)
        throw std::runtime_error("empty list!");
    Node<T>* temp = head;
    head = head->next;
    if (head == nullptr) //Special Case
        tail = nullptr;
    T info = temp->data;
    delete temp;
    temp = nullptr;
    size--;
    return info;
}

template<typename T>
T SLL<T>::removeLast()throw (std::runtime_error) {
    if (head == nullptr)
        throw std::runtime_error("empty list!");
    Node<T>* tmp = head;
    Node<T>* last = tail;
    if (head->next == nullptr)  //special case - list of one node
        head = tail = nullptr;
    else {   //list with more than one node
        for (int i = 0; i < size - 2; i++)     //finding the node before last node
            tmp = tmp->next;
        tail = tmp;
        tail->next = nullptr;
    }
    T info = last->data;
    delete last;
    last = nullptr; //optional, since the scope of last is bounded to this function
    size--;
    return info;
}

//removes the first occurrence of target and returns true.
//if target doesn't exist, it returns false
template<typename T>
bool SLL<T>::remove(T target) throw (std::runtime_error) {
    if (head == nullptr) // list is empty
        throw std::runtime_error("empty list!");
    Node<T>* prev = nullptr;
    Node<T>* tmp = head;
    while (tmp != nullptr) {
        if (tmp->data == target) {
            if (tmp == head)
                head = tmp->next;
            else
                prev->next = tmp->next;
            if (tmp == tail)
                tail = prev;
            delete tmp;
            tmp = nullptr;
            --size;
            return true;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return false;
}

template<typename T>
void SLL<T>::remove(Iterator<T> p) throw (std::runtime_error) { 
    if (p == nullptr) // list is empty
        throw std::runtime_error("empty list!");
    Node<T>* prev = nullptr;
    Node<T>* current = head;
    Node<T>* next;
    bool isFound = false;
    while (current != nullptr) {
        next = current->next;
        //        if(current->data == p.content()) {
        if (p.isEqual(current)) {
            isFound = true;
            if (current == head)                    //removing head. reassign head to next node
                head = current->next;
            else
                prev->next = current->next;        // creating link between previous node and next node
            if (current == tail)                    // removing tail. Set tail to prev.
                tail = prev;
            delete current;
            current = nullptr;
            size--;
        }
        prev = current;
        current = next;

    }
    if (!isFound)
        throw std::runtime_error("Node not found in list!");
}

template<typename T>
bool SLL<T>::contains(T target) const   throw (std::runtime_error) {   
    if (head == nullptr)
        throw std::runtime_error("List is empty!");
    Node<T>* current = head;
    while (current != nullptr) {
        if (current->data == target)
            return true;
        current = current->next;
    }
    return false;
}

//returns the node in i-th position of the list
template<typename T>
Node<T> SLL<T>::getObject(int index) const throw (std::runtime_error) {
    if (index < 0 || index > size - 1)
        throw std::runtime_error("Index out of range");
    Node<T>* current = head;
    for (int i = 0; i < index; i++)
        current = current->next;
    return *current;
}

//returns the information in i-th position of the list (type T)
template<typename T>
T SLL<T>::getInfo(int index) const throw (std::runtime_error) {
    if (index < 0 || index > size - 1)
        throw std::runtime_error("Index out of range");
    Node<T>* current = head;
    for (int i = 0; i < index; i++)
        current = current->next;
    return current->data;
}

template<typename T>
Iterator<T> SLL<T>::begin() const {
    return Iterator<T>(head);
}

template<typename T>
Iterator<T> SLL<T>::end()const {
    return Iterator<T>(tail->next);
}
template<typename T>
void SLL<T>::setHead(Node<T>* h) {
    head = h;
}
template<typename T>
void SLL<T>::setTail(Node<T>* t) {
    tail = t;
}

SLL<int> genSLL(int n) {                // Part a - generates & returns linked list of random integers
    SLL<int> list;
    for (int i = 0; i < n; i++) {
        int dataToInsert = rand() % 100;
        list.addLast(dataToInsert);
    }
    return list;
}

SLL<int> genSLL(const std::vector<int>& list) {     // part b - receives a vector, generates & returns SSL
    SLL<int> newList;
    for (int element : list) {
        newList.addLast(element);
    }
    return newList;
}

template<typename T>
void printSLL(const SLL<int>& list) {            // part c - prints out linked list from head to tail
    for (Iterator<T> itr = list.begin(); !itr.isEqual(list.end()); itr.next())
        std::cout << itr.content() << "\t";
}

void sort(SLL<int>& list) {                          // part d - sorts the list in ascending order using bubble sort
    bool isSorted = false;
    for (Iterator<int> decrement = list.end(); !decrement.isEqual(list.begin()) && !isSorted; ) {
        isSorted = true;
        Iterator<int> itr = list.begin();
        Iterator<int> next = itr.getNext();
        for (; next != nullptr && !next.isEqual(list.end()); itr.next(), next.next()) {
            if (itr.content() > next.content()) {
                if (itr == list.begin()) {               // swapping 1st and 2nd nodes
                    list.addFirst(next.content());
                    list.remove(next);
                    next = itr;
                    itr = list.begin();
                }
                else {
                    list.add(next, itr.content());
                    list.remove(itr);
                    itr = next;
                    next.next();
                }
                isSorted = false;
            }
        }
        decrement = next;
    }
}
SLL<int> merge(const SLL<int>& list1, const SLL<int>& list2) {      // Receives two sorted linked lists and merges them
    SLL<int> list;
    Iterator<int> itr1 = list1.begin(), itr2 = list2.begin();
    while (itr1 != nullptr && itr2 != nullptr) {
        if (itr1.content() < itr2.content()) {
            list.addLast(itr1.content());
            itr1.next();
        }
        else {
            list.addLast(itr2.content());
            itr2.next();
        }
    }
    while (itr1 != nullptr) {        // reached end of list2, transfer rest of contents from list1
        list.addLast(itr1.content());
        itr1.next();
    }
    while (itr2 != nullptr) {         // reached end of list1, transfer rest of contents from list2
        list.addLast(itr2.content());
        itr2.next();
    }

    return list;
}
#endif
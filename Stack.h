#ifndef STACK_H
#define STACK_H

#include <iostream>

namespace cop4530 {

template <typename T>
class Stack {
public:
    Stack();
    ~Stack();
    Stack(const Stack<T>& duplicate);
    Stack(Stack<T>&& duplicate);
    Stack<T>& operator=(const Stack<T>& duplicate);
    Stack<T>& operator=(Stack<T>&& duplicate);
    bool empty() const;
    void clear();
    void push(const T& x);
    void push(T&& x);
    void pop();
    T& top();
    const T& top() const;
    int size() const;
    void print(std::ostream& os, char ofc = ' ') const;

private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d = T{}, Node* n = nullptr) : data{d}, next{n} {}
        Node(T&& d, Node* n = nullptr) : data{std::move(d)}, next{n} {}
    };

    Node* topNode;
    int NodeSize;
};
} 

#include "Stack.hpp"
#endif 

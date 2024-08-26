#include "Stack.h"

namespace cop4530 {

// ***********************************************************************
// * Function Name: Stack<T>::Stack()                                     *
// * Description: Default constructor. Initializes a empty stack          *
// *                                                                      *
// * Parameter Description: None                                          *
// * Date: 6/18/2024                                                      *
// * Author: Dallas Toth                                                  *
// * References: None                                                     *
// ***********************************************************************
template <typename T>
Stack<T>::Stack() : topNode{nullptr}, NodeSize{0} {
    
}

// ***********************************************************************
// * Function Name: Stack<T>::~Stack()                                    *
// * Description: Destructor, clears all the elements                     *
// *                                                                      *
// * Parameter Description: None                                          *
// * Date: 6/18/2024                                                      *
// * Author: Dallas Toth                                                  *
// * References: None                                                     *
// ***********************************************************************
template <typename T>
Stack<T>::~Stack() {
    clear();
}

// ***********************************************************************
// * Function Name: Stack<T>::Stack(const Stack<T>& duplicate)            *
// * Description: Copy constructor Copies all elements from another stack *
// *                                                                      *
// * Parameter Description:                                               *
// * - const Stack<T>& duplicate: other stack object copied               *
// * Date: 6/18/2024                                                      *
// * Author: Dallas Toth                                                  *
// * References: None                                                     *
// ***********************************************************************
template <typename T>
Stack<T>::Stack(const Stack<T>& duplicate) : topNode{nullptr}, NodeSize{0} {
    Node* temp = duplicate.topNode;
    Stack<T>tempStack;
    
    while (temp) {
        tempStack.push(temp -> data);
        temp = temp -> next;
    }
    while (!tempStack.empty()) {
        push(tempStack.top());
        tempStack.pop();
    }
}

    // ***********************************************************************
    // * Function Name: Stack<T>::Stack(Stack<T>&& duplicate)                 *
    // * Description: Move constructor. Moves all elements from another stack *
    // *                                                                      *
    // * Parameter Description:                                               *
    // * - Stack<T>&& duplicate: Rvalue reference to another stack            *
    // * Date: 6/18/2024                                                      *
    // * Author: Dallas Toth                                                  *
    // * References: None                                                     *
    // ***********************************************************************
    template <typename T>
    Stack<T>::Stack(Stack<T>&& duplicate) : topNode(nullptr), NodeSize(0) {
        topNode = duplicate.topNode;
        NodeSize = duplicate.NodeSize;

        duplicate.topNode = nullptr;
        duplicate.NodeSize = 0;
    }

    // ***********************************************************************
    // * Function Name: Stack<T>& Stack<T>::operator=(const Stack<T>& duplicate) *
    // * Description: Assignment operator. Copies elements from another stack *
    // *                                                                      *
    // * Parameter Description:                                               *
    // * - const Stack<T>& duplicate: another stack object to be copied from  *
    // *                                                                      *
    // * Returns: current stack object after assignment                       *
    // * Date: 6/18/2024                                                      *
    // * Author: Dallas Toth                                                  *
    // * References: None                                                     *
    // ***********************************************************************
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& duplicate) {
    if (this != &duplicate) {
        clear();
        
        Node* temp = duplicate.topNode;
        Stack<T> tempStack;
        
        while (temp) {
            tempStack.push(temp -> data);
            temp = temp -> next;
        }
        
        while (!tempStack.empty()) {
            push(tempStack.top());
            tempStack.pop();
        }
    }
    
    return *this;
}

    // ***********************************************************************
    // * Function Name: Stack<T>& Stack<T>::operator=(Stack<T>&& duplicate)   *
    // * Description: Transfers elements from another stack. Move             *
    // *                                                                      *
    // * Parameter Description:                                               *
    // * - Stack<T>&& duplicate: Rvalue reference to another Stack object to be *
    // *                         moved from                                   *
    // * Returns: Reference to the current Stack object after move assignment.*
    // * Date: 6/18/2024                                                      *
    // * Author: Dallas Toth                                                  *
    // * References: None                                                     *
    // ***********************************************************************
template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& duplicate) {
    if (this != &duplicate) {
        clear();
        
        topNode = duplicate.topNode;
        NodeSize = duplicate.NodeSize;
        
        duplicate.topNode = nullptr;
        duplicate.NodeSize = 0;
    }
    
    return *this;
}

    // ***********************************************************************
    // * Function Name: bool Stack<T>::empty() const                          *
    // * Description: Checks if stack is empty                                *
    // * Parameter Description: None                                          *
    // * Returns: True if the stack is empty                                  *
    // * Date: 6/18/2024                                                      *
    // * Author: Dallas Toth                                                  *
    // * References: None                                                     *
    // ***********************************************************************
template <typename T>
bool Stack<T>::empty() const {
    return topNode == nullptr;
}

    // ***********************************************************************
    // * Function Name: void Stack<T>::clear()                                *
    // * Description: Clears all elements from stack                          *
    // * Parameter Description: None                                          *
    // * Date: 6/18/2024                                                      *
    // * Author: Dallas Toth                                                  *
    // * References: None                                                     *
    // ***********************************************************************
template <typename T>
void Stack<T>::clear() {
    while (!empty()) {
        pop();
    }
}

    // ***********************************************************************
    // * Function Name: void Stack<T>::push(const T& x)                       *
    // * Description: Push a new element onto  top of the stack               *
    // * Parameter Description:                                               *
    // * - const T& x: The element to be pushed onto stack                    *
    // * Date: 6/18/2024                                                      *
    // * Author: Dallas Toth                                                  *
    // * References: None                                                     *
    // ***********************************************************************
template <typename T>
void Stack<T>::push(const T& x) {
    Node* newNode = new Node{x, topNode};
    topNode = newNode;
    NodeSize++;
}

    // ***********************************************************************
    // * Function Name: void Stack<T>::push(T&& x)                            *
    // * Description: Moves a new element onto the top of the stack           *
    // * Parameter Description:                                               *
    // * - T&& x: element to be moved onto the stack                          *
    // * Date: 6/18/2024                                                      *
    // * Author: Dallas Toth                                                  *
    // * References: None                                                     *
    // ***********************************************************************
template <typename T>
void Stack<T>::push(T&& x) {
    Node* newNode = new Node{std::move(x), topNode};
    topNode = newNode;
    NodeSize++;
}

    // ***********************************************************************
    // * Function Name: void Stack<T>::pop()                                  *
    // * Description: Removes the top element from the stack                  *
    // * Parameter Description: None                                          *
    // * Date: 6/18/2024                                                      *
    // * Author: Dallas Toth                                                  *
    // * References: None                                                     *
    // ***********************************************************************
template <typename T>
void Stack<T>::pop() {
    if (!empty()) {
        Node* prevTop = topNode;
        topNode = topNode -> next;
        
        delete prevTop;
        NodeSize--;
    }
}

    // ***********************************************************************
    // * Function Name: T& Stack<T>::top()                                    *
    // * Description: Returns a reference to the top element of the stack     *
    // * Parameter Description: None                                          *
    // * Date: 6/18/2024                                                      *
    // * Author: Dallas Toth                                                  *
    // * References: None                                                     *
    // ***********************************************************************
template <typename T>
T& Stack<T>::top() {
    if (empty()) {
        throw std::out_of_range("stack is empty");
    }
    return topNode -> data;
}

    // ***********************************************************************
    // * Function Name: const T& Stack<T>::top() const                        *
    // * Description: Returns a const reference to the top element of stack   *
    // *                                                                      *
    // * Parameter Description: None                                          *
    // * Date: 6/18/2024                                                      *
    // * Author: Dallas Toth                                                  *
    // * References: None                                                     *
    // ***********************************************************************
template <typename T>
const T& Stack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("stack is empty");
    }
    return topNode -> data;
}

    // ***********************************************************************
    // * Function Name: int Stack<T>::size() const                            *
    // * Description: Returns the number of elements in the stack             *
    // * Parameter Description: None                                          *
    // * Date: 6/18/2024                                                      *
    // * Author: Dallas Toth                                                  *
    // * References: None                                                     *
    // ***********************************************************************
template <typename T>
int Stack<T>::size() const {
    return NodeSize;
}

    // ***********************************************************************
    // * Function Name: void Stack<T>::print(std::ostream& os, char ofc) const*
    // * Description: Prints all elements of the stack to the output stream  *
    // *                                                                      *
    // * Parameter Description:                                               *
    // * - os: Reference to the output stream                                 *
    // * - ofc: Delimiter character used to separate elements                 *
    // * Date: 6/20/2024                                                      *
    // * Author: Dallas Toth                                                  *
    // * References: None                                                     *
    // ***********************************************************************
template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const {
    Node* current = topNode;
    while (current) {
        os << current -> data << ofc;
        current = current -> next;
        }
    }
} 

/**~*~*~*~*
   Stack template
*~*/

#ifndef STACK_ADT
#define STACK_ADT

template <class T>
class Stack{
private:
    // Structure for the stack nodes
    struct StackNode
    {
      T value;          // Value in the node
      StackNode *next;  // Pointer to next node
    };

    StackNode *top;     // Pointer to the stack top
    int length;

public:
    // Constructor
    Stack(){
      top = nullptr;
      length = 0;
    }
    // Destructor
    ~Stack();

    // Stack operations:
    bool push(T);
    T pop();

    // return value on the top of stack
    T peek(){
        return top->value;
    }

    // check if stack is empty
    bool isEmpty(){
        return !length;
    }

    // return length of stack
    int getLength(){
        return length;
    }
};

/**~*~*~*~*
  Member function push inserts the argument onto
  the stack.
*~**/
template<class T>
bool Stack<T>::push(T item)
{
    StackNode *newNode; // Pointer to a new node

    // Allocate a new node and store num there.
    newNode = new StackNode;
    if (!newNode)
        return false;
    newNode->value = item;

    // Update links and counter
    newNode->next = top;
    top = newNode;
    length++;

    return true;
}

/**~*~*~*~*
  Member function pop deletes the value at the top
  of the stack and returns it.
  Assume stack is not empty.
*~**/
template<class T>
T Stack<T>::pop(){
    StackNode* tempNode = top;
    top = tempNode->next;
    T tempVal = tempNode->value;

    delete tempNode;
    length--;
    return tempVal;
}

/**~*~*~*~*
  Destructor:
  Traverses the list deleting each node (without calling pop)
*~**/
template<class T>
Stack<T>::~Stack()
{
    StackNode *currNode;
    currNode = top;

    while (currNode){
        top = currNode->next;
        delete currNode;
        currNode = top;
    }
}


#endif
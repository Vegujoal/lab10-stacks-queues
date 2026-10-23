/*
 * Course: COEN 2220 - Programming 2
 * Name: [Jose A Vera Guagua]
 * Lab: Lab 10 - Stacks & Queues
 * Description: Practice - a dynamic stack of active function calls
 * Due date: [10/23/2026]
 */

#include <iostream>
#include <string>
using namespace std;

class FunctionCallStack
{
private:
    // ===== Resolve these TODOs now (Part C) =====

    // TODO (Part C): Define Node with string functionName and Node *next.
    struct Node
    {
        string functionName; // Store one function name.
        Node *next;          // Point to the function call immediately below this one.
    };
    // TODO (Part C): Declare Node *top for the node that must leave next.
    Node *top;

public:
    // TODO (Part C): Write a constructor that creates an empty stack.
    FunctionCallStack()
    {
        top = nullptr;
    }

    // ===== Resolve these TODOs later (Part D) =====

    // TODO (Part D): Write isEmpty as a const member function.
    bool isEmpty() const
    {
        return top == nullptr;
    }
    // TODO (Part D): Write push to add a function name at top.
    void push(const string& functionName)
    {
        Node *newNode = new Node{functionName, top};
        top = newNode;
    }
    // TODO (Part D): Write pop. It returns bool and uses string& removedFunctionName.
    bool pop(string& removedFunctionName)
    {
        if (isEmpty())
        {
            return false; 
        }
        removedFunctionName = top->functionName;
        Node *temp = top;
        top = top->next;
        delete temp;
        return true;
    }

    // TODO (Part D): Write peek. It returns bool and uses string& topFunctionName.
    bool peek(string& topFunctionName) const
    {
        if (isEmpty())
        {
            return false; 
        }
        topFunctionName = top->functionName;
        return true;
    }
    // TODO (Part D): Write a destructor that releases every dynamic node.
    ~FunctionCallStack()
    {
    while (!isEmpty())
    {
        Node *temp = top;
        top = top->next;
        delete temp;
    }
}
};

int main()
{
    cout << boolalpha;

    // ===== Resolve these TODOs later (Part D) =====

    // TODO (Part D): Create a FunctionCallStack object.
    FunctionCallStack stack;
    // TODO (Part D): Push main, loadSchedule, and formatSchedule in that order.
    stack.push("main");
    stack.push("loadSchedule");
    stack.push("formatSchedule");
    // TODO (Part D): Use peek and pop to demonstrate LIFO with descriptive output.
    string functionName;
    if (stack.peek(functionName))
    {
        cout << "Current function: " << functionName << endl;
    }
    if (stack.pop(functionName))
    {
        cout << "Returned from function: " << functionName << endl;
    }
    // TODO (Part D): Pop remaining calls, then demonstrate an unsuccessful pop on an empty stack.
    while (stack.pop(functionName))
    {
        cout << "Returned from function: " << functionName << endl;
    }
    cout << "Stack is empty: " << stack.isEmpty() << endl;
    bool popResult = stack.pop(functionName);
    cout << "Pop from empty stack succeeded: " << popResult << endl;
    

    return 0;
}

/*
 * Analysis Answers
 *
 * D1 — Adding formatSchedule
 * When push("formatSchedule") executes, what must newNode->next receive before top
 * changes? Explain why reversing those two assignments would lose the previous top.
 * Answer:
 *newNode->next must receive the current value of top before top is updated to point to newNode.
 *If we reversed the assignments, we would lose the reference to the previous top node, making it impossible to access the rest of the stack.

 * D2 — Returning from a function
 * After main, loadSchedule, and formatSchedule are pushed in that order, list the
 * order in which three successful pop calls must return their names. Explain LIFO.
 * Answer:
 *This occurs in the order: formatSchedule, loadSchedule, main. LIFO (Last In, First Out) means that the last function pushed onto the stack is the first one to be popped off
 *reflecting the order of function calls and returns.

 * D3 — Destructor order
 * Why must the destructor save a next-node address before deleting the current node?
 * Answer:
 *The destructor must save the address of the next node before deleting the current node to ensure it can access the rest of the stack and delete all nodes properly.
 */
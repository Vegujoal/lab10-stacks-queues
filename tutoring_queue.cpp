/*
 * Course: COEN 2220 - Programming 2
 * Name: [Jose A Vera Guagua]
 * Lab: Lab 10 - Stacks & Queues
 * Description: Practice - a dynamic queue of tutoring requests
 * Due date: [10/23/2026]
 */

#include <iostream>
#include <string>
using namespace std;

class TutoringQueue
{
private:
    struct Node
    {
        string studentId; // Store one student waiting for tutoring.
        Node *next;       // Point to the student immediately behind this one.
    };

    Node *front; // Point to the student who must be served next.
    Node *rear;  // Point to the student most recently added.

public:
    TutoringQueue()
    {
        front = nullptr;
        rear = nullptr;
    }

    ~TutoringQueue()
    {
        while (front != nullptr)
        {
            Node *nodeToDelete = front;
            front = front->next; // Advance before releasing the current node.
            delete nodeToDelete;
        }

        rear = nullptr;
    }

    bool isEmpty() const
    {
        return front == nullptr;
    }

    // ===== Resolve these TODOs now (Part E) =====

    // TODO (Part E): Write enqueue to add newStudentId at rear.
    void enqueue(const string &newStudentId)
    {
        Node *newNode = new Node{newStudentId, nullptr};

        if (isEmpty())
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }
    // TODO (Part E): Write dequeue. It returns bool and uses string& servedStudentId.
    bool dequeue(string &servedStudentId)
    {
        if (isEmpty())
        {
            return false; // Queue is empty, cannot dequeue.
        }

        Node *nodeToDelete = front;
        servedStudentId = front->studentId; // Get the student ID to return.
        front = front->next; // Move front to the next node.

        if (front == nullptr) // If the queue is now empty, update rear.
        {
            rear = nullptr;
        }

        delete nodeToDelete; // Free the memory of the dequeued node.
        return true; // Dequeue successful.
    }
};

int main()
{
    cout << boolalpha;

    // TODO (Part E): Create a TutoringQueue object.
    TutoringQueue queue;
    // TODO (Part E): Add TU-301, TU-318, and TU-327 in that arrival order.
    queue.enqueue("TU-301");
    queue.enqueue("TU-318");
    queue.enqueue("TU-327");
    // TODO (Part E): Dequeue and print the first two served student IDs.
    string studentId;
    if (queue.dequeue(studentId))
    {
        cout << "Served student ID: " << studentId << endl;
    }
    if (queue.dequeue(studentId))
    {
        cout << "Served student ID: " << studentId << endl;
    }
    // TODO (Part E): Dequeue the last student, then print whether the queue is empty.
    if (queue.dequeue(studentId))
    {
        cout << "Served student ID: " << studentId << endl;
    }
    cout << "Queue empty: " << queue.isEmpty() << endl;
    // TODO (Part E): Add TU-340 after the queue becomes empty, dequeue it, and print its ID.
    queue.enqueue("TU-340");
    if (queue.dequeue(studentId))
    {
        cout << "Served student after empty queue: " << studentId << endl;
    }
    return 0;
}

/*
 * Analysis Answers
 *
 * E1 — First arrival
 * Why must the first call to enqueue assign newNode to both front and rear?
 * Answer:Because when the queue is empty, both front and rear should point to the same node
 * This ensures that the queue maintains its integrity and allows for proper enqueue and dequeue operations.
 *
 * E2 — Last departure
 * After dequeue removes the only remaining node, what must happen to rear and why?
 * Answer:Rear must be set to nullptr after dequeue removes the only remaining node.
 * This is because when the queue becomes empty, both front and rear should point to nullptr to indicate that there are no more nodes in the queue.
 *
 * E3 — FIFO evidence
 * List the expected service order for TU-301, TU-318, and TU-327. Explain why this
 * differs from the return order of the function-call stack in Part D.
 * Answer:
 *This is because the queue is FIFO (First In, First Out) data structure, meaning that the first student to arrive (TU-301) will be the first to be served.
 Followed by TU-318 and then TU-327. This differs from the return order of the function-call stack in Part D, which follows a LIFO (Last In, First Out) order, where the last function called is the first to return.
 */
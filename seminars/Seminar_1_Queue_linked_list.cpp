#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <iostream>
using namespace std;

class Queue {
public:
    // constructor will be called now
    Queue(int c);
    // destructor will be called automatically
    ~Queue();

    // below is defenition of public functions:
    void Enqueue(int data);
    int Dequeue();
    int get_test_var();

private:
    struct Node {
        Node *Next;
        int Data;

        // below is constructor
        // In C++ the only difference between a class and a struct is that members and base classes are private by default in classes,
        // whereas they are public by default in structs. So structs can have constructors,
        // and the syntax is the same as for classes.
        Node(int c) : Next(nullptr), Data(c) {}
    };

    Node *head;
    Node *tail;
    Node test_var;
};

// define constructor outside class
Queue::Queue(int c) :
        head(nullptr), // parent class that needs to take arguments to its constructor
        tail(nullptr), // parent class that needs to take arguments to its constructor
        test_var(c)// parent class that needs to take arguments to its constructor
{
    int a = 4;
    std::cout << "constructor!!" << endl;
}

// define destructor outside class
Queue::~Queue() {
    //printf("QUEUE");
    std::cout << "destructor!" << endl;
    while (head != nullptr) {
        Node *nextNode = head->Next;
        delete head;
        head = nextNode;
    }
}

// public function that returns private test variable
int Queue::get_test_var(){
    return test_var.Data;
}


// объявление public методов вне класса. Для этого пишется Queue::...
void Queue::Enqueue(int data) {
    //printf("Enqueue");
    std::cout << "Enqueue" << endl;
    Node *newNode = new Node(-1); // set default value -1
    newNode->Data = data;
    if (tail == nullptr) {
        assert(head == nullptr);
        head = newNode;
        tail = newNode;
    } else {
        tail->Next = newNode;
        tail = newNode;
    }
}

int Queue::Dequeue() {
    //printf("Dequeue");
    std::cout << "Dequeue" << endl;
    assert(head != nullptr);

    int tempData = head->Data;
    Node *tempNode = head;
    head = head->Next;
    if (head == nullptr) {
        tail = nullptr;
    }
    delete tempNode;
    return tempData;
}

int main() {
    //int n;
    //std::cin >> n;
    //int arr[15];
    std::cout << "resr" << endl;


    Queue q(15);
    q.Enqueue(123);
    q.Enqueue(123);
    std::cout << q.Dequeue() << endl; // print returned value
    std::cout << q.Dequeue() << endl; // print returned value
    // std::cout << q.Dequeue() << endl; // print returned value

    std::cout << q.get_test_var() << endl; // print returned value
    int a = 5;
    // destructor is called automatically

    return 0;
}
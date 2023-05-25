#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <mutex>

using namespace std;

template <typename T>
class Stack
{
private:
    size_t count;
    size_t capacity;
    vector<shared_ptr<T>> array;
    mutex mtx;

public:
    Stack(size_t capacity) : count(0), capacity(capacity), array(capacity) {}

    void Push(shared_ptr<T> data)
    {
        lock_guard<mutex> lock(mtx);
        if (count < capacity)
        {
            array[count++] = data;
        }
        else
        {
            throw runtime_error("Stack is full");
        }
    }
    shared_ptr<T> Pop()
    {
        lock_guard<mutex> lock(mtx);
        shared_ptr<T> result = nullptr;
        if (count > 0)
        {
            result = array[--count];
        }
        return result;
    }
    size_t Size()
    {
        lock_guard<mutex> lock(mtx);
        return count;
    }

    bool isEmpty()
    {
        lock_guard<mutex> lock(mtx);
        return count == 0;
    }

    bool isFull()
    {
        lock_guard<mutex> lock(mtx);
        return count == capacity;
    }
    shared_ptr<T> Peek()
    {
        lock_guard<mutex> lock(mtx);
        shared_ptr<T> result = nullptr;
        if (count > 0)
        {
            result = array[count - 1];
        }
        return result;
    }
    void Print()
    {
        lock_guard<mutex> lock(mtx);
        cout << "Printing stack" << endl;
        for (int i = 0; i < count; i++)
        {
            cout << *(array[i]) << endl;
        }
    }
};

int main()
{
    Stack<int> myStack(5); // Creates a stack of integers with capacity of 5

    // Push some elements into the stack
    for(int i = 0; i < 5; i++){
        myStack.Push(make_shared<int>(i));
    }

    // Print the stack
    myStack.Print();

    // Pop an element from the stack and print it
    auto popped = myStack.Pop();
    if(popped){
        cout << "Popped: " << *popped << endl;
    }

    // Print the stack after popping
    myStack.Print();

    return 0;
}

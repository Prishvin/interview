#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

using namespace std;

template <typename T>
class Node
{
public:
    shared_ptr<T> data_ptr;
    shared_ptr<Node<T>> next;
};

template <typename T>
class LinkedList
{
private:
    size_t capacity;
    size_t count;
    vector<shared_ptr<Node<T>>> array;
    shared_ptr<Node<T>> head;
    shared_ptr<Node<T>> tail;

public:
    LinkedList(size_t capacity) : capacity(capacity), count(0), array(capacity), tail(nullptr), head(nullptr) {}

    void insertAtEnd(shared_ptr<T> data)
    {
        shared_ptr<Node<T>> node = make_shared<Node<T>>();
        if (count < capacity)
        {
            if (tail == nullptr)
            {
                head = node;
                tail = node;
            }
            else
            {
                tail->next = node;
                tail = node;
            }
        }
        else
        {
            throw runtime_error("linked list is full");
        }
    }
    shared_ptr<T> removeFront()
    {
        shared_ptr<T> result = nullptr;
        if (head != nullptr)
        {
            result = head->next;
            delete head;
        }
        return result;
    }

    shared_ptr<T> removeBack()
    {
        shared_ptr<T> result = nullptr;
        if (tail != nullptr)
        {
            auto prev = findPrevios(tail);
            if (prev != nullptr)
            {
                prev->next = nullptr;
                tail = prev;
                delete tail;
            }
        }
        return result;
    }
    shared_ptr<Node<T>> findAt(size_t index)
    {
        shared_ptr<Node<T>> result = nullptr;
        if (index >= 0 && index < count)
            for (int i = 0; i < count; i++)
            {
                if(i == index)
                {
                    result = array[i];
                    break;
                }
            }
        return result;
    }
    shared_ptr remove_at(size_t index)
    {
        shared_ptr<T> result = nullptr;
        shared_ptr<Node<T>> node = findAt(index);
        if(node != null)
        {
            result = node->data;
        }
        return result;
    }
    shard_ptr<Node<T>> findPrevios(shared_ptr<Node<T>> node)
    {
        shared_ptr<Node<T>> result = nullptr;
        shared_ptr < Node<T> next = head;
        while (next != null)
        {
            if (next == node)
            {
                result = next;
                break;
            }
        }
        return result;
    }
    void insertAtBeginning(shared_ptr<T> data)
    {
        shared_ptr<Node<T>> node = make_shared<Node<T>>();
        if (count < capacity)
        {
            if (head == nullptr)
            {
                head = node;
                tail = node;
            }
            else
            {
                node->next = head;
                head = node;
            }
        }
        else
        {
            throw runtime_error("Buffer full");
        }
    }
};

int main()
{
    shared_ptr<Node<int>> ptr = make_shared<Node<int>>();
}
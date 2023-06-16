#include <iostream>
#include <stdexcept>

// front_> head -> <prev next> - <prev next> <- tail <back
using namespace std;

template <typename T>
class Node
{
public:
    Node() : data(nullptr), next(nullptr), previos(nullptr) {}
    T *data;
    Node<T> *next;
    Node<T> *previos;
};

// front_> head -> <prev next> - <prev next> <- tail <back

template <typename T>
class DoubleLinkedList
{
public:
    DoubleLinkedList() : head(nullptr), tail(nullptr) {}
    Node<T> *head;
    Node<T> *tail;

    T *get_front()
    {
        if (head != nullptr)
            return head->data;
        else
            return nullptr;
    }
    T *get_back()
    {
        if (head != nullptr)
            return tail->data;
        else
            return nullptr;
    }
    // front_> head -> <prev next> - <prev next> <- tail <back
    void removeFront()
    {
        if (head != nullptr)
        {
            Node<T> *next = head->next;
            delete head;
            head = next;
            if (head)

                head->previos = nullptr;
            else
                tail = nullptr;
        }
    }
    void removeBack()
    {
        if (tail != nullptr)
        {
            Node<T> *previous = tail->previos;
            delete tail;
            tail = previous;
            if (tail)
                tail->next = nullptr;
            else
                head = nullptr;
        }
    }
    void insertFront(T *item)
    {
        Node<T> *node = new Node<T>;
        Node<T> *tmp = head;

        head = node;
        node->data = item;

        if (tmp != nullptr)
        {
            node->next = tmp;
            tmp->previos = node;
        }
        if (tail == nullptr)
        {
            tail = node;
        }
    }
    int count_elements()
    {
        Node<T> *next = head;

        int i = 0;

        while (next != nullptr)
        {

            next = next->next;
            i++;
        }

        return i;
    }
    Node<T> *getAt(int index)
    {
        Node<T> *next = head;
        Node<T> *result = nullptr;
        int i = 0;

        while (next != nullptr)
        {
            if (i == index)
            {
                result = next;
                break;
            }
            else
            {
                next = next->next;
                i++;
            }
        }
        return result;
    }

    bool insertAt(T *item, int index)
    {
        // front_> head -> <prev next> - <prev next> <- tail <back
        int count = count_elements();
        if (index < 0)
            return false;
        if (index == 0)
            insertFront(item);
        else if (index == count)
            insertBack(item);
        else
        {
            Node<T> *current = getAt(index);
            Node<T> *node = new Node<T>;
            Node<T> *next = current->next;
            Node<T> *previos = current->previos;
            node->data = item;
            node->next = current;
            node->previos = current->previos;
            current->previos = node;
        }
        return true;
    }

    void insertBack(T *item)
    {
        Node<T> *node = new Node<T>;
        Node<T> *tmp = tail;

        tail = node;
        node->data = item;

        if (tmp != nullptr)
        {
            node->previos = tmp;
            tmp->next = node;
        }
        if (head == nullptr)
        {
            head = node;
        }
    }

    void print()
    {
        cout << "Printing list" << endl;
        Node<T> *next = head;
        while (next != nullptr)
        {
            cout << *next->data << " " << next->next << endl;
            next = next->next;
        }
    }
};

int main()
{
    DoubleLinkedList<int> list;

    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    int a4 = 4;
    int a5 = 5;
    int a6 = 6;

    list.insertFront(&a1);
    list.insertFront(&a2);
    list.insertFront(&a3);
    list.insertFront(&a4);
    list.insertFront(&a5);
    list.insertFront(&a6);

    list.print();

    list.removeFront();
    list.removeFront();
    list.print();

    list.removeBack();
    list.removeBack();
    list.print();
}
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;
template <typename T>

class CircularBuffer
{
    public:

    CircularBuffer(int capacity): buffer(capacity), capacity(capacity), head(0), tail(0), count(0) {}
    vector<T> buffer;
    int head;
    int tail;
    int count;
    int capacity;

    bool enqueue(T &item)
    {
          buffer[tail] = item;
          tail = (tail+1)%capacity;
          if(count < capacity)
          {
            
            count++;
          }
          else
          {
             head = (head+1)%capacity;
          }
    }

    T dequeue()
    {
      
        if(count == 0)
            throw runtime_error("buffer is empty");
            else
            {
                count--;
                  T result = buffer[head];
                head = (head + 1) % capacity;
                return result;
            }
    }

    void print()
    {

        cout << "printing " << count << endl;
        for(int i = 0; i < count; i++)
            cout << buffer[(head + i)%capacity].value1 << endl;

    }

    T get_at(int index)
    {
    
        if(index < 0 || index >= count)
            throw exception("index out of bounds");
        else
            {
                return &buffer[ (head + index)%capacity];
            }

    }



};


class Item
{
    public:
        Item (){}
        Item(int v1, int v2): value1(v1), value2(v2){}
        int value1;
        int value2;
};

int main(void)
{
    Item t1(11, 11);
    Item t2(22, 11);
    Item t3(33, 11);
    Item t4(44, 11);
    Item t5(55, 11);
    Item t6(66, 11);

    std::cout << "Hello CB\n";
    CircularBuffer<Item> buf(3);

    buf.enqueue(t1);
    buf.print();
    buf.enqueue(t2);
    buf.print();

    buf.dequeue();
    buf.print(); 

    buf.enqueue(t3);
    buf.print();
    buf.enqueue(t4);
    buf.print();
    buf.enqueue(t5);
    buf.print();
}

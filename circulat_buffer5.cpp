#include <iostream>
#include <memory>
#include <vector>
#include <mutex>

template<typename T>
class CircularBuffer
{
	private:
		size_t count;
		size_t capacity;
		size_t head;
		size_t tail;
		mutex mtx;
		vector<shared_ptr<T>> data;
	public:
		CircularBuffer(size_t capacity): capacity(capacity), count(0), head(0), tail(0), data(vector<shared_ptr<T>>(capacity)) {}
		~CircularBuffer()
		{
			//nothing to do here
		}
		bool Enqueue(shared_ptr<T> item) //true if overflows
		{
			lock_guard<mutex> lock(mtx);
			bool result = false;
			data[tail] = item;
			tail = (tail + 1) % capacity;
			if(count < capacity)
			{
				count++;
			}
			else
			{
				head = (head + 1) % capacity;
				result = true;
			}
			return result;
		}
		
		shared_ptr<T> Dequeue()
		{
			lock_guard<mutex> lock(mtx);
			shared_ptr<T> result = nullptr;
			if(count > 0)
				{
					result = data[head];
					head = (head + 1) % capacity;
					count--;
				}
			return result;
		}
		
		shared_ptr<T> Peek()
		{
			lock_guard<mutex> lock(mtx);
			shared_ptr<T> result = nullptr;
			if(count > 0)
				result = data[head];
			return result;
		}
		
		void Print()
		{
		}
		
};
int main()
{
    CircularBuffer<int> cb(5);
    for(int i =0; i < 6; i++)
    {
        cb.enqueue(make_shared<int>(i));

    }
    cb.print();
        for(int i =0; i < 8; i++)
    {
        cb.enqueue(make_shared<int>(i));

    }
    cb.print();
    return 0;
}
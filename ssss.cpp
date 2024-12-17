#include <iostream>
using namespace std;

template<typename T>
class MyInt
{
private:
    T value;
public:
    MyInt(T value = T()) : value(value) {}
    void SetData(T value)
    {
        this->value = value;
    }
    T GetData() const
    {
        return value;
    }
};

template<typename T>
class Stack
{
private:
    T* data;
    size_t size;
    size_t capacity;

    void Resize(size_t newCapacity)
    {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; i++)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Stack(size_t capacity = 4) : capacity(capacity), size(0)
    {
        data = new T[capacity];
    }

    ~Stack()
    {
        delete[] data;
    }

    void Push(const T& value)
    {
        if (size == capacity)
        {
            Resize(capacity * 2);
        }
        data[size++] = value;
    }

    T& Peek()
    {
        if (size == 0) throw out_of_range("stack is empty");
        return data[size - 1];
    }

    void Pop()
    {
        if (size > 0)
        {
            size--;
        }
    }

    size_t GetSize() const
    {
        return size;
    }

    size_t GetCapacity() const
    {
        return capacity;
    }

    bool IsEmpty() const
    {
        return size == 0;
    }
};

template<typename T>
class Queue
{
private:
    T* data;
    size_t size;
    size_t capacity;
    size_t frontIndex;
    size_t back;

    void Resize(size_t newCapacity)
    {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; i++)
        {
            newData[i] = data[(frontIndex + i) % capacity];
        }
        delete[] data;
        data = newData;
        frontIndex = 0;
        back = size;
        capacity = newCapacity;
    }

public:
    Queue(size_t capacity = 4) : capacity(capacity), size(0), frontIndex(0), back(0)
    {
        data = new T[capacity];
    }
    ~Queue()
    {
        delete[] data;
    }
    void Enqueue(const T& value)
    {
        if (size == capacity)
        {
            Resize(capacity * 2);
        }
        data[back] = value;
        back = (back + 1) % capacity;
        size++;
    }
    void Dequeue()
    {
        if (IsEmpty()) throw out_of_range("queue is empty");
        frontIndex = (frontIndex + 1) % capacity;
        size--;
    }

    T& Front()
    {
        if (IsEmpty()) throw out_of_range("queue is empty");
        return data[frontIndex];
    }

    size_t GetSize() const
    {
        return size;
    }

    bool IsEmpty() const
    {
        return size == 0;
    }
};

int main()
{
    Stack<MyInt<int>> myStack;
    myStack.Push(1);
    myStack.Push(2);
    myStack.Push(3);
    myStack.Push(63);

    while (!myStack.IsEmpty())
    {
        cout << myStack.Peek().GetData() << endl;
        myStack.Pop();
    }

    Queue<MyInt<string>> myQueue;
    myQueue.Enqueue(MyInt<string>("Hello"));
    myQueue.Enqueue(MyInt<string>("World"));
    myQueue.Enqueue(MyInt<string>("Queue"));

    while (!myQueue.IsEmpty())
    {
        cout << myQueue.Front().GetData() << endl;
        myQueue.Dequeue();
    }
}

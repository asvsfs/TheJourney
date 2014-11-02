template <typename T, unsigned int capacity>
class MemoryPool
{
public:
    MemoryPool()
    {
        for (unsigned int i = 0; i < capacity; i++)
        {
            myUnusedMemory[i] = &myMemory[i];
        }
    }

    void* operator new(std::size_t size)
    {
        return myUnusedMemory[myUnusedIndex--];
    }

    void operator delete(void* ptr)
    {
        myUnusedMemory[++myUnusedIndex] = (T*)ptr;
    }

private:
    static int myUnusedIndex;
    static T myMemory[capacity];
    static T* myUnusedMemory[capacity];
};

template <typename T, unsigned int capacity> int MemoryPool<T, capacity>::myUnusedIndex = capacity-1;
template <typename T, unsigned int capacity> T MemoryPool<T, capacity>::myMemory[capacity];
template <typename T, unsigned int capacity> T* MemoryPool<T, capacity>::myUnusedMemory[capacity];
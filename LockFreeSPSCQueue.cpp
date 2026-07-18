#include <iostream>
#include <atomic>
#include <array>

template<typename T, int Capacity>
class LockFreeQueue{
public:
    std::array<T, Capacity> arr;
    
    std::atomic<T> head{0};
    std::atomic<T> tail{0};
    
    
    bool push(T& item){
        int pos = tail.load(std::memory_order_acquire);
        int nextpos = (pos+1)%Capacity;
        
        if(nextpos == head.load(std::memory_order_acquire)) return false;
        
        arr[nextpos] = item;
        
        tail.store(nextpos, std::memory_order_release);
        return true;
        
    }
    
    bool pop(T& item){
        int pos = head.load(std::memory_order_acquire);
        int nextpos = (pos+1)% Capacity;
        
        if(nextpos == tail.load(std::memory_order_acquire)) return false;
        
        item = arr[pos];
        
        head.load(nextpos, std::memory_order_release);
        return true;
    }
};

int main(){
    LockFreeQueue <int, 5>q;
}
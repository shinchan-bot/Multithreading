#include <iostream>
#include <atomic>
#include <array>
using namespace std;


template<typename T>
class _Vector{
    
public:

    _Vector(): data_(nullptr), size_(0), capacity_(0){}
    
    ~_Vector(){
        delete[] data_;
    }
    
    size_t _size(){
        return size_;
    }
    
    size_t _capacity(){
        return capacity_;
    }
    
    void _push_back(const T& value){
        if(size_ == capacity_){
            reserve(capacity_ == 0 ? 1 : capacity_*2);
        }
        
        data_[size_] = value;
        size_++;
        
    }
    
    void _pop_back(){
        if(size_ == 0) return;
        
        size_--;
    }
    
    void reserve(T newCapacity){
        if(newCapacity < capacity_) return;
        
        
        T* newdata = new T[newCapacity];
        
        for(int i=0; i<capacity_; i++){
            newdata[i] = std::move(data_[i]);
        }
        
        delete[] data_;
        
        data_ = newdata;
        capacity_ = newCapacity;
        return ;
    }
    
    bool empty(){
        return 0 == size_;
    }
    
    T& operator[] (int idx){
        return data_[idx];
    }
    
    void clear(){
        size_ = 0;
    }
    
    void resize(int newCapacity){
        if(newCapacity > capacity_) reserve(newCapacity);
        
        if(newCapacity > size_){
            for(int i=size_; i< newCapacity; i++){
                data_[i] = T();
            }
        }
        
        size_ = newCapacity;
    }
    
    
    
private:
    T capacity_ = 0;
    T size_ = 0;
    T* data_ = nullptr;
    
};

int main(){
    _Vector<int> v;
    
    v._push_back(1);
    cout<<v._size()<<endl;
    v._pop_back();
    cout<<v._size()<<endl;
    
}
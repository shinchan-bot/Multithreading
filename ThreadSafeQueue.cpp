#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <queue>

template<typename T>
class ThreadSafeQueue{
public:
    std::mutex mtx;
    std::condition_variable cv;
    
    void push(int value){
        std::lock_guard<std::mutex> lock(mtx);
        q.push(std::move(value));
        cv.notify_all();
    }
    
    void pop(){
        std::lock_guard<std::mutex> lock(mtx);
        if(!q.empty()) q.pop();
        cv.notify_all();
    }
    
    void display(){
        std::lock_guard<std::mutex> lock(mtx);
        if(!q.empty()) std::cout<<q.back()<<std::endl;
        sleep(1);
        cv.notify_all();
    }
    
private:
    std::queue<T> q;
    
};

void helper(ThreadSafeQueue<int> &mq){
    mq.push(1);
    mq.display();
    mq.push(2);
    mq.display();
    mq.push(3);
    mq.display();
    mq.pop();
    mq.display();
    mq.pop();
    mq.display();

}


int main(){

    ThreadSafeQueue<int> mq;
    std::vector<std::thread> thread_pool;
    
    for(int i = 0; i<10; i++){
        thread_pool.emplace_back(helper, std::ref(mq));
    }
    
    for(int i=0; i<10; i++){
        if(thread_pool[i].joinable()) thread_pool[i].join();
    }
    
}



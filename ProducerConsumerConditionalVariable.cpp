#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <queue>

std::queue<int> buffer;

std::condition_variable cv;
std::mutex mtx;

void producer(){
    
    while(true){
        std::unique_lock<std::mutex> lock(mtx);
        
        cv.wait(lock, [](){return buffer.empty();});
        
        while(buffer.size() < 10){ buffer.push(1); std::cout<<"Producer: "<<buffer.size()<<std::endl; sleep(1);}
        
        
        lock.unlock();
        cv.notify_all();
    }
    
}

void consumer(){
    while(true){
        std::unique_lock<std::mutex> lock(mtx);
        
        cv.wait(lock, [](){return buffer.size() >=10;});
        
        while(buffer.size() > 0){  buffer.pop(); std::cout<<"Consumer: "<<buffer.size()<<std::endl; sleep(1);}

        lock.unlock();
        cv.notify_all();
    }
}




int main(){

    std::thread t1(producer);
    std::thread t2(consumer);
    
    t1.join();
    t2.join();
    
}
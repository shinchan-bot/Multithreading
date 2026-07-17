#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>
#include <condition_variable>


std::atomic<int> counter(0);
std::mutex mtx;
int MAX_COUNT = 100;
std::atomic<bool> stop_flag(false);

std::atomic<int> turn(0);
std::condition_variable cv;


void helper(int t){
    int myTurn = t;
    
    
    while(true){

    
        std::unique_lock<std::mutex> lock(mtx);
        
        cv.wait(lock, [myTurn](){return myTurn == turn.load(std::memory_order_acquire) || counter >= MAX_COUNT; });
        
        
        if(counter >= MAX_COUNT){
             turn = (turn+1)%4;

            cv.notify_all();
            return;
        }
        ++counter;
        turn = (turn+1)%4;
        std::cout<<turn<<".   "<<counter<<std::endl;
        
        cv.notify_all();
    }
}


int main(){

    std::vector<std::thread> thread_pool;
    for(int i=0; i<4; i++){
        thread_pool.emplace_back(helper, i);
    }

    for(int i=0; i<4; i++){
        if(thread_pool[i].joinable())
            thread_pool[i].join();
    }

}
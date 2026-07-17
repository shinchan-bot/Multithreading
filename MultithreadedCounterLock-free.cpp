#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>

std::atomic<int> counter(0);
std::mutex mtx;
int MAX_COUNT = 100;
std::atomic<bool> stop_flag(false);

std::atomic<int> turn{0};

void helper(int t){
    int myTurn = t;
    
    while(true){
        while(turn.load(std::memory_order_acquire) != myTurn) {}
        {
            std::lock_guard<std::mutex> lock(mtx);
            if(counter >= MAX_COUNT){
                break;
            }
            counter+=1;
            std::cout<<myTurn<<".  "<<counter<<std::endl;
            turn = (turn+1)%4;
        }
        
        // std::this_thread::yield();
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
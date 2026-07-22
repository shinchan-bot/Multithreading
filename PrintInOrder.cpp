class Foo {
public:
    Foo() {

    }

    std::atomic<int> turn{0};

    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        while(turn.load(std::memory_order_acquire) != 0){}
        int nextturn = turn+1;
        printFirst();
        turn.store(nextturn, std::memory_order_release);

    }

    void second(function<void()> printSecond) {
        
        // printSecond() outputs "second". Do not change or remove this line.
        while(turn.load(std::memory_order_acquire) != 1){}
        int nextturn = turn+1;
        printSecond();
        turn.store(nextturn, std::memory_order_release);

    }

    void third(function<void()> printThird) {
        
        // printThird() outputs "third". Do not change or remove this line.
        while(turn.load(std::memory_order_acquire) != 2){}
        int nextturn = turn+1;
        printThird();
        turn.store(nextturn, std::memory_order_release);

    }
};
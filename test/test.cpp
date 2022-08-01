#include <iostream>
#include <thread>
#include <memory>
#include "../include/sort.h"
#include "../../src/data_struct/queue_thread.cpp"

void test_heapsort()
{   
    std::cout<<"===============";
    std::cout << __FUNCTION__ << "==============="<< std::endl;
    int input[5] = {1,5,2,4,3};
    // reverse(intput);
    heap_sort(input,5,true);
    for(int i = 0;i<5;i++)
    {
        std::cout<<input[i]<<" ";
    }
    std::cout<<std::endl;


    double input2[5] = {1.1,5.5,2.3,2.4,3.1};
    heap_sort(input2,5,false);
    for(int i = 0;i<5;i++)
    {
        std::cout<<input2[i]<<" ";
    }
    std::cout<<std::endl;
    return;
}

void test_thread_queue(){
    Queue<int> safe_que;

    auto producer = [&]() {    
        for (int i = 0; i < 100; ++i) {
            safe_que.push(i);
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    };

    auto consumer1 = [&]() {
        while (1) {
            std::printf("[1]  -------   %d\n", safe_que.pop());
        }
    };

    auto consumer2 = [&]() {
        while (1) {
            auto value = 0;
            auto res = safe_que.try_pop(value);
            std::printf("[2]  -------   %d\n", res ? value : -1);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    };

    std::thread t1(producer);
    std::thread t2(consumer1);
    t1.join();
    t2.join();
}




int main()
{
    std::cout<<"Hello TinySTL!"<<std::endl;
    test_thread_queue();
    return 0;
}
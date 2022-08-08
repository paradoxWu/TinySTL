#include <iostream>
#include <thread>
#include <memory>
#include "../include/sort.h"
#include "../../src/data_struct/queue_thread.cpp"
#include "../../src/data_struct/vector_.cpp"


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
            std::printf("[push]  -------   %d\n",i);
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
    std::thread t2(consumer2);
    t1.join();
    t2.join();
}

void test_vector(){
    std::cout<<__FUNCTION__<<std::endl;
    std::cout<<"================="<<std::endl;
    {

        Vector<int> vec2(10);
        std::cout<<"vec is empty? "<<vec2.empty()<<std::endl;
        for(int i =0;i<10;i++){
            vec2[i] = i;
        }
        for(int i =0;i<10;i++){
            std::cout<<vec2[i]<<" ";
        }
        std::cout<<std::endl;
        std::cout<<"vec is empty? "<<vec2.empty()<<std::endl;
        vec2.clear();
        std::cout<<"vec is empty? "<<vec2.empty()<<std::endl;
    }

    {
        Vector<int> vec;
        std::cout<<"vec is empty? "<<vec.empty()<<std::endl;
        vec.push_back(1);
        vec.push_back(2);
        std::cout<<vec[0]<<" "<<vec[1]<<std::endl;
        std::cout<<"vec is empty? "<<vec.empty()<<std::endl;

    }
    std::cout<<"================="<<std::endl;
    std::cout<<"end"<<std::endl;
}

int main()
{
    std::cout<<"Hello TinySTL!"<<std::endl;
    test_vector();
    return 0;
}
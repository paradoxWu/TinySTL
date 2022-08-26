#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include "../include/sort.h"
#include "../include/my_string.h"
#include "../../src/data_struct/queue_thread.cpp"
#include "../../src/data_struct/vector_.cpp"
#include "../../src/utility/allocator.cpp"

void test_heapsort()
{
        std::cout << "===============";
        std::cout << __FUNCTION__ << "===============" << std::endl;
        int input[5] = { 1, 5, 2, 4, 3 };
        // reverse(intput);
        heap_sort(input, 5, true);
        for (int i = 0; i < 5; i++) {
                std::cout << input[i] << " ";
        }
        std::cout << std::endl;

        double input2[5] = { 1.1, 5.5, 2.3, 2.4, 3.1 };
        heap_sort(input2, 5, false);
        for (int i = 0; i < 5; i++) {
                std::cout << input2[i] << " ";
        }
        std::cout << std::endl;
        return;
}

void test_thread_queue()
{
        std::cout << "===============";
        std::cout << __FUNCTION__ << "===============" << std::endl;
        std::cout << "========Test 1=========" << std::endl;
        Queue<int> safe_que;
        {
                auto producer = [&]() {
                        for (int i = 0; i < 100; ++i) {
                                safe_que.push(i);
                                std::printf("[push]  -------   %d\n", i);
                                std::this_thread::sleep_for(std::chrono::seconds(2));
                        }
                };

                auto consumer1 = [&]() {
                        while (1) {
                                std::printf("[1]  -------   %d\n", safe_que.pop());
                        }
                };
                std::thread t1(producer);
                std::thread t2(consumer1);
                t1.join();
                t2.join();
        }

        std::cout << "========Test 2=========" << std::endl;

        {
                auto producer = [&]() {
                        for (int i = 0; i < 100; ++i) {
                                safe_que.push(i);
                                std::printf("[push]  -------   %d\n", i);
                                std::this_thread::sleep_for(std::chrono::seconds(2));
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
        std::cout << "=================" << std::endl;
        std::cout << "end" << std::endl;
}

void test_vector()
{
        std::cout << "===============";
        std::cout << __FUNCTION__ << "===============" << std::endl;
        std::cout << "========Test 1=========" << std::endl;
        {

                Vector<int> vec2(10);
                std::cout << "vec is empty? " << vec2.empty() << std::endl;
                std::cout << "vec size: " << vec2.size() << std::endl;
                std::cout << "vec capacity: " << vec2.capacity() << std::endl;
                for (int i = 0; i < 10; i++) {
                        vec2[i] = i;
                }
                for (int i = 0; i < 10; i++) {
                        std::cout << vec2[i] << " ";
                }
                std::cout << std::endl;
                std::cout << "vec is empty? " << vec2.empty() << std::endl;
                std::cout << "vec size: " << vec2.size() << std::endl;
                std::cout << "vec capacity: " << vec2.capacity() << std::endl;
                vec2.clear();
                std::cout << "vec is empty? " << vec2.empty() << std::endl;
                std::cout << "vec size: " << vec2.size() << std::endl;
                std::cout << "vec capacity: " << vec2.capacity() << std::endl;
        }
        std::cout << "========Test 2=========" << std::endl;
        {
                Vector<int> vec;
                std::cout << "vec is empty? " << vec.empty() << std::endl;
                std::cout << "vec size: " << vec.size() << std::endl;
                std::cout << "vec capacity: " << vec.capacity() << std::endl;
                vec.push_back(1);
                vec.push_back(2);
                std::cout << vec[0] << " " << vec[1] << std::endl;
                std::cout << vec.front() << " " << vec.back() << std::endl;
                std::cout << "vec is empty? " << vec.empty() << std::endl;
                std::cout << "vec size: " << vec.size() << std::endl;
                std::cout << "vec capacity: " << vec.capacity() << std::endl;
                vec[1] = 100;
                std::cout << vec[0] << " " << vec[1] << std::endl;
                vec.clear();
                std::cout << "vec is empty? " << vec.empty() << std::endl;
                std::cout << "vec size: " << vec.size() << std::endl;
                std::cout << "vec capacity: " << vec.capacity() << std::endl;
        }
        std::cout << "=================" << std::endl;
        std::cout << "end" << std::endl;
}

void test_string()
{
        MyString a;
        std::cout << "a is " << a << std::endl;
        string input = "test1";
        MyString b(input.data());
        std::cout << "b is " << b << std::endl;

        a = b;
        std::cout << "a is " << a << std::endl;
        const char *mystr = a.c_str();
        std::cout << "mystr is " << mystr << std::endl;

        MyString c = std::move(b);
        std::cout << "c is " << c << std::endl;
        std::cout << "b is " << b << std::endl;

        // c++;
        // std::cout << "c is " << c << std::endl; //

        /*
        a is
        b is test1
        mystr is test
        c is test1
        b is
        c is uftu2
        */
}

void test_allocator()
{
        int ia[5] = { 0, 1, 2, 3, 4 };
        std::vector<int, WYH::allocator<int>> iv(ia, ia + 5);
        for (size_t i = 0; i < iv.size(); i++) {
                std::cout << iv[i] << " ";
        }
        std::cout << std::endl;
        WYH::allocator<int> all_;
        std::cout << "max_size of the allocator:" << all_.max_size() << std::endl;
}

int main()
{
        std::cout << "Hello TinySTL!" << std::endl;
        test_allocator();
        return 0;
}
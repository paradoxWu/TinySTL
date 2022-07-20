#include <iostream>
#include "../include/sort.h"

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

int main()
{
    std::cout<<"Hello TinySTL!"<<std::endl;
    test_heapsort();
    return 0;
}
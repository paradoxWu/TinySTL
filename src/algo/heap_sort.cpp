#include <iostream>
#include <algorithm>
// #include "../../include/sort.h"

template<class T>
void reverse(T &b,int len)
{
    // size_t len = sizeof(b)/sizeof(b[0]);
    for(size_t i =0;i<len/2;i++)
    {
        std::swap(b[i],b[len-1-i]);
    }
}

template<class T>
void max_heapify(T &arr, int start, int end) {
    int dad = start;
    int son = dad * 2 + 1;

    while (son < end) { // 若子節點指標在範圍內才做比較
        if (son + 1 < end && arr[son] < arr[son + 1]) // 先比較兩個子節點大小，選擇最大的
            son++;

        if (arr[dad] > arr[son]) // 如果父節點大於子節點代表調整完畢，直接跳出函數
            return;
        else { // 否則交換父子內容再繼續子節點和孫節點比較
            std::swap(arr[dad], arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void heap_sort(int *arr,int len,bool reverse_flag)
{    
    // 初始化，i从倒数第二层开始,建立一个最大堆
    for (int i = len/2-1; i >= 0; i--)
    {
        max_heapify(arr, i, len);
    }
    // 先將第一個元素和已经排好的元素前一位做交換，再從新調整(刚调整的元素之前的元素)，直到排序完畢
    for (int i = len - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);
        max_heapify(arr, 0, i);
    }
    if(reverse_flag){
        reverse(arr,len);
    }
}

void heap_sort(double *arr,int len,bool reverse_flag)
{    
    // 初始化，i从倒数第二层开始,建立一个最大堆
    for (int i = len/2-1; i >= 0; i--)
    {
        max_heapify(arr, i, len);
    }
    // 先將第一個元素和已经排好的元素前一位做交換，再從新調整(刚调整的元素之前的元素)，直到排序完畢
    for (int i = len - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);
        max_heapify(arr, 0, i);
    }
    if(reverse_flag){
        reverse(arr,len);
    }
}


// int main()
// {
//     int input[5] {1,5,2,4,3};
//     // reverse(intput);
//     heap_sort(input,5,false);
//     for(int i = 0;i<5;i++)
//     {
//         std::cout<<input[i]<<" ";
//     }
//     std::cout<<std::endl;


//     double input2[5] {1.1,5.5,2.3,2.4,3.1};
//     heap_sort(input2,5,false);
//     for(int i = 0;i<5;i++)
//     {
//         std::cout<<input2[i]<<" ";
//     }
//     std::cout<<std::endl;
//     return 0;
// }
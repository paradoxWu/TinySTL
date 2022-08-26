# 空间配置器 Allocator
隐藏在各类容器(container)背后 默默工作
例如vector
```c++
template<class T,class Alloc = alloc>
class vector{
    public:
    ......
    protected:
        typedef simple_alloc<value_type,Alloc> data_allocator;
}
```
缺省的使用默认的配置器`std::alloc`，实际我们也可以自己写一个去创建容器

## 一些比较重要的代码
1. `ptrdiff_t`: 常记录指针地址相减的结果`long int`  
    `size_t`: 计算元素数量，实际为`unsigned int`

> std::ptrdiff_t is signed. std::size_t is unsigned
2. `set_new_handler(0)`  
> new_handler 用于 当内存分配的需求无法被满足时 根据传入的函数地址调用指定的函数.如果设置为0，set_new_handler(0)，相当于set_new_handler(nullptr)，就会默认，在内存分配失败时抛出`std::bad_alloc`异常，具体可以翻阅 《effective c++》 条款7
3. `::operator new` `::operate delete`
> c++常见的new，delete其实是包括两部分的
> new: 分配内存+构造函数; ::operator new + placement new
> delete: 析构函数+释放内存  ~() + ::operate::delete

可以参考c中`stdlib. h`的`malloc()`,`free()`, 实际上SGI STL的空间配置器使用的也是malloc和free，可能的原因除了历史原因外，还有实际上c++中没有相应于`realloc()`这样的操作

## 双层级配置器
### 第一级配置器
使用malloc，relloc，free
需要设置类似set_new_handler()的函数，处理分配失败的情况

### 第二级配置器
当配置区块小于128bytes，采用第二级配置器，使用内存池(memory pool)的方式
维护自由链表(free list)，SGI第二级配置器主动将小额区块的内存需求调整为8的倍数，例如30byte调整为32bytes，共维护16个free-lists（8，16，24.....128)
```c++
union obj{
    union obj *free_list_link;
    char client_data[1];
}
```
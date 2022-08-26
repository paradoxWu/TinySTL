# 右值与移动构造函数

c++11特性里面，非常重要的一点就是加入了右值引用

> 值得一提的是，左值的英文简写为“lvalue”，右值的英文简写为“rvalue”。很多人认为它们分别是"left value"、"right value" 的缩写，其实不然。lvalue 是“loactor value”的缩写，可意为存储在内存中、有明确存储地址（可寻址）的数据，而 rvalue 译为 "read value"，指的是那些可以提供数据值的数据（不一定可以寻址，例如存储于寄存器中的数据）
> 如何判断表达式为左值还是右值，通常两个办法

1. 赋值号（=）左边的左值，右边的右值

```c++
int a = 5;
5 = a;//error
```

2. 可以获取到存储地址的为左值，反之为右值

## 一种万能的引用方式-常量左值引用

常量左值引用既可以操作左值，也可以操作右值

```c++
int num = 10;
const int &b = num;
const int &c = 10;
```

我们知道，右值往往是没有名称的，因此要使用它只能借助引用的方式。这就产生一个问题，实际开发中我们可能需要对右值进行修改（实现移动语义时就需要），显然左值引用的方式是行不通的.
为了解决这个问题，C++11 标准新引入了另一种引用方式，称为右值引用，用 "&&" 表示。

## 解读右值引用

### T&& k = getVar();

通常，我们在程序中常常会这么写

```c++
int i = getVar();//(1)
```

这行代码会产生几种类型的值呢？答案是会产生两种类型的值，一种是左值i，一种是函数getVar()返回的临时值，这个临时值在表达式结束后就销毁了，而左值i在表达式结束后仍然存在，这个临时值就是右值，具体来说是一个纯右值，右值是不具名的.

```c++
T&& k = getVar();//(2)
```

虽然第二行代码和第一行代码看起来差别不大，但是实际上语义的差别很大，这里，getVar()产生的临时值不会像第一行代码那样，在表达式结束之后就销毁了，而是会被“续命”，他的生命周期将会通过右值引用得以延续，和变量k的声明周期一样长

**从性能考虑**

```c++
A GetA()
{
    return A();
}

int main() 
{
    A a = GetA();
    return 0;
} //(3)
```

这样的写法中，如果不考虑编译器的优化，是会调用一次构造，两次拷贝构造，三次析构函数
而

```c++
int main() {
    A&& a = GetA();
    return 0;
}
```

通过右值引用，比之前少了一次拷贝构造和一次析构，原因在于右值引用绑定了右值，让临时右值的生命周期延长了

### T(T&& a) : m_val(val)

```c++
class A
{
public:
    A():m_ptr(new int(0)){cout << "construct" << endl;}
    A(const A& a):m_ptr(new int(*a.m_ptr)) //深拷贝的拷贝构造函数
    {
        cout << "copy construct" << endl;
    }
    ~A(){ delete m_ptr;}
private:
    int* m_ptr;
};
int main() {
    A a = GetA();
    return 0;
}
```

> 输出：
> construct
> copy construct
> copy construct

一个带有堆内存的类，必须提供一个深拷贝拷贝构造函数，因为默认的拷贝构造函数是浅拷贝，会发生“指针悬挂”的问题。如果不提供深拷贝的拷贝构造函数，上面的测试代码将会发生错误（编译选项-fno-elide-constructors），内部的m_ptr将会被删除两次，一次是临时右值析构的时候删除一次，第二次外面构造的a对象释放时删除一次，而这两个对象的m_ptr是同一个指针，这就是所谓的指针悬挂问题。提供深拷贝的拷贝构造函数虽然可以保证正确，但是在有些时候会造成额外的性能损耗，因为有时候这种深拷贝是不必要的

```c++
class A
{
public:
    A() :m_ptr(new int(0)){}
    A(const A& a):m_ptr(new int(*a.m_ptr)) //深拷贝的拷贝构造函数
    {
        cout << "copy construct" << endl;
    }
    A(A&& a) :m_ptr(a.m_ptr)
    {
        a.m_ptr = nullptr;
        cout << "move construct" << endl;
    }
    ~A(){ delete m_ptr;}
private:
    int* m_ptr;
};
int main(){
    A a = Get(false); 
} 
```

> 输出：
> construct
> move construct
> move construct

移动构造函数并没有做深拷贝，仅仅是将指针的所有者转移到了另外一个对象，同时，将参数对象a的指针置为空，这里仅仅是做了浅拷贝，因此，这个构造函数避免了临时变量的深拷贝问题

> 需要注意的一个细节是，我们提供移动构造函数的同时也会提供一个拷贝构造函数，以防止移动不成功的时候还能拷贝构造，使我们的代码更安全。

### std::move

普通的左值是否也能借助移动语义来优化性能呢，那该怎么做呢？事实上C++11为了解决这个问题，提供了std::move方法来将左值转换为右值，从而方便应用移动语义。move是将对象资源的所有权从一个对象转移到另一个对象，只是转移，没有内存的拷贝，这就是所谓的move语义

### std::forward

```c++
template <typename T>void f(T&& val){ foo(std::forward<T>(val)); }
```

c++11前

```c++
template <typename T>
void forwardValue(T& val)
{
    processValue(val); //右值参数会变成左值 
}
template <typename T>
void forwardValue(const T& val)
{
    processValue(val); //参数都变成常量左值引用了 
}
```

都不能按照参数的本来的类型进行转发
C++11引入了完美转发：在函数模板中，完全依照模板的参数的类型（即保持参数的左值、右值特征），将参数传递给函数模板中调用的另外一个函数。C++11中的std::forward正是做这个事情的，他会按照参数的实际类型进行转发

```c++
void processValue(int& a){ cout << "lvalue" << endl; }
void processValue(int&& a){ cout << "rvalue" << endl; }
template <typename T>
void forwardValue(T&& val)
{
    processValue(std::forward<T>(val)); //照参数本来的类型进行转发。
}
void Testdelcl()
{
    int i = 0;
    forwardValue(i); //传入左值 
    forwardValue(0);//传入右值 
}
```

> 输出：
> lvaue
> rvalue

## background
https://zhuanlan.zhihu.com/p/85809752
STL 的目标就是要把数据和算法分开，分别对其进行设计，之后通过一种名为 iterator 的东西，把这二者再粘接到一起。

设计模式中，关于 iterator 的描述为：一种能够顺序访问容器中每个元素的方法，使用该方法不能暴露容器内部的表达方式。而类型萃取技术就是为了要解决和 iterator 有关的问题的。

它将范型算法(find, count, find_if)用于某个容器中,最重要的是要给算法提供一个访问容器元素的工具，iterator 就扮演着这个重要的角色。

而在算法中我们可能会定义简单的中间变量或者设定算法的返回变量类型，这时候需要知道迭代器所指元素的类型是什么，但是由于没有 typeof 这类判断类型的函数,我们无法直接获取，那该如何是好？本文就来具体阐述。

对于迭代器来说就是一种智能指针，因此，它也就拥有了一般指针的所有特点——能够对其进行*和->操作。但是在遍历容器的时候，不可避免的要对遍历的容器内部有所了解，所以，干脆把迭代器的开发工作交给容器的设计者好了，如此以来，所有实现细节反而得以封装起来不被使用者看到，这正是为什么每一种 STL 容器都提供有专属迭代器的缘故。

下面一些点会比较简略

1. 模板函数的参数推导机制
2. 内嵌型别

## 1.template 参数推导

首先，在算法中运用迭代器时，很可能会用到其相应型别（associated type）（迭代器所指之物的型别）。假设算法中有必要声明一个变量，以"迭代器所指对象的型别"为型别，该怎么办呢？

解决方法是：利用 function template 的参数推导机制。

例如：

如果 T 是某个指向特定对象的指针，那么在 func 中需要指针所指向对象的型别的时候，怎么办呢？这个还比较容易，模板的参数推导机制可以完成任务，

```c++
template <class I>
inline
void func(I iter) {
    func_impl(iter, *iter); // 传入iter和iter所指的值，class自动推导
}
```

通过模板的推导机制，我们轻而易举的或得了指针所指向的对象的类型。

```c++
template <class I, class T>
void func_impl(I iter, T t) {
        T tmp; // 这里就是迭代器所指物的类别
        // ... 功能实现
}

int main() {
    int i;
    func(&i);
}
```

但是，函数的"template 参数推导机制"推导的只是参数，无法推导函数的返回值类型。万一需要推导函数的传回值，就无能为力了。因此，我们引出下面的方法。

## 2.声明内嵌型别

迭代器所指对象的型别，称之为迭代器的 value type。

尽管在 func_impl 中我们可以把 T 作为函数的返回值，但是问题是用户需要调用的是 func。

```c++
template <class I, class T>
T func_impl(I iter, T t) {
        T tmp; // 这里就是迭代器所指物的类别
        // ... 功能实现
}
template <class T>
(*T) func(T t) { // !!!Wrong code
    return func_impl(t, *t); // forward the task to func_impl
}
int main() {
    int i  =10;
    cout<<func(&i)<<endl; // !!! Can’t pass compile
}
```

如果去编译上述代码，编译失败！

这个问题解决起来也不难，声明内嵌型别似乎是个好主意，这样我们就可以直接获取。只要做一个 iterator，然后在定义的时候为其指向的对象类型制定一个别名，就好了，像下面这样：
```c++
template <class T>
struct MyIter {
    typedef T value_type; // 内嵌型别声明
    T* ptr;
    MyIter(T* p = 0) : ptr(p) {}
    T& operator*() const { return *ptr; }
};

template <class I>
typename I::value_type
func(I ite) {
    std::cout << "class version" << std::endl;
    return *ite;
}
int main() {
    // ...
    MyIter<int> ite(new int(8));
    cout << func(ite);    // 输出8
}
```

很漂亮的解决方案，看上去一切都很完美。但是，实际上还是有问题，因为 func 如果是一个泛型算法，那么它也绝对要接受一个原生指针作为迭代器，但是显然，你无法让下面的代码编译通过：
```c++
int *p = new int(5);
cout<<func(p)<<endl; // error
```

我们的 func 无法支持原生指针，这显然是不能接受的。此时，template partial specialization 就派上了用场。



## Traits编程技法
因为模板函数的参数推导机制的一些限制，当return的型别为模版时，就会束手无策
解决这一问题
### Partial Specialization （模板偏特化）
含义: 当class template 拥有一个以上的template参数，可以针对其中某个或者数个template进行特化（而不是所有，因为所有都特化那还需要写啥模板 0-0!）

### C++ typedef typename 作用
在traits的写法中我们可以见到
```cpp
template <class T>
struct itertools_traits{
    typedef typename I::value_type value_type;
}
```

其中 `typedef typename I::value_type value_type`就是这里的用法
为什么要加  `typename`

> 实际上，模板类型在实例化之前，编译器并不知道vector`<T>`::size_type是什么东西，事实上一共有三种可能：
>
> 1. 静态成员变量 2. 静态成员函数 3. 嵌套类型
>    语句的真是面目是：
>    typedef创建了存在类型的别名，而typename告诉编译器I::value_type是一个类型而不是一个成员。

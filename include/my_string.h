#include <iostream>
#include <string.h>
using namespace std;

class MyString
{
public:
        MyString(const char *ptr = nullptr); //通配构造函数
        MyString(const MyString &str); //拷贝构造函数
        MyString &operator=(const MyString &str); //=复制函数
        // 触发move语义，src被掏空了
        MyString(MyString &&src);
        friend ostream &operator<<(ostream &, MyString &); //重载<<运算符
        friend istream &operator>>(istream &, MyString &); //重载>>运算符
        size_t size() const; //获取字符的长度
        const char *c_str(); //转化成c字符串
        MyString &operator+=(const MyString &str); //+=元素符重载
        bool operator==(const MyString &str); //==运算符重载
        ~MyString(); //析构函数
private:
        char *data_; //实际字符串内容
        size_t length_; //字符串的长度
};
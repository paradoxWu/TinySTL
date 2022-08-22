/*
实现一个string类
构造，析构，拷贝构造，拷贝赋值，移动构造，移动赋值，后置++， c_str()函数，可以强转为const char*
*/

#include <iostream>
#include <string.h>
using namespace std;

class MyString{
  public:
    MyString(const char* ptr = nullptr); //通配构造函数
    MyString(const MyString& str); //拷贝构造函数
    MyString & operator=(const MyString & str);//=复制函数
    friend ostream& operator<< (ostream&,MyString&);//重载<<运算符  
    friend istream& operator>> (istream&,MyString&);//重载>>运算符  
    size_t size() const; //获取字符的长度
    const char* c_str();//转化成c字符串
    MyString & operator+=(const MyString& str);//+=元素符重载
    bool operator==(const MyString& str);//==运算符重载
    ~MyString(); //析构函数
  private:
    char* data_;     //实际字符串内容
    size_t length_;  //字符串的长度
};

MyString::MyString(const char* ptr){
    if(!ptr){
        data_ = new char[1];
        *data_ = '\0';
        this->length_ = 0;
    }else{
        this->length_ = strlen(ptr);
        this->data_ = new char[this->length_ + 1];
        strcpy(this->data_,ptr);
    }
}

MyString::MyString(const MyString& str){
    if(!str.data_){
        this->data_ = new char[1];
        *(this->data_) = '\0';
    }else{
        this->length_ = strlen(str.data_);
        this->data_ = new char[length_ + 1];
        strcpy(this->data_,str.data_);
    }
}

MyString::~MyString() //析构函数
{
    if(this->data_){
        delete []data_;
        data_ = nullptr;
        length_ = 0;
    }

}

MyString & MyString::operator=(const MyString & str){
    if(this != &str){
        this->length_ = strlen(str.data_);
        this->data_ = new char[this->length_ + 1];
        strcpy(this->data_,str.data_);
    }
    return *this;  //自己赋值自身，直接返回该对象即可
}

//重载<<运算符
ostream& operator<< (ostream& os,MyString& str){
    os<<str.data_;
    return os;
}
//重载>>运算符  
istream& operator>> (istream& is ,MyString& str){
    //该用法是错误的is>>str.data;
    //因为不能确定str.data和输入的字符串的大小
    char tmp[1000] = {0};
    is>>tmp;
    str.length_ = strlen(tmp);
    str.data_ = new char[str.length_ + 1];
    strcpy(str.data_,tmp);
    return is;
    
}

const char* MyString::c_str(){
  return this->data_;
}

int main(){
  MyString a;
  std::cout << "a is " << a << std::endl;
  string input = "test1";
  MyString b(input.data());
  std::cout << "b is " << b << std::endl;

  a = b;
  std::cout << "a is " << a << std::endl;
  const char* mystr = a.c_str();
  std::cout << "mystr is " << mystr << std::endl;
  return 0;
  // MyString c = std::move(b);
  // std::cout << "c is "<< c << std::endl;
  // std::cout << "b is " << b << std::endl;

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
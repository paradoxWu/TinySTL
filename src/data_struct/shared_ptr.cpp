#include <iostream>

template<typename T>
class SharedPtr
{
public:
    explicit SharedPtr();
    explicit SharedPtr(T *ptr);
    SharedPtr(const SharedPtr &p);
    SharedPtr(SharedPtr &&p);
    ~SharedPtr();

    SharedPtr& operator=(const SharedPtr &ptr);

    T& operator*();
    T* operator->();

    operator bool() const;
    
    T* get() const;

    size_t use_count() const;

    bool unique();

    void swap(SharedPtr &p);

private:
    size_t count_;
    T *ptr_;
};

template<typename T>
SharedPtr<T>::SharedPtr(): count_(0),ptr_(nullptr) {}

template<typename T>
SharedPtr<T>::SharedPtr(T *ptr): count_(1),ptr_(ptr) {}

template<typename T>
SharedPtr<T>::~SharedPtr()
{
    this->count_--;
    if(this->count_ == 0){
        delete this->ptr_;
        this->ptr_ = nullptr;
    }
    std::cout<<"shared prt destory."<<std::endl;
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr &p)
{ 
    this->count_ = p.count_;
    this->ptr_ = p.ptr_;
    ++(count_);
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr &&p)
{
    if(this!= &p){
        this->count_ = p.count_;
        this->ptr_ = p.ptr_;
    }
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr &p)
{
    if(this->ptr_ = p.ptr_){
        return *this;
    }

    if(p){
        this->count_--;
        if(this->count_==0){
            delete this->ptr_;
            delete this->count_;
        }
    }

    this->ptr_ = p.ptr_;
    this->count_ = p.count_;
    this->count_++;
    return *this;
}

template<typename T>
T& SharedPtr<T>::operator*()
{
    return *this->ptr_;
}

template<typename T>
T* SharedPtr<T>::operator->()
{
    return this->ptr_;
}

template<typename T>
SharedPtr<T>::operator bool() const
{
    return this->ptr_ != nullptr;
}

template<typename T>
T* SharedPtr<T>::get() const
{
    return this->ptr_;
}

template<typename T>
size_t SharedPtr<T>::use_count() const
{
    return this->count_;
}

template<typename T>
bool SharedPtr<T>::unique()
{
    return this->count_ == 1;
}

template<typename T>
void SharedPtr<T>::swap(SharedPtr& p)
{
    std::swap(*this, p);
}
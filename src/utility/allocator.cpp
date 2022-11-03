#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>

using namespace std;

namespace WYH
{

template <class T> 
inline T *_allocate(ptrdiff_t size, T *)
{
        // make sure it will throw an exception when allocing mermory fails.
        set_new_handler(nullptr);
        // 分配内存 可以opertor new也可以 malloc
        T *tmp = static_cast<T *>(::operator new(static_cast<size_t>(size) * sizeof(T)));
        if (tmp == nullptr) {
                std::cerr << "out of memory" << std::endl;
                std::exit(1);
        }
        return tmp;
}

template <class T> 
inline void _deallocate(T *buffer)
{
        ::operator delete(buffer);
}

template <class T1, class T2> 
inline void _construct(T1 *ptr, const T2 &value)
{
        new (ptr) T1(value);
}

template <class T> 
inline void _destroy(T *ptr)
{
        ptr->~T();
}

template <class T> 
class allocator
{
public:
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;

        template <class U> struct rebind {
                typedef allocator<U> other;
        };

        pointer allocate(size_t n, const void *hint = 0)
        {
                return _allocate(static_cast<ptrdiff_t>(n), static_cast<pointer>(0));
        }

        void deallocate(pointer p, size_t n)
        {
                _deallocate(p);
        }

        void construct(pointer p, const T &value)
        {
                _construct(p, value);
        }
        void destroy(pointer p)
        {
                _destroy(p);
        }

        pointer address(reference x)
        {
                return (pointer)&x;
        }

        const_pointer const_address(const_reference x)
        {
                return (const_pointer)&x;
        }

        unsigned long max_size()
        {
                return static_cast<unsigned long>(UINT_MAX / sizeof(T));
        }
};
} // end of namespace WYH
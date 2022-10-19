
template<typename Item>
struct ListIter
{
    Item* ptr; //keep a reference to Container

    ListIter(Item* t=nullptr) : ptr(t) {}

    // no need to realize copy and operator=

    Item& operator*() const { return *ptr; }
    Item* operator->() const { return ptr; }

    ListIter& operator++() { ptr = ptr->next(); return *this; }

    ListIter& operator++(int){ListIter tmp = *this; ++*this;return tmp;}

    bool operator==(const ListIter& lhs) const { return ptr == lhs.ptr; }

    bool operator!=(const ListIter& lhs) const { return ptr != lhs.ptr; }
};

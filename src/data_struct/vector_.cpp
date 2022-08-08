#include <stdlib.h>


template<class value_type>
class Vector
{
    public:
        Vector(){

        }

        Vector(size_t n){
            this->size = n;
            this->begin = static_cast<value_type*>(malloc(n*sizeof(value_type)));
            this->end = this->begin + n*sizeof(value_type);
        }

        ~Vector(){
            free(this->begin);
            this->begin = nullptr;
            this->cur = nullptr;
            this->end = nullptr;
        }

        bool empty(){
            return begin==end;
        }

        value_type front(){
            return *begin;
        }

        value_type back(){
            return *(end-sizeof(value_type));
        }

        value_type &operator [](size_t index){
            return *(begin+index*sizeof(value_type));
        }

        void clear(){
            free(this->begin);
            this->begin = nullptr;
            this->cur = nullptr;
            this->end = nullptr;
        }

        // void resize(){

        // }    
        void push_back(const value_type &value){
            if(begin==nullptr){
                this->size = 1;
                this->begin = static_cast<value_type*>(malloc(sizeof(value_type)));
                this->end = this->begin + sizeof(value_type);
                this->cur = this->begin;
            }
            if(cur==end){
                this->begin = static_cast<value_type*>(realloc(this->begin,2*this->size*sizeof(value_type)));
                this->end = this->begin + 2*this->size*sizeof(value_type);
            }
            *cur = value;
            cur += sizeof(value_type);
        }

        // void pop_back(){

        // }


        // void erase(size_t index){

        // }

        // void insert(size_t index){
    
        // }
    private:
        size_t size = 0;
        value_type *begin = nullptr;
        value_type *cur = nullptr; //the last one element which has the value
        value_type *end = nullptr ; // the last one which can fill in value
};
//
// Created by 12den on 03-Mar-22.
//

#pragma once

using namespace std;

template<typename Vector>
class VectorIterator{
public:
    using valueType = typename Vector::valueType;
    using pointerType = valueType*;
    using referenceType = valueType&;
private:
    pointerType l_Ptr;
public:
    VectorIterator(pointerType ptr)
        :l_Ptr(ptr) {}

    VectorIterator& operator++(){
        l_Ptr++;
        return *this;
    }

    VectorIterator operator++(int){
        VectorIterator iterator = *this;
        ++(*this);
        return iterator;
    }

    VectorIterator& operator--(){
        l_Ptr--;
        return *this;
    }

    VectorIterator operator--(int){
        VectorIterator iterator = *this;
        --(*this);
        return iterator;
    }

    referenceType operator[](int index){
        return *(l_Ptr+index);
    }

    pointerType operator->(){
        return l_Ptr;
    }

    referenceType operator*(){
        return *l_Ptr;
    }

    pointerType operator-(int a){
        return l_Ptr-a;
    }

    pointerType operator+(int a){
        return l_Ptr+a;
    }

    int operator-(VectorIterator<Vector> a){
        return l_Ptr-a.l_Ptr;
    }

    pointerType operator+=(int a){
        l_Ptr += a;
        return l_Ptr;
    }

    pointerType operator-=(int a){
        l_Ptr -= a;
        return l_Ptr;
    }

    bool operator == (const VectorIterator& other) const{
        return l_Ptr==other.l_Ptr;
    }

    bool operator != (const VectorIterator& other) const{
        return l_Ptr!=other.l_Ptr;
    }

    bool operator <= (const VectorIterator& other) const{
        return l_Ptr<=other.l_Ptr;
    }

    bool operator >= (const VectorIterator& other) const{
        return l_Ptr>=other.l_Ptr;
    }

    bool operator > (const VectorIterator& other) const{
        return l_Ptr>other.l_Ptr;
    }
    bool operator < (const VectorIterator& other) const{
        return l_Ptr<other.l_Ptr;
    }
};

template<typename T, int list_capacity = 10>
class Vector{
public:
    using valueType = T;
    using Iterator = VectorIterator<Vector<T>>;
private:
    T* list;
    size_t l_Size;
    size_t l_Cap;
private:

    void swap(T &a, T &b){
        T temp = a;
        a = b;
        b = temp;
    }

    void alloc(size_t newsize){
        //resizes array keeping current elements
        if(l_Size == newsize)
            return;

        T* newlist = new T[newsize];

        if(l_Size > newsize){
            l_Size = newsize;
        }

        for(auto i = 0; i<l_Size && i <newsize;i++)
            new(&newlist[i]) T(move(list[i]));

        delete[] list;
        list = newlist;
        l_Cap = newsize;
    }

    void index_check(int index){
        //check if index is out of range and throws out_of_range exception as needed
        if(0 > index || index >= l_Size)
            throw out_of_range("index err");
    }

    int Partition(int start, int end, bool reverse){
        auto piv = list[end];
        auto piv_index = start ;

        for(int i = start ; i < end;i++)
            if((list[i] <= piv )== !reverse){
                swap(list[i], list[piv_index]);
                piv_index++;
            }
        swap(list[end], list[piv_index]);
        return piv_index;
    }

    void quicksort(int start, int end, bool reverse){
        if(start < end){
            int middle = Partition(start, end, reverse);
            quicksort(start, middle-1, reverse);
            quicksort(middle + 1, end, reverse);
        }
    }

public:
    Vector(){
        //constructor
        list = new T[list_capacity];
        l_Size = 0;
        l_Cap = list_capacity;
    }

    //destructor
    ~Vector(){
        clear();
        delete[] list;
    }

    size_t capacity(){
        //return current maximum size
        return l_Cap;
    }

    size_t size(){
        //return current size(number of elements in array)
        return l_Size;
    }

    size_t resize(size_t newsize){
        //changes the current size keeping old elements on the same positions
        //returns the old size
        size_t oldsize = l_Size;
        alloc(newsize);
        return oldsize;
    }

    T max(){
        //returns the maximum element in the array
        //if the array is empty it throws an error
        if(l_Size == 0){
            throw runtime_error("List is empty");
        }
        T maxim = list[0];
        for(auto i = begin(); i < end(); i++)
            if(maxim < *i){
                maxim = *i;
            }
        return maxim;
    }

    T min(){
        //returns the minimum element in the array
        //if the array is empty it throws an error
        if(l_Size == 0){
            throw runtime_error("List is empty");
        }
        T minim = list[0];
        for(auto i = begin(); i < end(); i++)
            if(minim > *i){
                minim = *i;
            }
        return minim;
    }

    T pop(int index = -1){
        //deletes the element at the given index
        //if no index is given the last element is deleted
        //returns deleted element
        if(index == -1){
            return list[--l_Size];
        }
        index_check(index);
        T element = list[index];
        for(auto i = Iterator(list+index);i < end()-1; i++){
            *i = move(*(i+1));
        }
        return element;
    }

    void insert(int index, T element){
        //inserts given element before the element at the given index
        index_check(index);
        for(auto i = end() --;i > Iterator(list + index); i--){
            *i = move(*(i-1));
        }
        list[index] = element;
        l_Size++;
    }

    void pushback(T element){
        //inserts an element at the back of the array
        if(l_Size >= l_Cap){
            alloc(2*l_Size);
        }
        list[++l_Size - 1] = element;
    }

    void clear(){
        for(auto i = 0;i < l_Size; i++)
            list[i].~T();
        l_Size = 0;
    }

    template<typename... Args>
    void emplaceback(Args&&... args){
        //creates array element type(ex. structs) from given arguments and inserts it at the back
        if(l_Size >= l_Cap){
            alloc(2*l_Size);
        }
        new(&list[++l_Size - 1]) T(forward<Args>(args)...);
    }

    T& operator[](size_t index){
        //enables use of [] for normal elements
        index_check(index);
        return list[index];
    }


    const T& operator[](size_t index) const{
        //enables use of [] for const elements
        index_check(index);
        return list[index];
    }

    friend ostream &operator<<(ostream &out, const Vector& v){
        //function for printing using standard "cout"
        for(int i=0; i<v.l_Size; i++)
            out << v.list[i] << " ";
        return out;
    }

    void fill(T element){
        //replaces all elements with given element
        for(auto i = begin(); i < end(); i++){
            *i = element;
        }
    }

    int search(T element){
        for(auto i = 0; i < l_Size; i++){
            if(list[i] == element)
                return i;
        }
        return NULL;
    }

    int rsearch(T element){
        for(auto i = rbegin(); i > rend(); i--){
            if(*i == element)
                return i- begin();
        }
        return NULL;
    }

    Vector<int> search_all(T element){
        auto ilist = new Vector<int, 10>;
        for(auto i = begin(); i < end(); i++){
            if(*i == element)
                (*ilist).pushback(i -begin());
        }
        return *ilist;
    }

    void sort(int start = 0, int end = -1){
        if(end == -1)
            end = l_Size - 1;
        index_check(start);
        index_check(end);
        quicksort(start, end, false);
    }

    void rsort(int start = 0, int end = -1){
        if(end == -1)
            end = l_Size - 1;
        index_check(start);
        index_check(end);
        quicksort(start, end, true);
    }

    Iterator begin(){
        //returns an iterator at the first element of array
        return Iterator(list);
    }

    Iterator rbegin(){
        //returns an iterator at the last element of array
        return Iterator(list+l_Size) - 1;
    }

    Iterator end(){
        //returns an iterator at the end of the array
        return Iterator(list + l_Size);
    }

    Iterator rend(){
        //returns an iterator at the beginning of the array
        return Iterator(list) - 1;
    }
};




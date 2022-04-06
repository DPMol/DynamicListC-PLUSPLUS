#pragma once
#include <functional>
#include <iostream>
#include <cstring>

//Iterator
template<typename array>
class array_iterator{
public:
    using value_type = typename array::value_pointer;
    using value_pointer = value_type*;
    using value_reference = typename array::value_type&;

private:
    value_pointer iterator_pointer;

public:

    /**
     * Constructor for array iterator.
     * @param ptr Pointer to array.
     */
    explicit array_iterator(value_pointer ptr):iterator_pointer(ptr) {}

    /**
     * Allows use of dereference*  operator.
     * @return Dereferenced value.
     */
    typename array::value_type& operator*(){
        return **iterator_pointer;
    }

    /**
     * Alows use of rvalue ++ operator.
     * @return Returns incremented pointer.
     */
    array_iterator& operator++(){
        iterator_pointer++;
        return *this;
    }

    /**
     * Alows use of lvalue ++ operator.
     * @return Returns pointer before incrementation.
     */
    array_iterator operator++(int){
        array_iterator temp = *this;
        ++(*this);
        return temp;
    }

    /**
     * Alows use of rvalue -- operator.
     * @return Returns decremented pointer.
     */
    array_iterator& operator--(){
        iterator_pointer--;
        return *this;
    }

    /**
     * Alows use of lvalue -- operator.
     * @return Returns pointer before decrementation.
     */
    array_iterator operator--(int){
        array_iterator temp = *this;
        --(*this);
        return temp;
    }

    /**
     * Allows subtraction between pointer and integer.
     * @param int_value Integer to be subtracted.
     * @return Returns pointer after subtraction.
     */
    value_pointer operator-(long long int_value){
        return iterator_pointer - int_value;
    }

    /**
     * Allows addition between pointer and integer.
     * @param int_value Integer to be added.
     * @return Returns pointer after addition.
     */
    value_pointer operator+(long long int_value){
        return iterator_pointer + int_value;
    }

    /**
     * Allows subtraction between 2 pointers
     * @param other Pointer to be subtracted
     * @return Returns pointer after subtraction
     */
    int operator-(array_iterator other){
        return iterator_pointer - other.iterator_pointer;
    }

    /**
     * Allows use of operator [] to access iterator elements.
     * @param index Index at which element is situated.
     * @return Reference of element at given index.
     */
    value_reference operator[](long long index){
        return **(iterator_pointer+index);
    }

    /**
     * Allows use of < operator.
     * @param other Rvalue iterator.
     * @return Result of comparison.
     */
    bool operator < (const array_iterator& other) const{
        return iterator_pointer<other.iterator_pointer;
    }

    /**
     * Allows use of -> operator.
     * @return (*iterator).
     */
    array_iterator operator->(){
        return *iterator_pointer;
    }

    /**
     * Allows use of += operation.
     * @param int_value Integer to be added.
     * @return Iterator pointer after operation.
     */
    value_pointer operator+=(long long int_value){
        iterator_pointer += int_value;
        return iterator_pointer;
    }

    /**
     * Allows use of -= operation.
     * @param int_value Integer to be subtracted.
     * @return Iterator pointer after operation.
     */
    value_pointer operator-=(long long int_value){
        iterator_pointer -= int_value;
        return iterator_pointer;
    }

    /**
     * Allows use of -= operation between iterators.
     * @param other Iterator to be subtracted.
     * @return Iterator pointer after operation.
     */
    value_pointer operator-=(const array_iterator other){
        iterator_pointer -= other;
        return iterator_pointer;
    }

    /**
     * Allows use of == operator.
     * @param other Rvalue iterator.
     * @return Result of comparison.
     */
    bool operator == (const array_iterator& other) const{
        return iterator_pointer==other.iterator_pointer;
    }

    /**
     * Allows use of != operator.
     * @param other Rvalue iterator.
     * @return Result of comparison.
     */
    bool operator != (const array_iterator& other) const{
        return iterator_pointer!=other.iterator_pointer;
    }

    /**
     * Allows use of <= operator.
     * @param other Rvalue iterator.
     * @return Result of comparison.
     */
    bool operator <= (const array_iterator& other) const{
        return iterator_pointer<=other.iterator_pointer;
    }

    /**
     * Allows use of >= operator.
     * @param other Rvalue iterator.
     * @return Result of comparison.
     */
    bool operator >= (const array_iterator& other) const{
        return iterator_pointer>=other.iterator_pointer;
    }

    /**
     * Allows use of > operator.
     * @param other Rvalue iterator.
     * @return Result of comparison.
     */
    bool operator > (const array_iterator& other) const{
        return iterator_pointer>other.iterator_pointer;
    }
};

template <typename T>
class array {
public:
    using value_type = T;
    using value_pointer = T*;
    using iterator = array_iterator<array<T>>;

private:
    //representation
    value_pointer *list = nullptr;
    long long list_size;
    long long list_capacity;

//Functions
private:

    /**
     * Allocates more space for internal array and copies all elements.
     * @param new_capacity New maximum size.\n
     * Must be greater than old capacity.
     */
    void realloc(const long long new_capacity) {
        auto *new_list = (value_pointer *) ::operator new(new_capacity * sizeof(value_pointer));

        for (auto i = 0; i < list_size; i++)
            new_list[i] = list[i];

        ::operator delete(list, list_capacity * sizeof(value_pointer));
        list = new_list;
        list_capacity = new_capacity;
    }

    /**
     * Checks if given index is in the array scope.
     * @param index Index to be checked.
     */
    void index_check(long long index) {
        //check if index is out of range and throws out_of_range exception as needed
        if (index < 0 || index >= list_size)
            throw std::out_of_range("index err");
    }

    /**
     * Swaps the values of the two given pointers.
     * @param a First pointer.
     * @param b Second pointer.
     */
    void swap(value_pointer& a, value_pointer& b){
        value_pointer temp = a;
        a = b;
        b = temp;
    }

public:

    /**
     * Creates and returns an object of class array.
     */
    array() {
        list_size = 0;
        list_capacity = 140;
        realloc(list_capacity);
    }

    /**
     * Copy constructor.
     * @param other Other class to be copied.
     */
    array(const array<value_type> &other) {
        list_size = 0;
        list_capacity = other.list_capacity;
        realloc(list_capacity);
        list_size = other.list_size;
        for (auto i = 0; i < list_size; i++) {
            list[i] = (value_pointer) ::operator new(sizeof(value_type));
            new(list[i]) value_type(*other.list[i]);
        }
    }

    /**
     * Allows use of == operator between arrays.
     * @param other Array to be compared.
     * @return True if both arrays contain the same list.\na
     * False otherwise.
     */
    bool operator==(const array<value_type> &other) const{

        if(list_size!=other.list_size)
            return false;

        for(auto i = 0; i <list_size; i++)
            if (*list[i] != *other.list[i])
                return false;


        return true;
    }

    /**
     * Copy constructor.
     * @param other Array to be copied.
     * @return Returns destination array reference after copy.
     */
    array& operator=(const array<value_type> &other){
        if(this == &other)
            return *this;
        clear();
        for(auto i = 0; i < other.list_size; i++){
            push_back(*other.list[i]);
        }
        list_size = other.list_size;
        return *this;
    }

    /**
     * Destroys object of class array.
     */
    ~array() {
        clear();
        ::operator delete(list, list_capacity * sizeof(value_pointer));
        //delete[] list;
    }

    /**
     * Destroys all elements of the array.
     */
    void clear() {
        for (auto i = 0; i < list_size; i++) {
            list[i]->~T();
            ::operator delete(list[i], sizeof(value_type));
        }
        list_size = 0;
    }

    /**
     * Returns the number of elements currently in the array.
     * @return Number of elements.
     */
    long long size() {
        return list_size;
    }

    /**
     * Inserts given value as the last element by copying.
     * @param value Element to be inserted.
     */
    void push_back(const value_type &value) {

        if (list_size >= list_capacity) {
            realloc(2 * list_capacity);
        }
        list[list_size] = (value_pointer) ::operator new(sizeof(value_type));
        new(list[list_size++]) value_type(value);
    }

    /**
     * Inserts given value as the last element by moving.
     * @param value Element to be inserted.
     */
    void push_back(value_type &&value) {

        if (list_size >= list_capacity) {
            realloc(2 * list_capacity);
        }
        list[list_size] = (value_pointer) ::operator new(sizeof(value_type));
        new(list[list_size++]) value_type(std::move(value));
    }

    template<typename... Args>
    void emplace_back(Args&&... args){
        if (list_size >= list_capacity) {
            realloc(2 * list_capacity);
        }
        list[list_size] = (value_pointer) ::operator new(sizeof(value_type));
        new(list[list_size++]) value_type(value_type(std::forward<Args>(args)...));
    }

    /**
     * Destroys last element of the array.
     */
    void pop_back() {
        list[--list_size]->~T();
        ::operator delete(list[list_size], sizeof(value_type));
    }

    /**
     * Destroys element at given position.\n
     * Shifts other elements to the left to fill the created gap.
     * @param position Position of element to be destroyed.
     */
    void pop(const long long position) {
        index_check(position);
        list[position]->~T();
        ::operator delete(list[position], sizeof(value_type));
        memmove(list + position, list + position + 1, sizeof(value_pointer) * (list_size-- - position));
    }

    /**
     * Inserts given element before the given position.
     * @param value Element to be inserted.
     * @param positon Position where element is inserted.
     */
    void insert(const value_type &value, const long long position) {
        if (list_size >= list_capacity) {
            realloc(2 * list_capacity);
        }

        memmove(list + position + 1, list + position, sizeof(value_pointer) * (list_size++ - position));
        /*
        for(auto i = list_size; i > position; i--)
            list[i] = list[i - 1];
        */

        list[position] = new value_type;
        new(list[position]) value_type(value);

    }

    /**
     * Return a reference to the first element in array.
     * @return First element of array.
     */
    value_type &front() {
        return *list[list_size - 1];
    }

    /**
     * Return a const reference to the first element in array.
     * @return First element of array.
     */
    const value_type &front() const {
        return *list[0];
    }

    /**
     * Return a reference to the last element in array.
     * @return Last element of array.
     */
    value_type &back() {
        return *list[list_size - 1];
    }

    /**
     * Return a const reference to the last element in array.
     * @return Last element of array.
     */
    const value_type &back() const {
        return *list[list_size - 1];
    }


    /**
     * Allows use of operator [] to access array elements.
     * @param index Index at which element is situated.
     * @return Reference of element at given index.
     */
    value_type &operator[](long long index) {
        //enables use of [] for normal elements
        index_check(index);
        return *list[index];
    }

    /**
     * Allows use of operator [] to access array elements.
     * @param index Index at which element is situated.
     * @return Const reference of element at given index.
     */
    const value_type &operator[](long long index) const {
        //enables use of [] for const elements
        index_check(index);
        return *list[index];
    }

    /**
     * Return an iterator at the start of the array.
     * @return Begin iterator.
     */
    iterator begin() const{
        return iterator(list);
    }

    /**
     * Return an iterator just outside the end of the array.
     * @return End iterator.
     */
    iterator end() const{
        return iterator(list + list_size);
    }

    /**
     * Replaces all current elements with given element.
     * @param value Element to be put in the array.
     */
    void fill(const value_type &value) {
        for (auto i = 0; i < list_size; i++) {
            list[i]->~T();
            new(list[i]) value_type(value);
        }
    }

    /**
     * Return an iterator at the end of the array.
     * @return Reverse begin iterator.
     */
    iterator rbegin() const{
        return iterator(list + list_size - 1);
    }

    /**
     * Return an iterator just outside the start of the array.
     * @return Reverse end iterator.
     */
    iterator rend() const{
        return iterator(list - 1);
    }

    /**
     * Function that allows std::cout<< for array.
     * @param out Operator from std::cout.
     * @param arr Reference to array.
     * @return Array elements converted to std::cout.
     */
    friend std::ostream &operator<<(std::ostream &out, const array &arr) {
        out << "[";
        for (long long i = 0; i < arr.list_size - 1; i++)
            out << *(arr.list[i]) << ", ";
        if (arr.list_size > 0)
            out << arr.back();
        out << "]";
        return out;
    }

//    /**
//     * Function that allows std::fout<< for array.
//     * @param out Operator from std::fout.
//     * @param arr Reference to array.
//     * @return Array elements converted to std::fout.
//     */
//    friend std::ofstream &operator<<(std::ofstream &out, const array &arr) {
//        out << [;
//        for (long long i = 0; i < arr.list_size - 1; i++)
//            out << *(arr.list[i]) << ", ";
//        if (arr.list_size > 0)
//            out << arr.back();
//        out << "]";
//        return out;
//    }

    /**
     * Sort function using interchange sort.
     * @param cmp Optional compare parameter.\n
     * Must return an integer and contain 2 elements of array type as parameters.
     */
    void sort(std::function<int(const value_type& , const value_type&)> cmp = [](const value_type& a, const value_type& b){return a < b;}){
        for(int i = 0; i < list_size; i++)
            for(int j = 0; j < list_size; j++)
                if(!cmp(*list[i], *list[j]))
                    swap(list[i], list[j]);
    }

    /**
     * Sort function that also accepts reverse parameter.
     * @param reverse Reverse parameter.
     * @param cmp Optional compare parameter.\n
     * Must return an integer and contain 2 elements of arrays type as parameters.
     */
    void sort(bool reverse, std::function<int(const value_type& , const value_type&)> cmp = [](const value_type& a, const value_type& b){return a < b;}){
        std::cout<<"alin\n";
        for(int i = 0; i < list_size; i++)
            for(int j = 0; j < list_size; j++)
                if(!cmp(*list[i], *list[j]) == reverse)
                    swap(list[i], list[j]);
        std::cout<<"bota\n";
    }

    /**
     * Reverse the array.
     */
    void reverse(){
        for(long long i = 0, j = list_size - 1; i < j ; i++, j--)
            swap(list[i], list[j]);
    }

    /**
     * Creates a new array filtered with given function.
     * @param cmp Filter function.\n
     * Must return integer and accept 1 element of arrays type as parameter.
     * @return New filtered list.
     */
    array filter_get(std::function<int(const value_type)> cmp){
        array<value_type> new_array;
        for(auto i: *this)
            if(cmp(i))
                new_array.push_back(i);

        return new_array;
    }

    /**
     * Filters array with given function.
     * @param cmp Filter function.\n
     * Must return integer and accept 1 element of arrays type as parameter.
     */
    void filter(std::function<int(const value_type)> cmp){
        long long i = 0;
        while(i<list_size)
            if(!cmp(*list[i]))
                pop(i);
            else
                i++;
    }

    /**
     * Return position of first instance of given value in array.\n
     * If no instance is found function will return -1.
     * @param value Element to be searched.
     * @return Position of value in array.
     */
    long long search(const value_type& value){
        long long i = 0;
        while(i < list_size){

            if(*list[i] == value)
                return i;
            i++;
        }
        return -1;
    }

    /**
     * Return position of last instance of given value in array.\n
     * If no instance is found function will return -1.
     * @param value Element to be searched.
     * @return Position of value in array.
     */
    long long rsearch(const value_type& value){
        long long i = list_size - 1;
        while(i >= 0){
            if(*list[i] == value)
                return i;
        }
        return -1;
    }
};



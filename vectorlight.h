#ifndef VECTORLIGHT_H
#define VECTORLIGHT_H

/* VECTOR LIGHTWEIGHT IMPLEMENTATION
 * Barebones vector functionality (think 'unbounded stack').
 * Also no C++11 features :(
 * Made by Alan Chen
 */

#include <stdlib.h>

template <typename Type>
class VectorLight {
public:
    VectorLight(); // Constructor (there is no way to initilize vector with values)
    size_t size(); // return size
    Type* begin(); // Give pointer to internal array
    Type* end(); // Give pointer to end of array
    size_t capacity(); // Give allocated size
    bool empty(); // Test whether vector is empty
    void push_back(Type); // add to end
    Type pop_back(); // remove from back
    Type &operator[](size_t); // Returns a reference to the element at position n in the vector
    Type& at(size_t); // Returns a reference to the element at position n in the vector. Also checks if in-bounds
    Type* insert(Type* pos, Type value);
    Type& front(); // return reference to front
    Type& back(); // return reference to back
    Type* data(); // Give pointer to internal array
    void assign (size_t n, Type value);  // The new contents are n elements, each initialized to a copy of value
    void clear(); // Remove and deallocate all data
private:
    size_t length;
    size_t max_length;
    Type* array;
    void vector_resize();
};

#endif // VECTORLIGHT_H

#include "vectorlight.h"
#include <stdlib.h>

/* CONSTRUCTORS */

// Initialize empty vector
template <typename Type>
VectorLight<Type>::VectorLight() {
    length = 0;
    max_length = 2;
    array = new Type[max_length];
}

/* ITERATORS (or pointers in this implementation) */

// Give pointer to beginning of array
template <typename Type>
Type* VectorLight<Type>::begin() {
    return &array[0];
}

// Give pointer to next element position
template <typename Type>
Type* VectorLight<Type>::end() {
    return &array[length];
}

/* CAPACITY */

// Give size
template <typename Type>
size_t VectorLight<Type>::size() {
    return length; // Use overflow
}

// Give size allocated.
template <typename Type>
size_t VectorLight<Type>::capacity() {
    return max_length;
}

// Test if vector is empty.
template <typename Type>
bool VectorLight<Type>::empty() {
    return length == 0;
}

/* ELEMENT ACCESS */

// Returns a reference to the element at position n in the vector container.
// Yes, this can go out of bounds.
template <typename Type>
Type &VectorLight<Type>::operator[](size_t index) {
    return array[index];
}

// Returns a reference to the element at position n in the vector.
// The function automatically checks whether n is within the bounds of valid elements in the vector.
template <typename Type>
Type& VectorLight<Type>::at(size_t index) {
    try {
        if(index >= length) {
            throw "index out of bounds of vector.";
        }
        return array[index];
    }
    catch (int e) {
        //std::cout << "Error! Exception: " << e << '\n';
    }
}

// Returns a reference to the last element in the vector.
// Calling this function on an empty vector causes undefined behavior.
template <typename Type>
Type& VectorLight<Type>::front() {
    return array[0];
}

// Returns a direct reference to the last element in the vector.
// Unlike member end(), which returns a pointer just past this element, this function returns a direct reference.
// Calling this function on an empty vector causes undefined behavior.
template <typename Type>
Type& VectorLight<Type>::back() {
    return array[length];
}

// Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
template <typename Type>
Type* VectorLight<Type>::data() {
    return array;
}

/* MODIFIERS */

// The new contents are n elements, each initialized to a copy of val.
template <typename Type>
void VectorLight<Type>::assign (size_t n, Type value) {
    clear();
    for(size_t i = 0; i < n; i++) {
        push_back(value);
    }
}

// Adds a new element at the end of the vector, after its current last element. The content of val is copied (or moved) to the new element.
template <typename Type>
void VectorLight<Type>::push_back(Type value) {
    array[length] = value;
    length++;
    vector_resize();
    return;
}

// Removes the last element in the vector, effectively reducing the container size by one.
template <typename Type>
Type VectorLight<Type>::pop_back() {
    length--;
    Type trash = array[length];
    vector_resize();
    return trash;
}

// The vector is extended by inserting new elements before the element at the specified position, effectively increasing the container size by the number of elements inserted.
template <typename Type>
Type* VectorLight<Type>::insert(Type* pos, Type value) {
    Type* iterator = begin();
    int index = 0;
    int indexNew = 0;
    Type* newArr = new Type[max_length];
    while(iterator != end()) {
        if(iterator == pos) {
            newArr[indexNew] = value;
            indexNew++;
            length++;
        }
        newArr[indexNew] = array[index];
        index++;
        indexNew++;
        iterator++;
    }
    delete[] array;
    array = newArr;
    vector_resize();
    return pos;
}

// Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
template <typename Type>
void VectorLight<Type>::clear() {
   while(length != 0) {
       pop_back();
   }
}

// Resizes vector
template <typename Type>
void VectorLight<Type>::vector_resize() {
    if(length == max_length) {
        max_length = length * 2;
        Type* newArr = new Type[max_length];
        for(int i = 0; i < length; i++) {
            newArr[i] = array[i];
        }
        delete array;
        array = newArr;
    } else if(length < max_length/4) {
        max_length =  max_length / 2;
        Type* newArr = new Type[max_length];
        for(int i = 0; i < length; i++) {
            newArr[i] = array[i];
        }
        delete[] array;
        array = newArr;
    }
    return;
}

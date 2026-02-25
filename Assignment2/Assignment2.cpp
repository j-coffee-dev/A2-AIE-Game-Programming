//Assignment 2 for AIE Game Programming Course - 2026

#include <iostream>
#include <cassert>
using namespace std;

int linear_search(int* array, int size, int target) {
    /////////////////////////////////////////////////
    /// @brief  Takes in an array, if target is an element of the array returns the index 
    ///         index where it first occurs, else return -1.
    ///
    /// @param  array  : A pointer to the first element of an array of type int.
    /// @param  size   : The number of elements in array.
    /// @param  target : Element to search for.
    /// 
    /// @return  if target first occurs as element array[i] return index i,
    ///          else return -1 if target doesn't equal any element.
    /////////////////////////////////////////////////
    for (int i = 0; i < size; i++) {
        if (array[i] == target) {
            return i;
        }
    }
    return -1;
}

int main()
{
    //Question 6 - Linear Search
    const int num_of_elements = 20;
    int arr[num_of_elements] = { 67,13,3,89,43,2,19,71,5,61,97,7,37,31,17,11,83,53,23,29 };
    assert(linear_search(arr, num_of_elements, 3) == 2);
    assert(linear_search(arr, num_of_elements, 7) == 11);
    assert(linear_search(arr, num_of_elements, 67) == 0);
    assert(linear_search(arr, num_of_elements, 88) == -1);
    cout << "ASSERTS PASSED: LINEAR SEARCH ELEMENTS ARE IN CORRECT LOCATIONS." << endl;
}

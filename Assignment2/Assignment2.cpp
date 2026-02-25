//Assignment 2 for AIE Game Programming Course - 2026

#include <iostream>
#include <cassert>
#include <string>
using namespace std;

int linear_search(int* array, int size, int target) {
    /////////////////////////////////////////////////
    /// @brief  Takes in an array, if target is an element of the array returns the index 
    ///         index where it first occurs, else return -1.
    ///
    /// @param  array  : A pointer to the array to be searched.
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
void search_for_targ(int* array, int size) {
    /////////////////////////////////////////////////
    /// @brief  Loops through user input and searches the array 
    ///         for the input using linear_search.
    ///         Print to let user know if that element was found.
    ///
    /// @param  array  : A pointer to the array to be searched.
    /// @param  size   : The number of elements in array.
    /// 
    /// @return  Nothing.
    /////////////////////////////////////////////////

    string target;
    int target_int;
    cout << "Continue entering values to search the array for (type Q to quit): " << endl;

    while(true){
        cin >> target;
        try {
            target_int = stoi(target);
        }
        catch (...) {
            break;
        }
        int result = linear_search(array, size, target_int);
        if (result == -1) { cout << "Result not found." << endl; }
        else { cout << "Result found at index " << result << endl; }
    }
}

void swap_integers(int& a, int& b) {
    /////////////////////////////////////////////////
    /// @brief  Swaps the values of two integers.
    ///
    /// @param  a : First integer to be swapped.
    /// @param  b : Second integer to be swapped.
    /// 
    /// @return  No return. Original variables are modified
    ///          as they are passed by reference.
    /////////////////////////////////////////////////

    int temp;
    temp = a;
    a = b;
    b = temp;
}

void bubble_sort(int* array, int size) {
    /////////////////////////////////////////////////
    /// @brief  Sorts an integer array from smallest
    ///         to largest.
    ///
    /// @param  array : The array to be sorted.
    /// @param  size  : Size of the sorted array.
    /// 
    /// @return  No return. Original array is modified
    ///          via swap_integers.
    /////////////////////////////////////////////////

    bool swapped = true;

    do {
        swapped = false;
        for (int i = 0; i < size - 1; i++) {
            if (array[i] > array[i + 1]) {
                swap_integers(array[i], array[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

int main()
{
    //Question 6 - Linear Search
    cout << "---------------------------Question 6---------------------------" << endl;
    const int num_of_elements = 20;
    int arr[num_of_elements] = { 67,13,3,89,43,2,19,71,5,61,97,7,37,31,17,11,83,53,23,29 };
    assert(linear_search(arr, num_of_elements, 3) == 2);
    assert(linear_search(arr, num_of_elements, 7) == 11);
    assert(linear_search(arr, num_of_elements, 67) == 0);
    assert(linear_search(arr, num_of_elements, 88) == -1);
    cout << endl << "linear_search ASSERTS PASSED" << endl;

    search_for_targ(arr, num_of_elements);

    //Question 7 - Bubble Sort
    cout << "---------------------------Question 7---------------------------" << endl;
    bubble_sort(arr, num_of_elements);

    for (int i = 0; i < num_of_elements-1; i++) {
            assert(arr[i] <= arr[i + 1]);
    }
    cout << "bubble_sort ASSERTS PASSED" << endl;
}

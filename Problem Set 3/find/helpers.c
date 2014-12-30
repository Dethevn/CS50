/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int array[], int n)
{
    // TODO: implement a searching algorithm
    if (n < 0)
        return false;
   
    int min = 0;
    int max = n - 1;
    
    // when max == min, array will be size 1 with just the value in the array (step 10)
    while (max >= min)
    {
        int mid = min + ((max - min) / 2);
        if (array[mid] == value)
            return true;
        else if (array[mid] > value)
            max = mid - 1;
        else
            min = mid + 1;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n) sorting algorithm
    const int MAX = 65536;
    int sortedarray[65536] = {0};
    int counter = 0;
    
    // Loop through the original array; at index values in sorted array equal to value in original array
    // increment the value at that index by 1 for each occurence of the value in original array
    for (int i = 0; i < n; i++)
        sortedarray[values[i]]++;  
         
    // Loop through sorted array
    for (int i = 0; i < MAX; i++)
    {
        // When there is only a count of 1 at that index in sorted array, assign it to the old array
        if (sortedarray[i] == 1)
        {
            values[counter] = i;
            counter++;
        }
        // When there is more than 1 count at that index (old array had duplicate values), assign that index  
        // value that many times to the old array. 
        else if (sortedarray[i] > 1)
        {
            for (int j = 0, k = sortedarray[i]; j < k; j++)
                {
                values[counter] = i;
                counter++;
                }
        }
    }
    
    for (int i = 0; i < n; i++)
        printf("%i\n", values[i]);
        
    printf("\n");  
}

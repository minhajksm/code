// http://www.geeksforgeeks.org/dynamic-programming-set-15-longest-bitonic-subsequence/

// Given an array arr[0 ... n-1] containing n positive integers, a subsequence
// of arr[] is called Bitonic if it is first increasing, then decreasing. Write
// a function that takes an array as argument and returns the length of the
// longest bitonic subsequence.

// A sequence, sorted in increasing order is considered Bitonic with the
// decreasing part as empty. Similarly, decreasing order sequence is considered
// Bitonic with the increasing part as empty.

// Examples:
// Input arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
// Output: 6 (A Longest Bitonic Subsequence of length 6 is 1, 2, 10, 4, 2, 1)
// Input arr[] = {12, 11, 40, 5, 3, 1}
// Output: 5 (A Longest Bitonic Subsequence of length 5 is 12, 11, 5, 3, 1)
// Input arr[] = {80, 60, 30, 40, 20, 10}
// Output: 5 (A Longest Bitonic Subsequence of length 5 is 80, 60, 30, 20, 10)


#include <iostream>
using namespace std;


/* lbs() returns the length of the Longest Bitonic Subsequence in
   arr[] of size n. The function mainly creates two temporary arrays
   lis[] and lds[] and returns the maximum lis[i] + lds[i] - 1.

   lis[i] ==> Longest Increasing subsequence ending with arr[i]
   lds[i] ==> Longest decreasing subsequence starting with arr[i]
*/
int lbs( int arr[], int n )
{
    int i, j;

    /* Allocate memory for LIS[] and initialize LIS values as 1 for
       all indexes */
    int *lis = new int[n];
    for ( i = 0; i < n; i++ )
        lis[i] = 1;

    /* Compute LIS values from left to right */
    for ( i = 1; i < n; i++ )
        for ( j = 0; j < i; j++ )
            if ( arr[i] > arr[j] && lis[i] < lis[j] + 1)
                lis[i] = lis[j] + 1;

    /* Allocate memory for lds and initialize LDS values for
       all indexes */
    int *lds = new int [n];
    for ( i = 0; i < n; i++ )
        lds[i] = 1;

    /* Compute LDS values from right to left */
    for ( i = n-2; i >= 0; i-- )
        for ( j = n-1; j > i; j-- )
            if ( arr[i] > arr[j] && lds[i] < lds[j] + 1)
                lds[i] = lds[j] + 1;


    /* Return the maximum value of lis[i] + lds[i] - 1*/
    int max = lis[0] + lds[0] - 1;
    for (i = 1; i < n; i++)
        if (lis[i] + lds[i] - 1 > max)
            max = lis[i] + lds[i] - 1;
    return max;
}



class MySolution {
public:
    int lbs(int arr[], int n) {

        int lis[n], lds[n];

        for (int i = 0; i < n; i++) {
            lis[i] = 1;
            lds[i] = 1;
        }

        // compute longest increasing subsequence
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[i] > arr[j] && lis[j] + 1 > lis[i]) {
                    lis[i] = lis[j] + 1;
                }
            }
        }

        // compute longest decreasing subsequence
        for (int i = n - 2; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                if (arr[i] > arr[j] && lds[j] + 1 > lds[i]) {
                    lds[i] = lds[j] + 1;
                }
            }
        }

        // compute longest bitonic subsequence by going through every
        // array element
        int max_len = -1;
        for (int i = 0; i < n; i++) {
            if (lis[i] + lds[i] - 1 > max_len) {
                max_len = lis[i] + lds[i] - 1;
            }
        }

        return max_len;
    }

private:
    int max(int a, int b) {
        return a > b ? a : b;
    }
};


/* Driver program to test above function */
int main() {

    MySolution solution;
    int arr[] = {0,2,1,4,6,6,7,5,34,34,5,24,6,56,34,65,7,56,84,7,5,63};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("Length of LBS is %d\n", solution.lbs(arr, n));
    printf("Length of LBS is %d\n", lbs(arr, n));
    return 0;
}

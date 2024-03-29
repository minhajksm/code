// http://www.geeksforgeeks.org/dynamic-programming-set-17-palindrome-partitioning/

// Given a string, a partitioning of the string is a palindrome partitioning
// if every substring of the partition is a palindrome. For example,
// "aba|b|bbabb|a|b|aba" is a palindrome partitioning of "ababbbabbababa".
// Determine the fewest cuts needed for palindrome partitioning of a given
// string. For example, minimum 3 cuts are needed for "ababbbabbababa". The
// three cuts are "a|babbbab|b|ababa". If a string is palindrome, then minimum
// 0 cuts are needed. If a string of length n containing all different characters,
// then minimum n-1 cuts are needed.


#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


static const char alphanum[] =
    "0123456789"
    "!@#$%^&*"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

char genRandom(void) {
    return alphanum[rand() % stringLength];
}

void genString(char str[], int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        str[i] = genRandom();
    }
}


// A utility function to get minimum of two integers
int min (int a, int b) { return (a < b)? a : b; }

// Returns the minimum number of cuts needed to partition a string
// such that every part is a palindrome
int minPalPartion(char *str)
{
    // Get the length of the string
    int n = strlen(str);

    /* Create two arrays to build the solution in bottom up manner
       C[i][j] = Minimum number of cuts needed for palindrome partitioning
       of substring str[i..j]
       P[i][j] = true if substring str[i..j] is palindrome, else false
       Note that C[i][j] is 0 if P[i][j] is true */
    int C[n][n];
    bool P[n][n];

    int i, j, k, L; // different looping variables

    // Every substring of length 1 is a palindrome
    for (i=0; i<n; i++)
    {
        P[i][i] = true;
        C[i][i] = 0;
    }

    /* L is substring length. Build the solution in bottom up manner by
       considering all substrings of length starting from 2 to n.
       The loop structure is same as Matrx Chain Multiplication problem (
       See http://www.geeksforgeeks.org/archives/15553 )*/
    for (L=2; L<=n; L++)
    {
        // For substring of length L, set different possible starting indexes
        for (i=0; i<n-L+1; i++)
        {
            j = i+L-1; // Set ending index

            // If L is 2, then we just need to compare two characters. Else
            // need to check two corner characters and value of P[i+1][j-1]
            if (L == 2)
                P[i][j] = (str[i] == str[j]);
            else
                P[i][j] = (str[i] == str[j]) && P[i+1][j-1];

            // IF str[i..j] is palindrome, then C[i][j] is 0
            if (P[i][j] == true)
                C[i][j] = 0;
            else
            {
                // Make a cut at every possible localtion starting from i to j,
                // and get the minimum cost cut.
                C[i][j] = INT_MAX;
                for (k=i; k<=j-1; k++)
                    C[i][j] = min (C[i][j], C[i][k] + C[k+1][j]+1);
            }
        }
    }

    // Return the min cut value for complete string. i.e., str[0..n-1]
    return C[0][n-1];
}


class MySolution {
public:
    int minPalPartion(char str[]) {

        int n = strlen(str);
        int **cache = new int *[n];
        for (int i = 0; i < n; i++) {
            cache[i] = new int[n];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cache[i][j] = -1;
            }
        }
        return minPalPartionHelper(str, 0, n-1, cache);
    }

    int minPalPartionDP(char str[]) {

        int n = strlen(str);
        int table[n][n];        // substring str[i...j]
        bool isPD[n][n];        // if substring is palindrome

        // initialize arrays
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {   // only one character, true
                    table[i][j] = 0;
                    isPD[i][j] = true;
                } else {
                    table[i][j] = INT_MAX;
                    isPD[i][j] = false;
                }
            }
        }

        for (int cl = 2; cl <= n; cl++) {
            for (int i = 0; i < n - cl + 1; i++) {

                int j = i + cl - 1;

                // compute if str[i..j] is palindrome
                if (cl == 2) {
                    isPD[i][j] = (str[i] == str[j]);
                } else {
                    isPD[i][j] = (str[i] == str[j] && isPD[i+1][j-1]);
                }

                if (isPD[i][j] == true) {
                    table[i][j] = 0;
                } else {
                    for (int k = i; k < j; k++) { // different cut point
                        table[i][j] = min(table[i][j],
                                          table[i][k] + table[k+1][j] + 1);
                    }
                }
            }
        }

        return table[0][n-1];
    }

private:
    int min(int a, int b) {
        return a < b ? a : b;
    }

    bool isPalindrome(char str[], int i, int j) {

        while (i <= j) {
            if (str[i] != str[j]) {
                return false;
            } else {
                i++;
                j--;
            }
        }
        return true;
    }

    int minPalPartionHelper(char str[], int i, int j, int **cache) {

        if (cache[i][j] != -1) {
            return cache[i][j];
        }

        if (isPalindrome(str, i, j) == true) {
            cache[i][j] = 0;
            return 0;
        }

        int min_cut = INT_MAX;
        for (int k = i; k < j; k++) {
            int cut = minPalPartionHelper(str, i, k, cache) +
                minPalPartionHelper(str, k + 1, j, cache) + 1;
            if (cut < min_cut) {
                min_cut = cut;
            }
        }

        cache[i][j] = min_cut;
        return min_cut;
    }
};


// Driver program to test above function
int main()
{
    MySolution solution;
    //char str[] = "ababbbabbabababaa";
    char str[100];
    genString(str, 100);

    printf("Min cuts needed for Palindrome Partitioning is %d\n",
           minPalPartion(str));
    printf("Min cuts needed for Palindrome Partitioning is %d\n",
           solution.minPalPartion(str));
    printf("Min cuts needed for Palindrome Partitioning is %d\n",
           solution.minPalPartionDP(str));
    return 0;
}

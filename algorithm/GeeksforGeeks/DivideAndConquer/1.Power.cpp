// http://www.geeksforgeeks.org/write-a-c-program-to-calculate-powxn/

// Write a C program to calculate pow(x,n)
// Below solution divides the problem into subproblems of size y/2 and call
// the subproblems recursively.


#include <stdio.h>

/* Function to calculate x raised to the power y */
int power1(int x, unsigned int y)
{
    if( y == 0)
        return 1;
    else if (y%2 == 0)
        return power1(x, y/2)*power1(x, y/2);
    else
        return x*power1(x, y/2)*power1(x, y/2);

}

// Time Complexity: O(n)
// Space Complexity: O(1)
// Algorithmic Paradigm: Divide and conquer.


// Above function can be optimized to O(logn) by calculating power(x, y/2) only
// once and storing it.

// Function to calculate x raised to the power y in O(logn)
int power2(int x, unsigned int y)
{
    int temp;
    if ( y == 0)
        return 1;
    temp = power2(x, y/2);
    if (y%2 == 0)
        return temp*temp;
    else
        return x*temp*temp;
}

// Time Complexity of optimized solution: O(logn)
// Let us extend the pow function to work for negative y and float x.

// Extended version of power function that can work for float x and negative y
float power3(float x, int y)
{
    float temp;
    if ( y == 0)
        return 1;
    temp = power3(x, y/2);

    if (y%2 == 0)
        return temp*temp;
    else
    {
        if(y > 0)
            return x*temp*temp;
        else
            return (temp*temp)/x;
    }
}


class MySolution {
public:
    float power(float x, int y) {

        float temp = 0;

        if (y == 0) {
            return 1;
        } else if (y == 1) {
            return x;
        } else if (y % 2 == 0) {
            temp = power(x, y/2);
            return temp * temp;
        } else {
            temp = power(x, y/2);
            if (y < 0)
                return (temp * temp) / x;
            return temp * temp * x;
        }
    }
};


/* Program to test function power */
int main()
{
    float x = 2;
    int y = -3;
    MySolution solution;

    printf("%f\n", solution.power(x, y));

    return 0;
}

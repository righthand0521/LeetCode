#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DYNAMIC_PROGRAMMING (1)
#define MATH (1)
int numSquares(int n) {
    int retVal = 0;

    if (n <= 0) {
        return retVal;
    }

#if (DYNAMIC_PROGRAMMING)
    printf("DYNAMIC_PROGRAMMING\n");

    int i, j;
    int dp[n + 1];
    dp[0] = 0;
    for (i = 1; i <= n; ++i) {
        dp[i] = n + 1;
    }
    for (i = 1; i <= n; ++i) {
        for (j = 1; (j * j) <= i; ++j) {
            dp[i] = fmin(dp[i], (dp[i - (j * j)] + 1));
        }
    }
    retVal = dp[n];
#elif (MATH)
    printf("MATH\n");

    /* Lagrange's four-square theorem: https://en.wikipedia.org/wiki/Lagrange%27s_four-square_theorem
     *  Lagrange's four-square theorem, also known as Bachet's conjecture, states that
     *  every natural number can be represented as the sum of four integer squares.
     *  That is, the squares form an additive basis of order four.
     *  p = a0^2 + a1^2 + a2^2 + a3^2 where the four numbers a0, a1, a2, a3 are integers.
     */

    int squareRoot = sqrt(n);
    if (squareRoot * squareRoot == n) {
        retVal = 1;
        return retVal;
    }

    /* Legendre's three-square theorem: https://en.wikipedia.org/wiki/Legendre%27s_three-square_theorem
     *  In mathematics, Legendre's three-square theorem states that
     *  a natural number can be represented as the sum of three squares of integers
     *  n = x^2 + y^2 + z^2 if and only if n is not of the form n = (4^a)*(8b + 7) for nonnegative integers a and b.
     */
    while (n % 4 == 0) {
        n /= 4;
    }
    if (n % 8 == 7) {
        retVal = 4;
        return retVal;
    }

    /* Fermat's theorem on sums of two squares: https://en.wikipedia.org/wiki/Fermat%27s_theorem_on_sums_of_two_squares
     *  In additive number theory, Fermat's theorem on sums of two squares states that
     *  an odd prime p can be expressed as
     *  p = x^2 + y^2 with x and y integers, if and only if p = 1 (mod 4)
     */
    squareRoot = sqrt(n);
    int num, numSquare;
    int i;
    for (i = 1; i <= squareRoot; ++i) {
        num = n - (i * i);
        numSquare = sqrt(num);
        if (numSquare * numSquare == num) {
            retVal = 2;
            return retVal;
        }
    }

    retVal = 3;
#endif

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{12}, {13}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 12
     *  Output: 3
     *
     *  Input: n = 13
     *  Output: 2
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = numSquares(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}

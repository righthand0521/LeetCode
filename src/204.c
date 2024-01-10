#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countPrimes(int n) {
    int retVal = 0;

    if ((n == 0) || (n == 1)) {
        return retVal;
    }

    int i, j;

    /* https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
     *
     *  input: an integer n > 1.
     *  output: all prime numbers from 2 through n.
     *
     *  let A be an array of Boolean values, indexed by integers 2 to n, initially all set to true.
     *  for i = 2, 3, 4, ..., not exceeding √n do
     *      if A[i] is true
     *          for j = i^2, i^2+i, i^2+2i, i^2+3i, ..., not exceeding n do
     *              set A[j] := false
     *
     *  return all i such that A[i] is true.
     */
    bool isPrime[n + 1];
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = false;
    isPrime[1] = false;
    for (i = 2; i * i <= n; ++i) {
        if (isPrime[i] == true) {
            for (j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    for (i = 0; i < sizeof(isPrime) - 1; ++i) {
        if (isPrime[i] == true) {
            ++retVal;
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{10}, {0}, {1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = countPrimes(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> sieve(int upperLimit) {
        vector<int> retVal(upperLimit + 1, 1);  // Initiate an int array to mark prime numbers

        // 0 and 1 are not prime
        retVal[0] = 0;
        retVal[1] = 0;
        for (int number = 2; number * number <= upperLimit; number++) {
            if (retVal[number] == 0) {
                continue;
            }

            // Mark all multiples of 'number' as non-prime
            for (int multiple = number * number; multiple <= upperLimit; multiple += number) {
                retVal[multiple] = 0;
            }
        }

        return retVal;
    }

   public:
    vector<int> closestPrimes(int left, int right) {
        vector<int> retVal(2, -1);

        // Step 1: Get all prime numbers up to 'right' using sieve
        int upperLimit = right;
        vector<int> sieveArray = sieve(upperLimit);

        vector<int> primeNumbers;  // Store all primes in the range [left, right]
        for (int num = left; num <= right; num++) {
            // If number is prime add to the primeNumbers list
            if (sieveArray[num] == 1) {
                primeNumbers.push_back(num);
            }
        }
        int primeNumbersSize = primeNumbers.size();

        // Step 2: Find the closest prime pair
        if (primeNumbersSize < 2) {
            return retVal;
        }

        int minDifference = numeric_limits<int>::max();
        for (int index = 1; index < primeNumbersSize; index++) {
            int difference = primeNumbers[index] - primeNumbers[index - 1];
            if (difference < minDifference) {
                minDifference = difference;
                retVal[0] = primeNumbers[index - 1];
                retVal[1] = primeNumbers[index];
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int left;
        int right;
    };
    vector<subject> testData{{10, 19}, {4, 6}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: left = 10, right = 19
     *  Output: [11,13]
     *
     *  Input: left = 4, right = 6
     *  Output: [-1,-1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: left = " << testData[i].left << ", right = " << testData[i].right << "\n";

        answer = cSolution.closestPrimes(testData[i].left, testData[i].right);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   private:
    int MODULO = 1e9 + 7;

    long long powerOfModulo(long long base, long long exponent) {
        long long retVal = 1;

        // Calculate the exponentiation using binary exponentiation
        while (exponent > 0) {
            // If the exponent is odd, multiply the result by the base
            if (exponent % 2 == 1) {
                retVal = ((retVal * base) % MODULO);
            }

            // Square the base and halve the exponent
            base = (base * base) % MODULO;
            exponent /= 2;
        }

        return retVal;
    }

   public:
    int maximumScore(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();

        // Calculate the prime score for each number in nums
        vector<int> primeScores(numsSize);
        for (int index = 0; index < numsSize; index++) {
            int num = nums[index];
            // Check for prime factors from 2 to sqrt(n)
            for (int factor = 2; factor <= sqrt(num); factor++) {
                if (num % factor != 0) {
                    continue;
                }
                // Increment prime score for each prime factor
                primeScores[index]++;
                // Remove all occurrences of the prime factor from num
                while (num % factor == 0) {
                    num /= factor;
                }
            }
            // If num is still greater than or equal to 2, it's a prime factor
            if (num >= 2) {
                primeScores[index]++;
            }
        }

        // Initialize next and previous dominant index arrays
        vector<int> nextDominant(numsSize, numsSize);
        vector<int> prevDominant(numsSize, -1);
        // Stack to store indices for monotonic decreasing prime score
        stack<int> decreasingPrimeScoreStack;
        // Calculate the next and previous dominant indices for each number
        for (int index = 0; index < numsSize; index++) {
            // While the stack is not empty and the current prime score is greater than the stack's top
            while ((decreasingPrimeScoreStack.empty() == false) &&
                   (primeScores[decreasingPrimeScoreStack.top()] < primeScores[index])) {
                int topIndex = decreasingPrimeScoreStack.top();
                decreasingPrimeScoreStack.pop();
                // Set the next dominant element for the popped index
                nextDominant[topIndex] = index;
            }
            // If the stack is not empty, set the previous dominant element for the current index
            if (decreasingPrimeScoreStack.empty() == false) {
                prevDominant[index] = decreasingPrimeScoreStack.top();
            }
            // Push the current index onto the stack
            decreasingPrimeScoreStack.push(index);
        }

        // Calculate the number of subarrays in which each element is dominant
        vector<long long> numOfSubarrays(numsSize);
        for (int index = 0; index < numsSize; index++) {
            numOfSubarrays[index] = (long long)(nextDominant[index] - index) * (index - prevDominant[index]);
        }

        // Priority queue to process elements in decreasing order of their value
        priority_queue<pair<int, int>> processingQueue;
        // Push each number and its index onto the priority queue
        for (int index = 0; index < numsSize; index++) {
            processingQueue.push({nums[index], index});
        }

        // Process elements while there are operations left
        long long score = 1;
        while (k > 0) {
            // Get the element with the maximum value from the queue
            auto [num, index] = processingQueue.top();
            processingQueue.pop();
            // Calculate the number of operations to apply on the current element
            long long operations = min((long long)k, numOfSubarrays[index]);
            // Update the score by raising the element to the power of operations
            score = (score * powerOfModulo(num, operations)) % MODULO;
            // Reduce the remaining operations count
            k -= operations;
        }
        retVal = score;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{8, 3, 9, 3, 8}, 2}, {{19, 12, 14, 6, 10, 18}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [8,3,9,3,8], k = 2
     *  Output: 81
     *
     *  Input: nums = [19,12,14,6,10,18], k = 3
     *  Output: 4788
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maximumScore(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

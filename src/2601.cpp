#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool primeSubOperation(vector<int>& nums) {
        bool retVal = false;

        // Store the sieve array.
        int maxElement = *max_element(nums.begin(), nums.end());
        vector<int> sieve(maxElement + 1, 1);
        sieve[1] = 0;
        for (int i = 2; i <= sqrt(maxElement + 1); i++) {
            if (sieve[i] == 1) {
                for (int j = i * i; j <= maxElement; j += i) {
                    sieve[j] = 0;
                }
            }
        }

        // Start by storing the currValue as 1, and the initial index as 0.
        int currValue = 1;
        int numsSize = nums.size();
        int i = 0;
        while (i < numsSize) {
            // Store the difference needed to make nums[i] equal to currValue.
            int difference = nums[i] - currValue;
            // If difference is less than 0, then nums[i] is already less than currValue. Return false in this case.
            if (difference < 0) {
                return retVal;
            }

            // If the difference is prime or zero, then nums[i] can be made equal to currValue.
            // Otherwise, try for the next currValue.
            if (sieve[difference] == 1 or difference == 0) {
                i++;
                currValue++;
            } else {
                currValue++;
            }
        }
        retVal = true;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{4, 9, 6, 10}}, {{6, 8, 11, 12}}, {{5, 8, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [4,9,6,10]
     *  Output: true
     *
     *  Input: nums = [6,8,11,12]
     *  Output: true
     *
     *  Input: nums = [5,8,3]
     *  Output: false
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.primeSubOperation(testData[i].nums);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

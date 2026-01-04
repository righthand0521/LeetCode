#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int sumFourDivisors(vector<int>& nums) {
        int retVal = 0;

        for (int num : nums) {
            int factorCount = 0;
            int factorSum = 0;
            for (int i = 1; i * i <= num; ++i) {
                if (num % i != 0) {
                    continue;
                }
                factorCount++;
                factorSum += i;
                if (i * i != num) {
                    factorCount++;
                    factorSum += (num / i);
                }
            }
            if (factorCount == 4) {
                retVal += factorSum;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{21, 4, 7}}, {{21, 21}}, {{1, 2, 3, 4, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [21,4,7]
     *  Output: 32
     *
     *  Input: nums = [21,21]
     *  Output: 64
     *
     *  Input: nums = [1,2,3,4,5]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.sumFourDivisors(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

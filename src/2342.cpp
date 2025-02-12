#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int calculateDigitSum(int num) {
        int retVal = 0;

        while (num > 0) {
            retVal += num % 10;
            num /= 10;
        }

        return retVal;
    }

   public:
    int maximumSum(vector<int>& nums) {
        int retVal = -1;

        // Store numbers with their digit sums as pairs
        vector<pair<int, int>> digitSumPairs;
        for (int number : nums) {
            int digitSum = calculateDigitSum(number);
            digitSumPairs.push_back({digitSum, number});
        }
        sort(digitSumPairs.begin(), digitSumPairs.end());  // Sort based on digit sums, and if equal, by number value

        // Iterate through the sorted array to find the maximum sum of pairs
        int digitSumPairsSize = digitSumPairs.size();
        for (int index = 1; index < digitSumPairsSize; index++) {
            int currentDigitSum = digitSumPairs[index].first;
            int previousDigitSum = digitSumPairs[index - 1].first;
            // If two consecutive numbers have the same digit sum
            if (currentDigitSum == previousDigitSum) {
                int currentSum = digitSumPairs[index].second + digitSumPairs[index - 1].second;
                retVal = max(retVal, currentSum);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{18, 43, 36, 13, 7}}, {{10, 12, 19, 14}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [18,43,36,13,7]
     *  Output: 54
     *
     *  Input: nums = [10,12,19,14]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.maximumSum(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    void addMode(vector<int>& nums, int k, set<int>& modes, int value) {
        modes.insert(value);
        if (value - k >= nums.front()) {
            modes.insert(value - k);
        }
        if (value + k <= nums.back()) {
            modes.insert(value + k);
        }
    }
    int leftBound(vector<int>& nums, int value) {
        int retVal = 0;

        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int middle = (left + right) / 2;
            if (nums[middle] < value) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        retVal = left;

        return retVal;
    }
    int rightBound(vector<int>& nums, int value) {
        int retVal = 0;

        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int middle = (left + right + 1) / 2;
            if (nums[middle] > value) {
                right = middle - 1;
            } else {
                left = middle;
            }
        }
        retVal = left;

        return retVal;
    }

   public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int retVal = 0;

        int numsSize = nums.size();
        sort(nums.begin(), nums.end());

        unordered_map<int, int> numCount;
        set<int> modes;

        int lastNumIndex = 0;
        for (int i = 0; i < numsSize; ++i) {
            if (nums[i] == nums[lastNumIndex]) {
                continue;
            }
            numCount[nums[lastNumIndex]] = i - lastNumIndex;
            retVal = max(retVal, i - lastNumIndex);
            addMode(nums, k, modes, nums[lastNumIndex]);
            lastNumIndex = i;
        }

        numCount[nums[lastNumIndex]] = numsSize - lastNumIndex;
        retVal = max(retVal, numsSize - lastNumIndex);
        addMode(nums, k, modes, nums[lastNumIndex]);

        for (int mode : modes) {
            int left = leftBound(nums, mode - k);
            int right = rightBound(nums, mode + k);

            int tempAns;
            if (numCount.count(mode)) {
                tempAns = min(right - left + 1, numCount[mode] + numOperations);
            } else {
                tempAns = min(right - left + 1, numOperations);
            }
            retVal = max(retVal, tempAns);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
        int numOperations;
    };
    vector<subject> testData{{{1, 4, 5}, 1, 2}, {{5, 11, 20, 20}, 5, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,4,5], k = 1, numOperations = 2
     *  Output: 2
     *
     *  Input: nums = [5,11,20,20], k = 5, numOperations = 1
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << ", numOperations = " << testData[i].numOperations << "\n";

        answer = cSolution.maxFrequency(testData[i].nums, testData[i].k, testData[i].numOperations);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

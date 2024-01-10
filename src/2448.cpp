#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long getCost(int base, vector<int>& nums, vector<int>& cost) {
        long long retVal = 0;

        int numsSize = nums.size();
        for (int i = 0; i < numsSize; ++i) {
            retVal += ((long long)(abs(base - nums[i])) * cost[i]);
        }

        return retVal;
    }
    long long minCost(vector<int>& nums, vector<int>& cost) {
        long long retVal = 0;

        retVal = getCost(nums[0], nums, cost);
        int left = *min_element(nums.begin(), nums.end());
        int right = *max_element(nums.begin(), nums.end());

        while (left < right) {
            int middle = (left + right) / 2;

            long long costLeft = getCost(middle, nums, cost);
            long long costRight = getCost((middle + 1), nums, cost);
            retVal = min(costLeft, costRight);

            if (costLeft > costRight) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        vector<int> cost;
    };
    vector<subject> testData{{{1, 3, 5, 2}, {2, 3, 1, 14}}, {{2, 2, 2, 2, 2}, {4, 2, 8, 1, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,3,5,2], cost = [2,3,1,14]
     *  Output: 8
     *
     *  Input: nums = [2,2,2,2,2], cost = [4,2,8,1,3]
     *  Output: 0
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], cost = [";
        for (long unsigned int j = 0; j < testData[i].cost.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].cost[j];
        }
        cout << "]\n";

        answer = cSolution.minCost(testData[i].nums, testData[i].cost);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

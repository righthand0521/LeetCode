#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> frequencySort(vector<int>& nums) {
        vector<int> retVal = nums;

        unordered_map<int, int> frequency;
        for (int num : nums) {
            frequency[num]++;
        }

        sort(retVal.begin(), retVal.end(), [&](int a, int b) {
            if (frequency[a] == frequency[b]) {
                return a > b;
            }
            return frequency[a] < frequency[b];
        });

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 1, 2, 2, 2, 3}}, {{2, 3, 1, 3, 2}}, {{-1, 1, -6, 4, 5, -6, 1, 4, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,1,2,2,2,3]
     *  Output: [3,1,1,2,2,2]
     *
     *  Input: nums = [2,3,1,3,2]
     *  Output: [1,3,3,2,2]
     *
     *  Input: nums = [-1,1,-6,4,5,-6,1,4,1]
     *  Output: [5,-1,4,4,-6,-6,1,1,1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.frequencySort(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

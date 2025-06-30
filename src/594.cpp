#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int findLHS(vector<int>& nums) {
        int retVal = 0;

        unordered_map<int, int> frequency;
        for (int num : nums) {
            frequency[num]++;
        }

        for (auto [key, value] : frequency) {
            if (frequency.count(key + 1)) {
                retVal = max(retVal, value + frequency[key + 1]);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 3, 2, 2, 5, 2, 3, 7}}, {{1, 2, 3, 4}}, {{1, 1, 1, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,3,2,2,5,2,3,7]
     *  Output: 5
     *
     *  Input: nums = [1,2,3,4]
     *  Output: 2
     *
     *  Input: nums = [1,1,1,1]
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

        answer = cSolution.findLHS(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> retVal;

        for (int i = 0; i < n; ++i) {
            retVal.push_back(nums[i]);
            retVal.push_back(nums[i + n]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int n;
    };
    vector<subject> testData{{{2, 5, 1, 3, 4, 7}, 3}, {{1, 2, 3, 4, 4, 3, 2, 1}, 4}, {{1, 1, 2, 2}, 2}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], n = " << testData[i].n << "\n";

        answer = cSolution.shuffle(testData[i].nums, testData[i].n);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

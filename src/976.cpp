#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int largestPerimeter(vector<int>& nums) {
        int retVal = 0;

        // descending order
        sort(nums.begin(), nums.end(), greater<int>());
        for (long unsigned int i = 0; i < nums.size() - 2; ++i) {
            if (nums[i] < (nums[i + 1] + nums[i + 2])) {
                retVal = nums[i] + nums[i + 1] + nums[i + 2];
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 1, 2}}, {{1, 2, 1}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.largestPerimeter(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

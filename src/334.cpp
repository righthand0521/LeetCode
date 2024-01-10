#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    bool increasingTriplet(vector<int>& nums) {
        bool retVal = false;

        int first = numeric_limits<int>::max();
        int second = numeric_limits<int>::max();
        for (int num : nums) {
            if (num <= first) {
                first = num;
            } else if (num <= second) {
                second = num;
            } else {
                retVal = true;
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
    vector<subject> testData{{{1, 2, 3, 4, 5}}, {{5, 4, 3, 2, 1}}, {{2, 1, 5, 0, 4, 6}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,4,5]
     *  Output: true
     *
     *  Input: nums = [5,4,3,2,1]
     *  Output: false
     *
     *  Input: nums = [2,1,5,0,4,6]
     *  Output: true
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.increasingTriplet(testData[i].nums);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

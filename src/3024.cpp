#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    string none = "none";
    string equilateral = "equilateral";
    string isosceles = "isosceles";
    string scalene = "scalene";

   public:
    string triangleType(vector<int>& nums) {
        string retVal;

        sort(nums.begin(), nums.end());
        if (nums[0] + nums[1] <= nums[2]) {
            retVal = none;
        } else if (nums[0] == nums[2]) {
            retVal = equilateral;
        } else if ((nums[0] == nums[1]) || (nums[1] == nums[2])) {
            retVal = isosceles;
        } else {
            retVal = scalene;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 3, 3}}, {{3, 4, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,3,3]
     *  Output: "equilateral"
     *
     *  Input: nums = [3,4,5]
     *  Output: "scalene"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.triangleType(testData[i].nums);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

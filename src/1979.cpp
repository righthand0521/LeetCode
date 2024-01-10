#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findGCD(vector<int>& nums) {
        int retVal = 0;

        int minNums = *min_element(nums.begin(), nums.end());
        int maxNums = *max_element(nums.begin(), nums.end());
        retVal = __gcd(minNums, maxNums);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 5, 6, 9, 10}}, {{7, 5, 6, 8, 3}}, {{3, 3}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.findGCD(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

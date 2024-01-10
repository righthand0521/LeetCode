#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findNumbers(vector<int>& nums) {
        int retVal = 0;

        for (long unsigned int i = 0; i < nums.size(); ++i) {
            int tmp = nums[i];
            int count = 0;
            while (tmp > 0) {
                ++count;
                tmp /= 10;
            }
            if (count % 2 == 0) {
                ++retVal;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{12, 345, 2, 6, 7896}}, {{555, 901, 482, 1771}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.findNumbers(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
        vector<bool> retVal;

        int lSize = l.size();
        for (int i = 0; i < lSize; ++i) {
            retVal.emplace_back(true);

            int left = l[i];
            int right = r[i] + 1;
            vector<int> subarray(begin(nums) + left, begin(nums) + right);
            sort(subarray.begin(), subarray.end());

            int subarraySize = right - left;
            for (int j = 1; j < (subarraySize - 1); ++j) {
                if ((subarray[j] - subarray[j - 1]) != (subarray[j + 1] - subarray[j])) {
                    retVal[i] = false;
                    break;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        vector<int> l;
        vector<int> r;
    };
    vector<subject> testData{
        {{4, 6, 5, 9, 3, 7}, {0, 0, 2}, {2, 3, 5}},
        {{-12, -9, -3, -12, -6, 15, 20, -25, -20, -15, -10}, {0, 1, 6, 4, 8, 7}, {4, 4, 9, 7, 9, 10}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [4,6,5,9,3,7], l = [0,0,2], r = [2,3,5]
     *  Output: [true,false,true]
     *
     *  Input: nums = [-12,-9,-3,-12,-6,15,20,-25,-20,-15,-10], l = [0,1,6,4,8,7], r = [4,4,9,7,9,10]
     *  Output: [false,true,false,false,true,true]
     */

    Solution cSolution;
    vector<bool> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], l = [";
        for (long unsigned int j = 0; j < testData[i].l.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].l[j];
        }
        cout << "], r = [";
        for (long unsigned int j = 0; j < testData[i].r.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].r[j];
        }
        cout << "]\n";

        answer = cSolution.checkArithmeticSubarrays(testData[i].nums, testData[i].l, testData[i].r);

        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << ((answer[j] == true) ? "true" : "false");
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

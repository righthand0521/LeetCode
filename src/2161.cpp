#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        vector<int> retVal;

        int less = 0;
        int equal = 0;
        int greater = 0;
        for (int num : nums) {
            if (num < pivot) {
                equal++;
            } else if (num == pivot) {
                greater++;
            }
        }
        greater += equal;

        int numsSize = nums.size();
        retVal.assign(numsSize, 0);
        for (int num : nums) {
            if (num < pivot) {
                retVal[less] = num;
                less++;
            } else if (num > pivot) {
                retVal[greater] = num;
                greater++;
            } else {
                retVal[equal] = num;
                equal++;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int pivot;
    };
    vector<subject> testData{{{9, 12, 5, 10, 14, 3, 10}, 10}, {{-3, 4, 3, 2}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [9,12,5,10,14,3,10], pivot = 10
     *  Output: [9,5,3,10,10,12,14]
     *
     *  Input: nums = [-3,4,3,2], pivot = 2
     *  Output: [-3,2,4,3]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], pivot = " << testData[i].pivot << "\n";

        answer = cSolution.pivotArray(testData[i].nums, testData[i].pivot);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

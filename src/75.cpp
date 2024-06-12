#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    void swap(int* n1, int* n2) {
        int tmp = (*n1);
        (*n1) = (*n2);
        (*n2) = tmp;
    }

   public:
    void sortColors(vector<int>& nums) {
        int numsSize = nums.size();
        int ptr = 0;
        for (int i = 0; i < numsSize; ++i) {
            if (nums[i] == 0) {
                swap(&nums[i], &nums[ptr]);
                ptr++;
            }
        }
        for (int i = ptr; i < numsSize; ++i) {
            if (nums[i] == 1) {
                swap(&nums[i], &nums[ptr]);
                ptr++;
            }
        }
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 0, 2, 1, 1, 0}}, {{2, 0, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,0,2,1,1,0]
     *  Output: [0,0,1,1,2,2]
     *
     *  Input: nums = [2,0,1]
     *  Output: [0,1,2]
     */

    Solution cSolution;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        cSolution.sortColors(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

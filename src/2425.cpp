#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int xorAllNums(vector<int>& nums1, vector<int>& nums2) {
        int retVal = 0;

        int nums1Size = nums1.size();
        int nums2Size = nums2.size();

        int xor1 = 0;
        if (nums2Size % 2 != 0) {
            for (int num : nums1) {
                xor1 ^= num;
            }
        }

        int xor2 = 0;
        if (nums1Size % 2 != 0) {
            for (int num : nums2) {
                xor2 ^= num;
            }
        }

        retVal = xor1 ^ xor2;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums1;
        vector<int> nums2;
    };
    vector<subject> testData{{{2, 1, 3}, {10, 2, 5, 0}}, {{1, 2}, {3, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums1 = [2,1,3], nums2 = [10,2,5,0]
     *  Output: 13
     *
     *  Input: nums1 = [1,2], nums2 = [3,4]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums1 = [";
        for (long unsigned int j = 0; j < testData[i].nums1.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums1[j];
        }
        cout << "], nums2 = [";
        for (long unsigned int j = 0; j < testData[i].nums2.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums2[j];
        }
        cout << "]\n";

        answer = cSolution.xorAllNums(testData[i].nums1, testData[i].nums2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

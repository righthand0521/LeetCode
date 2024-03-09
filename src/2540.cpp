#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int getCommon(vector<int>& nums1, vector<int>& nums2) {
        int retVal = -1;

        int nums1Size = nums1.size();
        int nums2Size = nums2.size();

        int nums1Idx = 0;
        int nums2Idx = 0;
        while ((nums1Idx < nums1Size) && (nums2Idx < nums2Size)) {
            if (nums1[nums1Idx] == nums2[nums2Idx]) {
                retVal = nums1[nums1Idx];
                break;
            } else if (nums1[nums1Idx] > nums2[nums2Idx]) {
                nums2Idx++;
            } else if (nums1[nums1Idx] < nums2[nums2Idx]) {
                nums1Idx++;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums1;
        vector<int> nums2;
    };
    vector<subject> testData{{{1, 2, 3}, {2, 4}}, {{1, 2, 3, 6}, {2, 3, 4, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums1 = [1,2,3], nums2 = [2,4]
     *  Output: 2
     *
     *  Input: nums1 = [1,2,3,6], nums2 = [2,3,4,5]
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums1 = [";
        for (long unsigned int j = 0; j < testData[i].nums1.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums1[j];
        }
        cout << "], nums2 = [";
        for (long unsigned int j = 0; j < testData[i].nums2.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums2[j];
        }
        cout << "]\n";

        answer = cSolution.getCommon(testData[i].nums1, testData[i].nums2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

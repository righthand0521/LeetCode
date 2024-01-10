#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        double retVal = 0;

        int len1 = nums1.size();
        int len2 = nums2.size();
        int len = len1 + len2;
        vector<int> numsMerge(len);
        merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), numsMerge.begin());

        if (len % 2 == 1) {
            retVal = numsMerge[len / 2];
        } else {
            retVal = (double)(numsMerge[len / 2 - 1] + numsMerge[len / 2]) / 2;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums1;
        vector<int> nums2;
    };
    vector<subject> testData{{{1, 3}, {2}}, {{1, 2}, {3, 4}}, {{1}, {}}, {{1}, {2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums1 = [1,3], nums2 = [2]
     *  Output: 2.00000
     *
     *  Input: nums1 = [1,2], nums2 = [3,4]
     *  Output: 2.50000
     *
     *  Input: nums1 = [1], nums2 = []
     *  Output: 1.00000
     *
     *  Input: nums1 = [1], nums2 = [2]
     *  Output: 1.50000
     */

    Solution cSolution;
    double answer;
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

        answer = cSolution.findMedianSortedArrays(testData[i].nums1, testData[i].nums2);
        cout.setf(ios::fixed);
        cout.precision(5);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int nums1Size = nums1.size();
        if ((m + n) > nums1Size) {
            return;
        }

        int idx = nums1Size - 1;
        int idx1 = m - 1;
        int idx2 = n - 1;
        while ((idx1 >= 0) && (idx2 >= 0)) {
            if (nums1[idx1] > nums2[idx2]) {
                nums1[idx--] = nums1[idx1--];
            } else {
                nums1[idx--] = nums2[idx2--];
            }
        }
        while (idx1 >= 0) {
            nums1[idx--] = nums1[idx1--];
        }
        while (idx2 >= 0) {
            nums1[idx--] = nums2[idx2--];
        }
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums1;
        int m;
        vector<int> nums2;
        int n;
    };
    vector<subject> testData{{{1, 2, 3, 0, 0, 0}, 3, {2, 5, 6}, 3}, {{1}, 1, {}, 0}, {{0}, 0, {1}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
     *  Output: [1,2,2,3,5,6]
     *
     *  Input: nums1 = [1], m = 1, nums2 = [], n = 0
     *  Output: [1]
     *
     *  Input: nums1 = [0], m = 0, nums2 = [1], n = 1
     *  Output: [1]
     */

    Solution cSolution;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums1 = [";
        for (long unsigned int j = 0; j < testData[i].nums1.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums1[j];
        }
        cout << "], m = " << testData[i].m;
        cout << "nums2 = [";
        for (long unsigned int j = 0; j < testData[i].nums2.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums2[j];
        }
        cout << "], n = " << testData[i].n << "\n";

        cSolution.merge(testData[i].nums1, testData[i].m, testData[i].nums2, testData[i].n);
        cout << "Output: [";
        for (int j = 0; j < (testData[i].m + testData[i].n); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums1[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

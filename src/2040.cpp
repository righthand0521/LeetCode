#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {
        long long retVal = 0;

        int nums1Size = nums1.size();
        int nums2Size = nums2.size();

        int pos1 = 0;
        while ((pos1 < nums1Size) && (nums1[pos1] < 0)) {
            pos1++;
        }
        int pos2 = 0;
        while ((pos2 < nums2Size) && (nums2[pos2] < 0)) {
            pos2++;
        }

        long long left = -1e10;
        long long right = 1e10;
        while (left <= right) {
            long long middle = (left + right) / 2;
            long long count = 0;

            for (int i1 = 0, i2 = pos2 - 1; i1 < pos1 && i2 >= 0;) {
                if (static_cast<long long>(nums1[i1]) * nums2[i2] > middle) {
                    i1++;
                } else {
                    count += (pos1 - i1);
                    i2--;
                }
            }

            for (int i1 = pos1, i2 = nums2Size - 1; i1 < nums1Size && i2 >= pos2;) {
                if (static_cast<long long>(nums1[i1]) * nums2[i2] > middle) {
                    i2--;
                } else {
                    count += (i2 - pos2 + 1);
                    i1++;
                }
            }

            for (int i1 = 0, i2 = pos2; i1 < pos1 && i2 < nums2Size;) {
                if (static_cast<long long>(nums1[i1]) * nums2[i2] > middle) {
                    i2++;
                } else {
                    count += (nums2Size - i2);
                    i1++;
                }
            }

            for (int i1 = pos1, i2 = 0; i1 < nums1Size && i2 < pos2;) {
                if (static_cast<long long>(nums1[i1]) * nums2[i2] > middle) {
                    i1++;
                } else {
                    count += (nums1Size - i1);
                    i2++;
                }
            }

            if (count < k) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }
        retVal = left;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums1;
        vector<int> nums2;
        long long k;
    };
    vector<subject> testData{
        {{2, 5}, {3, 4}, 2}, {{-4, -2, 0, 3}, {2, 4}, 6}, {{-2, -1, 0, 1, 2}, {-3, -1, 2, 4, 5}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums1 = [2,5], nums2 = [3,4], k = 2
     *  Output: 8
     *
     *  Input: nums1 = [-4,-2,0,3], nums2 = [2,4], k = 6
     *  Output: 0
     *
     *  Input: nums1 = [-2,-1,0,1,2], nums2 = [-3,-1,2,4,5], k = 3
     *  Output: -6
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums1 = [";
        for (long unsigned int j = 0; j < testData[i].nums1.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums1[j];
        }
        cout << "], nums2 = [";
        for (long unsigned int j = 0; j < testData[i].nums2.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums2[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.kthSmallestProduct(testData[i].nums1, testData[i].nums2, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

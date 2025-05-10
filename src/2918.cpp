#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long minSum(vector<int>& nums1, vector<int>& nums2) {
        long long retVal = -1;

        long long sum1 = 0;
        int zero1 = 0;
        for (const int& num : nums1) {
            sum1 += num;
            if (num == 0) {
                sum1 += 1;
                zero1 += 1;
            }
        }

        long long sum2 = 0;
        int zero2 = 0;
        for (const int& num : nums2) {
            sum2 += num;
            if (num == 0) {
                sum2++;
                zero2++;
            }
        }

        if (((zero1 == 0) && (sum2 > sum1)) || ((zero2 == 0) && (sum1 > sum2))) {
            return retVal;
        }
        retVal = max(sum1, sum2);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums1;
        vector<int> nums2;
    };
    vector<subject> testData{{{3, 2, 0, 1, 0}, {6, 5, 0}}, {{2, 0, 2, 0}, {1, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums1 = [3,2,0,1,0], nums2 = [6,5,0]
     *  Output: 12
     *
     *  Input: nums1 = [2,0,2,0], nums2 = [1,4]
     *  Output: -1
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
        cout << "]\n";

        answer = cSolution.minSum(testData[i].nums1, testData[i].nums2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

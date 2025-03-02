#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
        vector<vector<int>> retVal;

        int nums1Size = nums1.size();
        int nums2Size = nums2.size();

        int idx1 = 0;
        int idx2 = 0;
        while ((idx1 < nums1Size) && (idx2 < nums2Size)) {
            if (nums1[idx1][0] == nums2[idx2][0]) {
                retVal.push_back({nums1[idx1][0], nums1[idx1][1] + nums2[idx2][1]});
                ++idx1;
                ++idx2;
            } else if (nums1[idx1][0] < nums2[idx2][0]) {
                retVal.push_back(nums1[idx1]);
                ++idx1;
            } else if (nums1[idx1][0] > nums2[idx2][0]) {
                retVal.push_back(nums2[idx2]);
                ++idx2;
            }
        }

        while (idx1 < nums1Size) {
            retVal.push_back(nums1[idx1]);
            ++idx1;
        }
        while (idx2 < nums2Size) {
            retVal.push_back(nums2[idx2]);
            ++idx2;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> nums1;
        vector<vector<int>> nums2;
    };
    vector<subject> testData{{{{1, 1}, {2, 3}, {4, 5}}, {{1, 4}, {3, 2}, {4, 1}}},
                             {{{2, 4}, {3, 6}, {5, 5}}, {{1, 3}, {4, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums1 = [[1,2],[2,3],[4,5]], nums2 = [[1,4],[3,2],[4,1]]
     *  Output: [[1,6],[2,3],[3,2],[4,6]]
     *
     *  Input: nums1 = [[2,4],[3,6],[5,5]], nums2 = [[1,3],[4,3]]
     *  Output: [[1,3],[2,4],[3,6],[4,3],[5,5]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums1 = [";
        for (long unsigned int j = 0; j < testData[i].nums1.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].nums1[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].nums1[j][k];
            }
            cout << "]";
        }
        cout << "], nums2 = [";
        for (long unsigned int j = 0; j < testData[i].nums2.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].nums2[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].nums2[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.mergeArrays(testData[i].nums1, testData[i].nums2);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
        vector<vector<int>> retVal(2);

        set<int> hashSet1(begin(nums1), end(nums1));
        set<int> hashSet2(begin(nums2), end(nums2));
        set_difference(hashSet1.begin(), hashSet1.end(), hashSet2.begin(), hashSet2.end(), back_inserter(retVal[0]));
        set_difference(hashSet2.begin(), hashSet2.end(), hashSet1.begin(), hashSet1.end(), back_inserter(retVal[1]));

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums1;
        vector<int> nums2;
    };
    vector<subject> testData{{{1, 2, 3}, {2, 4, 6}}, {{1, 2, 3, 3}, {1, 1, 2, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums1 = [1,2,3], nums2 = [2,4,6]
     *  Output: [[1,3],[4,6]]
     *
     *  Input: nums1 = [1,2,3,3], nums2 = [1,1,2,2]
     *  Output: [[3],[]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
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

        answer = cSolution.findDifference(testData[i].nums1, testData[i].nums2);
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

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        long long retVal = 0;

        vector<pair<int, int>> pairs;
        int nums1Size = nums1.size();
        for (int i = 0; i < nums1Size; i++) {
            pairs.push_back({nums1[i], nums2[i]});
        }
        sort(pairs.begin(), pairs.end(), [](pair<int, int>& a, pair<int, int>& b) { return a.second > b.second; });

        priority_queue<int, vector<int>, greater<int>> topKNums1;
        long long sumOfTopKNums1 = 0;
        for (int i = 0; i < k; i++) {
            sumOfTopKNums1 += (long long)pairs[i].first;
            topKNums1.push(pairs[i].first);
        }

        retVal = sumOfTopKNums1 * pairs[k - 1].second;
        for (int i = k; i < nums1Size; i++) {
            sumOfTopKNums1 += (pairs[i].first - topKNums1.top());
            topKNums1.pop();
            topKNums1.push(pairs[i].first);
            retVal = max(retVal, sumOfTopKNums1 * pairs[i].second);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums1;
        vector<int> nums2;
        int k;
    };
    vector<subject> testData{{{1, 3, 3, 2}, {2, 1, 3, 4}, 3}, {{4, 2, 3, 1, 1}, {7, 5, 10, 9, 6}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums1 = [1,3,3,2], nums2 = [2,1,3,4], k = 3
     *  Output: 12
     *
     *  Input: nums1 = [4,2,3,1,1], nums2 = [7,5,10,9,6], k = 1
     *  Output: 30
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums1 = [";
        for (long unsigned int j = 0; j < testData[i].nums1.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums1[j];
        }
        cout << "], nums2 = [";
        for (long unsigned int j = 0; j < testData[i].nums2.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums2[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maxScore(testData[i].nums1, testData[i].nums2, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

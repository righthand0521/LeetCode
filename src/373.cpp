#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<vector<int>> retVal;

        int nums1Size = nums1.size();
        int nums2Size = nums2.size();

        set<pair<int, int>> visited;

        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>>
            minHeap;
        minHeap.push({nums1[0] + nums2[0], {0, 0}});
        visited.insert({0, 0});
        while ((k > 0) && (minHeap.empty() == false)) {
            auto top = minHeap.top();
            minHeap.pop();
            int i = top.second.first;
            int j = top.second.second;
            retVal.push_back({nums1[i], nums2[j]});

            if ((i + 1 < nums1Size) && (visited.find({i + 1, j}) == visited.end())) {
                minHeap.push({nums1[i + 1] + nums2[j], {i + 1, j}});
                visited.insert({i + 1, j});
            }

            if ((j + 1 < nums2Size && visited.find({i, j + 1}) == visited.end())) {
                minHeap.push({nums1[i] + nums2[j + 1], {i, j + 1}});
                visited.insert({i, j + 1});
            }

            --k;
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
    vector<subject> testData{{{1, 7, 11}, {2, 4, 6}, 3}, {{1, 1, 2}, {1, 2, 3}, 2}, {{1, 2}, {3}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
     *  Output: [[1,2],[1,4],[1,6]]
     *
     *  Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
     *  Output: [[1,1],[1,1]]
     *
     *  Input: nums1 = [1,2], nums2 = [3], k = 3
     *  Output: [[1,3],[2,3]]
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
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.kSmallestPairs(testData[i].nums1, testData[i].nums2, testData[i].k);
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

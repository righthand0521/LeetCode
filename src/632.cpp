#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();

        // Merge all lists with their list index
        vector<pair<int, int>> merged;
        for (int i = 0; i < numsSize; ++i) {
            for (int num : nums[i]) {
                merged.push_back({num, i});
            }
        }
        sort(merged.begin(), merged.end());
        int mergedSize = merged.size();

        // Two pointers to track the smallest range
        unordered_map<int, int> freq;
        int rangeStart = 0;
        int rangeEnd = numeric_limits<int>::max();
        int count = 0;
        int left = 0;
        for (int right = 0; right < mergedSize; right++) {
            freq[merged[right].second]++;
            if (freq[merged[right].second] == 1) {
                count++;
            }

            // When all lists are represented, try to shrink the window
            while (count == numsSize) {
                int curRange = merged[right].first - merged[left].first;
                if (curRange < rangeEnd - rangeStart) {
                    rangeStart = merged[left].first;
                    rangeEnd = merged[right].first;
                }

                freq[merged[left].second]--;
                if (freq[merged[left].second] == 0) {
                    count--;
                }

                left++;
            }
        }

        retVal = {rangeStart, rangeEnd};

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> nums;
    };
    vector<subject> testData{{{{4, 10, 15, 24, 26}, {0, 9, 12, 20}, {5, 18, 22, 30}}},
                             {{{1, 2, 3}, {1, 2, 3}, {1, 2, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
     *  Output: [20,24]
     *
     *  Input: nums = [[1,2,3],[1,2,3],[1,2,3]]
     *  Output: [1,1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].nums[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].nums[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.smallestRange(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

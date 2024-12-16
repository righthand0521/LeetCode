#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        vector<int> retVal;

        retVal.assign(nums.begin(), nums.end());

        auto cmp = [](pair<int, int>& pair1, pair<int, int>& pair2) {
            if (pair1.first != pair2.first) {
                return pair1.first > pair2.first;
            }
            return pair1.second > pair2.second;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> minHeap(cmp);
        int numsSize = retVal.size();
        for (int i = 0; i < numsSize; ++i) {
            minHeap.push(make_pair(retVal[i], i));
        }

        for (int i = 0; i < k; ++i) {
            pair<int, int> element = minHeap.top();
            minHeap.pop();
            int idx = element.second;
            retVal[idx] *= multiplier;
            minHeap.push(make_pair(retVal[idx], idx));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
        int multiplier;
    };
    vector<subject> testData{{{2, 1, 3, 5, 6}, 5, 2}, {{1, 2}, 3, 4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,1,3,5,6], k = 5, multiplier = 2
     *  Output: [8,4,6,5,6]
     *
     *  Input: nums = [1,2], k = 3, multiplier = 4
     *  Output: [16,8]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << ", multiplier = " << testData[i].multiplier << "\n";

        answer = cSolution.getFinalState(testData[i].nums, testData[i].k, testData[i].multiplier);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

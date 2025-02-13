#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int minOperations(vector<int>& nums, int k) {
        int retVal = 0;

        priority_queue<long, vector<long>, greater<long>> minHeap(nums.begin(), nums.end());
        while (minHeap.top() < k) {
            long x = minHeap.top();
            minHeap.pop();
            long y = minHeap.top();
            minHeap.pop();
            minHeap.push(min(x, y) * 2 + max(x, y));

            retVal++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{2, 11, 10, 1, 3}, 10}, {{1, 1, 2, 4, 9}, 20}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,11,10,1,3], k = 10
     *  Output: 2
     *
     *  Input: nums = [1,1,2,4,9], k = 20
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n ";

        answer = cSolution.minOperations(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

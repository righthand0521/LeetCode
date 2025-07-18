#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    long long minimumDifference(vector<int>& nums) {
        long long retVal = 0;

        int n = nums.size() / 3;

        // max heap
        long long sum = 0;
        priority_queue<int> maxHeap;
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            maxHeap.push(nums[i]);
        }
        vector<long long> part1(n + 1);
        part1[0] = sum;
        for (int i = n; i < n * 2; ++i) {
            sum += nums[i];
            maxHeap.push(nums[i]);
            sum -= maxHeap.top();
            maxHeap.pop();
            part1[i - (n - 1)] = sum;
        }

        // min heap
        long long part2 = 0;
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (int i = n * 3 - 1; i >= n * 2; --i) {
            part2 += nums[i];
            minHeap.push(nums[i]);
        }
        retVal = part1[n] - part2;
        for (int i = n * 2 - 1; i >= n; --i) {
            part2 += nums[i];
            minHeap.push(nums[i]);
            part2 -= minHeap.top();
            minHeap.pop();
            retVal = min(retVal, part1[i - n] - part2);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 1, 2}}, {{7, 9, 5, 8, 1, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,1,2]
     *  Output: -1
     *
     *  Input: nums = [7,9,5,8,1,3]
     *  Output: 1
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.minimumDifference(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

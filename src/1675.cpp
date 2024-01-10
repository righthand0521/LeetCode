#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumDeviation(vector<int>& nums) {
        int retVal = numeric_limits<int>::max();

        /* https://leetcode.com/problems/minimize-deviation-in-array/solutions/955262/c-intuitions-and-flip/
         *
         * Intuition 1
         *  we can divide even numbers multiple times - till we get an odd number,
         *  but we can only double odd numbers once.
         *  After that, it will become an even number.
         * Intuition 2
         *  Even numbers never increase.
         *
         * Flip
         *  we can double all odd numbers first, so we can get forget of the second operation.
         *  Now, we only need to decrease the largest number - while it's even, which results a very simple solution.
         *
         * Solution
         *  Double odd numbers and put all numbers into a max heap.
         *  Track the smallest number.
         *  Track the minimum difference between the top of the heap and the smallest number.
         *  While the top of the heap is even, remove it, divide, and put back to the heap.
         */
        int minNum = numeric_limits<int>::max();
        priority_queue<int> priorityQueue;
        for (auto num : nums) {
            num = (num % 2 == 1) ? num * 2 : num;
            priorityQueue.push(num);
            minNum = min(minNum, num);
        }

        while (priorityQueue.top() % 2 == 0) {
            retVal = min(retVal, priorityQueue.top() - minNum);
            minNum = min(minNum, priorityQueue.top() / 2);
            priorityQueue.push(priorityQueue.top() / 2);
            priorityQueue.pop();
        }
        retVal = min(retVal, priorityQueue.top() - minNum);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3, 4}}, {{4, 1, 5, 20, 3}}, {{2, 10, 8}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,4]
     *  Output: 1
     *
     *  Input: nums = [4,1,5,20,3]
     *  Output: 3
     *
     *  Input: nums = [2,10,8]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.minimumDeviation(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

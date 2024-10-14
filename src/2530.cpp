#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    long long maxKelements(vector<int>& nums, int k) {
        long long retVal = 0;

        // Create max-heap to store the elements.
        priority_queue<int> maxHeap;
        for (auto& i : nums) {
            maxHeap.push(i);
        }

        while (k--) {
            int maxElement = maxHeap.top();
            retVal += maxElement;
            maxHeap.pop();
            maxHeap.push(ceil(maxElement / 3.0));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{10, 10, 10, 10, 10}, 5}, {{1, 10, 3, 3, 3}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [10,10,10,10,10], k = 5
     *  Output: 50
     *
     *  Input: nums = [1,10,3,3,3], k = 3
     *  Output: 17
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maxKelements(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

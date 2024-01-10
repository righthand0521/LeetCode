#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
#define HEAP (1)
#define QUICKSELECT (1)  // https://en.wikipedia.org/wiki/Quickselect
   public:
    Solution() {
#if (HEAP)
        cout << "Heap\n\n";
#elif (QUICKSELECT)
        cout << "Quickselect\n\n";
#endif
    }
#if (HEAP)
#elif (QUICKSELECT)
    int quickSelect(vector<int>& nums, int k) {
        int pivot = nums[rand() % nums.size()];

        vector<int> left;
        vector<int> middle;
        vector<int> right;
        for (int num : nums) {
            if (num > pivot) {
                left.push_back(num);
            } else if (num < pivot) {
                right.push_back(num);
            } else {
                middle.push_back(num);
            }
        }

        int leftSize = left.size();
        if (k <= leftSize) {
            return quickSelect(left, k);
        }

        int middleSize = middle.size();
        if (leftSize + middleSize < k) {
            return quickSelect(right, k - leftSize - middleSize);
        }

        return pivot;
    }
#endif
    int findKthLargest(vector<int>& nums, int k) {
        int retVal = 0;

#if (HEAP)
        priority_queue<int, vector<int>, greater<>> minHeap;
        for (int num : nums) {
            minHeap.push(num);
            int minHeapSize = minHeap.size();
            if (minHeapSize > k) {
                minHeap.pop();
            }
        }
        retVal = minHeap.top();
#elif (QUICKSELECT)
        retVal = quickSelect(nums, k);
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{3, 2, 1, 5, 6, 4}, 2}, {{3, 2, 3, 1, 2, 4, 5, 5, 6}, 4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,2,1,5,6,4], k = 2
     *  Output: 5
     *
     *  Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
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

        answer = cSolution.findKthLargest(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

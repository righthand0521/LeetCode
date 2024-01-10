#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    long long totalCost(vector<int>& costs, int k, int candidates) {
        long long retVal = 0;

        priority_queue<int, vector<int>, greater<>> leftHeap;
        priority_queue<int, vector<int>, greater<>> rightHeap;

        int left = 0;
        int right = costs.size() - 1;
        while (k--) {
            while (((int)leftHeap.size() < candidates) && (left <= right)) {
                leftHeap.push(costs[left++]);
            }
            while (((int)rightHeap.size() < candidates) && (left <= right)) {
                rightHeap.push(costs[right--]);
            }

            int leftValue = (leftHeap.size() > 0) ? leftHeap.top() : numeric_limits<int>::max();
            int rightValue = (rightHeap.size() > 0) ? rightHeap.top() : numeric_limits<int>::max();
            if (leftValue <= rightValue) {
                retVal += leftValue;
                leftHeap.pop();
            } else {
                retVal += rightValue;
                rightHeap.pop();
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> costs;
        int k;
        int candidates;
    };
    vector<subject> testData{{{17, 12, 10, 2, 7, 2, 11, 20, 8}, 3, 4}, {{1, 2, 4, 1}, 3, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: costs = [17,12,10,2,7,2,11,20,8], k = 3, candidates = 4
     *  Output: 11
     *
     *  Input: costs = [1,2,4,1], k = 3, candidates = 3
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: costs = [";
        for (long unsigned int j = 0; j < testData[i].costs.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].costs[j];
        }
        cout << "], k = " << testData[i].k << ", candidates = " << testData[i].candidates << "\n";

        answer = cSolution.totalCost(testData[i].costs, testData[i].k, testData[i].candidates);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

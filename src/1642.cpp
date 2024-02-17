#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        int retVal = 0;

        int heightsSize = heights.size();

        int brickSum = 0;
        priority_queue<int, vector<int>, greater<int>> laddersHeap;
        for (int i = 1; i < heightsSize; ++i) {
            int diff = heights[i] - heights[i - 1];
            if (diff <= 0) {
                continue;
            }

            laddersHeap.push(diff);
            int laddersHeapSize = laddersHeap.size();
            if (laddersHeapSize > ladders) {
                brickSum += laddersHeap.top();
                laddersHeap.pop();
            }

            if (brickSum > bricks) {
                retVal = i - 1;
                return retVal;
            }
        }

        retVal = heightsSize - 1;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> heights;
        int bricks;
        int ladders;
    };
    vector<subject> testData{
        {{4, 2, 7, 6, 9, 14, 12}, 5, 1}, {{4, 12, 2, 7, 3, 18, 20, 3, 19}, 10, 2}, {{14, 3, 19, 3}, 17, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
     *  Output: 4
     *
     *  Input: heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
     *  Output: 7
     *
     *  Input: heights = [14,3,19,3], bricks = 17, ladders = 0
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: heights = [";
        for (long unsigned int j = 0; j < testData[i].heights.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].heights[j];
        }
        cout << "], bricks = " << testData[i].bricks << ", ladders = " << testData[i].ladders << "\n";

        answer = cSolution.furthestBuilding(testData[i].heights, testData[i].bricks, testData[i].ladders);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

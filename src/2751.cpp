#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        vector<int> retVal;

        int positionsSize = positions.size();

        // Sort indices based on their positions
        vector<int> indices(positionsSize);
        for (int index = 0; index < positionsSize; ++index) {
            indices[index] = index;
        }
        sort(indices.begin(), indices.end(), [&](int lhs, int rhs) {
            // ascending order
            return positions[lhs] < positions[rhs];
        });

        stack<int> stack;
        for (int currentIndex : indices) {
            if (directions[currentIndex] == 'R') {
                stack.push(currentIndex);
                continue;
            }

            while (!stack.empty() && healths[currentIndex] > 0) {
                // Pop the top robot from the stack for collision check
                int topIndex = stack.top();
                stack.pop();

                if (healths[topIndex] > healths[currentIndex]) {
                    // Top robot survives, current robot is destroyed
                    healths[topIndex] -= 1;
                    healths[currentIndex] = 0;
                    stack.push(topIndex);
                } else if (healths[topIndex] < healths[currentIndex]) {
                    // Current robot survives, top robot is destroyed
                    healths[currentIndex] -= 1;
                    healths[topIndex] = 0;
                } else {
                    // Both robots are destroyed
                    healths[currentIndex] = 0;
                    healths[topIndex] = 0;
                }
            }
        }

        // Collect surviving robots
        for (int index = 0; index < positionsSize; ++index) {
            if (healths[index] > 0) {
                retVal.emplace_back(healths[index]);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> positions;
        vector<int> healths;
        string directions;
    };
    vector<subject> testData{{{5, 4, 3, 2, 1}, {2, 17, 9, 15, 10}, "RRRRR"},
                             {{3, 5, 2, 6}, {10, 10, 15, 12}, "RLRL"},
                             {{1, 2, 5, 6}, {10, 10, 11, 11}, "RLRL"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: positions = [5,4,3,2,1], healths = [2,17,9,15,10], directions = "RRRRR"
     *  Output: [2,17,9,15,10]
     *
     *  Input: positions = [3,5,2,6], healths = [10,10,15,12], directions = "RLRL"
     *  Output: [14]
     *
     *  Input: positions = [1,2,5,6], healths = [10,10,11,11], directions = "RLRL"
     *  Output: []
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: positions = [";
        for (long unsigned int j = 0; j < testData[i].positions.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].positions[j];
        }
        cout << "], healths = [";
        for (long unsigned int j = 0; j < testData[i].healths.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].healths[j];
        }
        cout << "], directions = \"" << testData[i].directions << "\"\n";

        answer = cSolution.survivedRobotsHealths(testData[i].positions, testData[i].healths, testData[i].directions);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

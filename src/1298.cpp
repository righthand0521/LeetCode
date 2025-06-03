#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys,
                   vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        int retVal = 0;

        int statusSize = status.size();
        vector<bool> canOpen(statusSize);
        for (int i = 0; i < statusSize; ++i) {
            canOpen[i] = (status[i] == 1);
        }
        vector<bool> hasBox(statusSize, false);
        vector<bool> used(statusSize, false);

        queue<int> bfsQueue;
        for (int initialBox : initialBoxes) {
            hasBox[initialBox] = true;
            if (canOpen[initialBox] == true) {
                bfsQueue.push(initialBox);
                used[initialBox] = true;
                retVal += candies[initialBox];
            }
        }

        while (bfsQueue.empty() == false) {
            int bigBox = bfsQueue.front();
            bfsQueue.pop();

            for (int key : keys[bigBox]) {
                canOpen[key] = true;
                if ((used[key] == false) && (hasBox[key] == true)) {
                    bfsQueue.push(key);
                    used[key] = true;
                    retVal += candies[key];
                }
            }

            for (int box : containedBoxes[bigBox]) {
                hasBox[box] = true;
                if ((used[box] == false) && (canOpen[box] == true)) {
                    bfsQueue.push(box);
                    used[box] = true;
                    retVal += candies[box];
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> status;
        vector<int> candies;
        vector<vector<int>> keys;
        vector<vector<int>> containedBoxes;
        vector<int> initialBoxes;
    };
    vector<subject> testData{
        {
            {1, 0, 1, 0},
            {7, 5, 4, 100},
            {{}, {}, {1}, {}},
            {{1, 2}, {3}, {}, {}},
            {0},
        },
        {
            {1, 0, 0, 0, 0, 0},
            {1, 1, 1, 1, 1, 1},
            {{1, 2, 3, 4, 5}, {}, {}, {}, {}, {}},
            {{1, 2, 3, 4, 5}, {}, {}, {}, {}, {}},
            {0},
        },
    };
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: status = [1,0,1,0], candies = [7,5,4,100], keys = [[],[],[1],[]],
     *  containedBoxes = [[1,2],[3],[],[]], initialBoxes = [0]
     *  Output: 16
     *
     *  Input: status = [1,0,0,0,0,0], candies = [1,1,1,1,1,1], keys = [[1,2,3,4,5],[],[],[],[],[]],
     *  containedBoxes = [[1,2,3,4,5],[],[],[],[],[]], initialBoxes = [0]
     *  Output: 6
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: status = [";
        for (long unsigned int j = 0; j < testData[i].status.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].status[j];
        }
        cout << "], candies = [";
        for (long unsigned int j = 0; j < testData[i].candies.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].candies[j];
        }
        cout << "], keys = [";
        for (long unsigned int j = 0; j < testData[i].keys.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].keys[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].keys[j][k];
            }
            cout << "]";
        }
        cout << "], containedBoxes = [";
        for (long unsigned int j = 0; j < testData[i].containedBoxes.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].containedBoxes[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].containedBoxes[j][k];
            }
            cout << "]";
        }
        cout << "], initialBoxes = [";
        for (long unsigned int j = 0; j < testData[i].initialBoxes.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].initialBoxes[j];
        }
        cout << "]\n";

        answer = cSolution.maxCandies(testData[i].status, testData[i].candies, testData[i].keys,
                                      testData[i].containedBoxes, testData[i].initialBoxes);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

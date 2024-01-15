#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        vector<vector<int>> retVal;

        unordered_map<int, int> lostHashTable;
        for (auto& match : matches) {
            int win = match[0];
            int lost = match[1];
            auto iterator = lostHashTable.find(win);
            if (iterator == lostHashTable.end()) {
                lostHashTable[win] = 0;
            }
            lostHashTable[lost]++;
        }

        vector<int> notLost;
        vector<int> lostExactlyOne;
        for (auto& iterator : lostHashTable) {
            if (iterator.second == 0) {
                notLost.emplace_back(iterator.first);
            } else if (iterator.second == 1) {
                lostExactlyOne.emplace_back(iterator.first);
            }
        }
        sort(notLost.begin(), notLost.end());
        sort(lostExactlyOne.begin(), lostExactlyOne.end());
        retVal.emplace_back(notLost);
        retVal.emplace_back(lostExactlyOne);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> matches;
    };
    vector<subject> testData{{{{1, 3}, {2, 3}, {3, 6}, {5, 6}, {5, 7}, {4, 5}, {4, 8}, {4, 9}, {10, 4}, {10, 9}}},
                             {{{2, 3}, {1, 3}, {5, 4}, {6, 4}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: matches = [[1,3],[2,3],[3,6],[5,6],[5,7],[4,5],[4,8],[4,9],[10,4],[10,9]]
     *  Output: [[1,2,10],[4,5,7,8]]
     *
     *  Input: matches = [[2,3],[1,3],[5,4],[6,4]]
     *  Output: [[1,2,5,6],[]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: matches = [";
        for (long unsigned int j = 0; j < testData[i].matches.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].matches[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].matches[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.findWinners(testData[i].matches);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

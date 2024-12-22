#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int search(int height, vector<pair<int, int>>& monoStack) {
        int retVal = -1;

        int left = 0;
        int right = monoStack.size() - 1;
        while (left <= right) {
            int middle = (left + right) / 2;
            if (monoStack[middle].first > height) {
                retVal = max(retVal, middle);
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        return retVal;
    }

   public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        vector<int> retVal;

        int queriesSize = queries.size();
        retVal.assign(queriesSize, -1);

        int heightsSize = heights.size();
        vector<vector<pair<int, int>>> newQueries(heightsSize);

        for (int i = 0; i < queriesSize; i++) {
            int a = queries[i][0];
            int b = queries[i][1];
            if (a > b) {
                swap(a, b);
            }

            if ((heights[b] > heights[a]) || (a == b)) {
                retVal[i] = b;
            } else {
                newQueries[b].push_back({heights[a], i});
            }
        }

        vector<pair<int, int>> monoStack;
        for (int i = heightsSize - 1; i >= 0; i--) {
            int monoStackSize = monoStack.size();
            for (auto& [a, b] : newQueries[i]) {
                int position = search(a, monoStack);
                if ((position < monoStackSize) && (position >= 0)) {
                    retVal[b] = monoStack[position].second;
                }
            }

            while ((monoStack.empty() == false) && (monoStack.back().first <= heights[i])) {
                monoStack.pop_back();
            }
            monoStack.push_back({heights[i], i});
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> heights;
        vector<vector<int>> queries;
    };
    vector<subject> testData{{{6, 4, 8, 5, 2, 7}, {{0, 1}, {0, 3}, {2, 4}, {3, 4}, {2, 2}}},
                             {{5, 3, 8, 2, 6, 1, 4, 6}, {{0, 7}, {3, 5}, {5, 2}, {3, 0}, {1, 6}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: heights = [6,4,8,5,2,7], queries = [[0,1],[0,3],[2,4],[3,4],[2,2]]
     *  Output: [2,5,-1,5,2]
     *
     *  Input: heights = [5,3,8,2,6,1,4,6], queries = [[0,7],[3,5],[5,2],[3,0],[1,6]]
     *  Output: [7,6,-1,4,6]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: heights = [";
        for (long unsigned int j = 0; j < testData[i].heights.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].heights[j];
        }
        cout << "], queries = [";
        for (long unsigned int j = 0; j < testData[i].queries.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].queries[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].queries[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.leftmostBuildingQueries(testData[i].heights, testData[i].queries);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

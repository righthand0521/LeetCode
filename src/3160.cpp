#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> queryResults(int limit, vector<vector<int>>& queries) {
        vector<int> retVal;

        int queriesSize = queries.size();
        retVal.resize(queriesSize);

        unordered_map<int, int> colorMap;
        unordered_map<int, int> ballMap;
        for (int i = 0; i < queriesSize; i++) {
            int ball = queries[i][0];
            int color = queries[i][1];
            if (ballMap.find(ball) != ballMap.end()) {
                // Decrement count of the previous color on the ball
                int prevColor = ballMap[ball];
                colorMap[prevColor]--;

                // If there are no balls with previous color left, remove color from color map
                if (colorMap[prevColor] == 0) {
                    colorMap.erase(prevColor);
                }
            }
            ballMap[ball] = color;  // Set color of ball to the new color
            colorMap[color]++;      // Increment the count of the new color
            retVal[i] = colorMap.size();
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int limit;
        vector<vector<int>> queries;
    };
    vector<subject> testData{{4, {{1, 4}, {2, 5}, {1, 3}, {3, 4}}}, {4, {{0, 1}, {1, 2}, {2, 2}, {3, 4}, {4, 5}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: limit = 4, queries = [[1,4],[2,5],[1,3],[3,4]]
     *  Output: [1,2,2,3]
     *
     *  Input: limit = 4, queries = [[0,1],[1,2],[2,2],[3,4],[4,5]]
     *  Output: [1,2,2,3,4]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: limit = " << testData[i].limit << ", queries = [";
        for (long unsigned int j = 0; j < testData[i].queries.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].queries[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].queries[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.queryResults(testData[i].limit, testData[i].queries);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class State {
   public:
    int x;
    int y;
    int distance;
    State(int x, int y, int distance) : x(x), y(y), distance(distance) {}
#if 0
#else
    bool operator<(const State& rth) const {
        // Compare the distances
        return distance > rth.distance;
    }
#endif
};

class Solution {
   private:
    int inf = 0x3f3f3f3f;
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

   public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int retVal = 0;

        int rowSize = moveTime.size();
        int colSize = moveTime[0].size();

        vector<vector<int>> dijkstra(rowSize, vector<int>(colSize, inf));
        dijkstra[0][0] = 0;

        vector<vector<int>> visit(rowSize, vector<int>(colSize, 0));

#if 0
        auto cmp = [](const State& a, const State& b) {
            // Compare the distances
            return a.distance > b.distance;
        };
        priority_queue<State, vector<State>, decltype(cmp)> queue(cmp);
#else
        priority_queue<State> queue;
#endif
        queue.push(State(0, 0, 0));

        while (queue.empty() == false) {
            State node = queue.top();
            queue.pop();

            if (visit[node.x][node.y]) {
                continue;
            }

            if ((node.x == rowSize - 1) && (node.y == colSize - 1)) {
                break;
            }

            visit[node.x][node.y] = 1;

            for (int i = 0; i < 4; i++) {
                int nextX = node.x + directions[i][0];
                if ((nextX < 0) || (nextX >= rowSize)) {
                    continue;
                }

                int nextY = node.y + directions[i][1];
                if ((nextY < 0) || (nextY >= colSize)) {
                    continue;
                }

                int distances = max(dijkstra[node.x][node.y], moveTime[nextX][nextY]) + (node.x + node.y) % 2 + 1;
                if (dijkstra[nextX][nextY] > distances) {
                    dijkstra[nextX][nextY] = distances;
                    queue.push(State(nextX, nextY, distances));
                }
            }
        }
        retVal = dijkstra[rowSize - 1][colSize - 1];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> moveTime;
    };
    vector<subject> testData{{{{0, 4}, {4, 4}}}, {{{0, 0, 0, 0}, {0, 0, 0, 0}}}, {{{0, 1}, {1, 2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: moveTime = [[0,4],[4,4]]
     *  Output: 7
     *
     *  Input: moveTime = [[0,0,0,0],[0,0,0,0]]
     *  Output: 6
     *
     *  Input: moveTime = [[0,1],[1,2]]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: moveTime = [";
        for (long unsigned int j = 0; j < testData[i].moveTime.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].moveTime[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].moveTime[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.minTimeToReach(testData[i].moveTime);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

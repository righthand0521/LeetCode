#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// https://leetcode.com/problems/snakes-and-ladders/solutions/794701/c-bfs-detailed-explanation-faster-than-99-31/
class Solution {
   public:
    void getCoordinate(int n, int s, int& row, int& col) {
        row = n - 1 - (s - 1) / n;
        col = (s - 1) % n;

        if (((n % 2 == 1) && (row % 2 == 1)) || ((n % 2 == 0) && (row % 2 == 0))) {
            col = n - 1 - col;
        }
    }
    int snakesAndLadders(vector<vector<int>>& board) {
        int retVal = -1;

        int n = board.size();
        vector<bool> seen(n * n + 1, false);
        seen[1] = true;

        queue<pair<int, int>> q;
        q.push({1, 0});
        while (q.empty() == false) {
            pair<int, int> p = q.front();
            q.pop();

            int s = p.first;
            int dist = p.second;
            if (s == n * n) {
                retVal = dist;
                return retVal;
            }

            int row, col;
            for (int i = 1; s + i <= n * n && i <= 6; i++) {
                getCoordinate(n, s + i, row, col);

                int sfinal = ((board[row][col] == -1) ? (s + i) : (board[row][col]));
                if (seen[sfinal] == false) {
                    seen[sfinal] = true;
                    q.push({sfinal, dist + 1});
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> board;
    };
    vector<subject> testData{{{{-1, -1, -1, -1, -1, -1},
                               {-1, -1, -1, -1, -1, -1},
                               {-1, -1, -1, -1, -1, -1},
                               {-1, 35, -1, -1, 13, -1},
                               {-1, -1, -1, -1, -1, -1},
                               {-1, 15, -1, -1, -1, -1}}},
                             {{{-1, -1}, {-1, 3}}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: board = [";
        for (long unsigned int j = 0; j < testData[i].board.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].board[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].board[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.snakesAndLadders(testData[i].board);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

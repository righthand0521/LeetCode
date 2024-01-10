#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int answer = 0;

   public:
    void backtracking(int n, vector<vector<int>>& requests, int index, vector<int>& building, int count, int zero) {
        int requestsSize = requests.size();
        if (index == requestsSize) {
            if (zero == n) {
                answer = max(answer, count);
            }
            return;
        }

        backtracking(n, requests, index + 1, building, count, zero);

        int z = zero;
        ++count;
        int x = requests[index][0];
        int y = requests[index][1];
        zero -= (building[x] == 0);
        building[x] -= 1;
        zero += (building[x] == 0);
        zero -= (building[y] == 0);
        building[y] += 1;
        zero += building[y] == 0;
        backtracking(n, requests, index + 1, building, count, zero);
        building[y] -= 1;
        building[x] += 1;
        --count;
        zero = z;
    }
    int maximumRequests(int n, vector<vector<int>>& requests) {
        int retVal = 0;

        answer = 0;
        vector<int> building(n, 0);
        int count = 0;
        int zero = n;
        backtracking(n, requests, 0, building, count, zero);
        retVal = answer;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> requests;
    };
    vector<subject> testData{{5, {{0, 1}, {1, 0}, {0, 1}, {1, 2}, {2, 0}, {3, 4}}},
                             {3, {{0, 0}, {1, 2}, {2, 1}}},
                             {4, {{0, 3}, {3, 1}, {1, 2}, {2, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 5, requests = [[0,1],[1,0],[0,1],[1,2],[2,0],[3,4]]
     *  Output: 5
     *
     *  Input: n = 3, requests = [[0,0],[1,2],[2,1]]
     *  Output: 3
     *
     *  Input: n = 4, requests = [[0,3],[3,1],[1,2],[2,0]]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", requests = [";
        for (long unsigned int j = 0; j < testData[i].requests.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].requests[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].requests[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.maximumRequests(testData[i].n, testData[i].requests);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

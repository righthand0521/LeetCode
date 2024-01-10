#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        int retVal = 0;

        int locationsSize = locations.size();
        vector<vector<int>> dp(locationsSize, vector<int>(fuel + 1));
        for (int i = 0; i <= fuel; i++) {
            dp[finish][i] = 1;
        }

        for (int i = 0; i <= fuel; ++i) {
            for (int src = 0; src < locationsSize; ++src) {
                for (int dst = 0; dst < locationsSize; ++dst) {
                    if (dst == src) {
                        continue;
                    }
                    if (abs(locations[src] - locations[dst]) <= i) {
                        dp[src][i] = (dp[src][i] + dp[dst][i - abs(locations[src] - locations[dst])]) % MODULO;
                    }
                }
            }
        }

        retVal = dp[start][fuel];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> locations;
        int start;
        int finish;
        int fuel;
    };
    vector<subject> testData{{{2, 3, 6, 8, 4}, 1, 3, 5}, {{4, 3, 1}, 1, 0, 6}, {{5, 2, 1}, 0, 2, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: locations = [2,3,6,8,4], start = 1, finish = 3, fuel = 5
     *  Output: 4
     *
     *  Input: locations = [4,3,1], start = 1, finish = 0, fuel = 6
     *  Output: 5
     *
     *  Input: locations = [5,2,1], start = 0, finish = 2, fuel = 3
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: locations = [";
        for (long unsigned int j = 0; j < testData[i].locations.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].locations[j];
        }
        cout << "], start = " << testData[i].start;
        cout << ", finish = " << testData[i].finish;
        cout << ", fuel = " << testData[i].fuel << "\n";

        answer = cSolution.countRoutes(testData[i].locations, testData[i].start, testData[i].finish, testData[i].fuel);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

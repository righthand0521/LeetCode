#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define BINARY_SEARCH (1)
#define DYNAMIC_PROGRAMMING (1)  // Time Limit Exceeded
class Solution {
   public:
    Solution() {
#if (BINARY_SEARCH)
        cout << "BINARY_SEARCH\n";
#elif (DYNAMIC_PROGRAMMING)
        cout << "DYNAMIC_PROGRAMMING: Time Limit Exceeded\n";
#endif
        cout << "\n";
    }
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        vector<int> retVal;

#if (BINARY_SEARCH)
        vector<int> greedy;
        for (int obstacle : obstacles) {
            if ((greedy.empty() == true) || (obstacle >= greedy.back())) {
                greedy.push_back(obstacle);
                retVal.push_back(greedy.size());
            } else {
                int position = upper_bound(greedy.begin(), greedy.end(), obstacle) - greedy.begin();
                retVal.push_back(position + 1);
                greedy[position] = obstacle;
            }
        }
#elif (DYNAMIC_PROGRAMMING)
        int obstaclesSize = obstacles.size();
        vector<int> dp(obstaclesSize, 1);
        for (int i = 0; i < obstaclesSize; ++i) {
            for (int j = 0; j < i; ++j) {
                if (obstacles[j] <= obstacles[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        retVal.assign(dp.begin(), dp.end());
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> obstacles;
    };
    vector<subject> testData{{{1, 2, 3, 2}}, {{2, 2, 1}}, {{3, 1, 5, 6, 4, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: obstacles = [1,2,3,2]
     *  Output: [1,2,3,3]
     *
     *  Input: obstacles = [2,2,1]
     *  Output: [1,2,1]
     *
     *  Input: obstacles = [3,1,5,6,4,2]
     *  Output: [1,1,2,3,2,2]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: obstacles = [";
        for (long unsigned int j = 0; j < testData[i].obstacles.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].obstacles[j];
        }
        cout << "]\n";

        answer = cSolution.longestObstacleCourseAtEachPosition(testData[i].obstacles);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

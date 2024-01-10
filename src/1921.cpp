#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
        int retVal = 0;

        int distSize = dist.size();  // n == dist.length == speed.length

        vector<double> arrival;
        for (int i = 0; i < distSize; ++i) {
            arrival.emplace_back((double)dist[i] / speed[i]);
        }

        sort(arrival.begin(), arrival.end());

        for (int i = 0; i < distSize; ++i) {
            if (arrival[i] <= i) {
                break;
            }
            retVal += 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> dist;
        vector<int> speed;
    };
    vector<subject> testData{
        {{1, 3, 4}, {1, 1, 1}}, {{1, 1, 2, 3}, {1, 1, 1, 1}}, {{3, 2, 4}, {5, 3, 2}}, {{4, 2, 3}, {2, 1, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: dist = [1,3,4], speed = [1,1,1]
     *  Output: 3
     *
     *  Input: dist = [1,1,2,3], speed = [1,1,1,1]
     *  Output: 1
     *
     *  Input: dist = [3,2,4], speed = [5,3,2]
     *  Output: 1
     *
     *  Input: dist = [4,2,3], speed = [2,1,1]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: dist = [";
        for (long unsigned int j = 0; j < testData[i].dist.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].dist[j];
        }
        cout << "], speed = [";
        for (long unsigned int j = 0; j < testData[i].speed.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].speed[j];
        }
        cout << "]\n";

        answer = cSolution.eliminateMaximum(testData[i].dist, testData[i].speed);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

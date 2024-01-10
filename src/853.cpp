#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
   public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int retVal = 0;

        // https://leetcode.com/problems/car-fleet/solutions/139850/c-java-python-straight-forward/
        map<int, double> time;
        int positionSize = position.size();
        for (int i = 0; i < positionSize; ++i) {
            double value = target - position[i];
            time[-position[i]] = value / speed[i];
        }

        double current = 0;
        for (auto iterator : time) {
            if (iterator.second > current) {
                current = iterator.second;
                ++retVal;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int target;
        vector<int> position;
        vector<int> speed;
    };
    vector<subject> testData{{12, {10, 8, 0, 5, 3}, {2, 4, 1, 1, 3}}, {10, {3}, {3}}, {100, {0, 2, 4}, {4, 2, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
     *  Output: 3
     *
     *  Input: target = 10, position = [3], speed = [3]
     *  Output: 1
     *
     *  Input: target = 100, position = [0,2,4], speed = [4,2,1]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: target = " << testData[i].target << ", position = [";
        for (long unsigned int j = 0; j < testData[i].position.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].position[j];
        }
        cout << "], speed = [";
        for (long unsigned int j = 0; j < testData[i].speed.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].speed[j];
        }
        cout << "]\n";

        answer = cSolution.carFleet(testData[i].target, testData[i].position, testData[i].speed);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> retVal;

        for (auto asteroid : asteroids) {
            int currentAsteroidSize = abs(asteroid);
            while ((retVal.empty() == false) && (retVal.back() > 0) && (asteroid < 0)) {
                int previousAsteroidSize = abs(retVal.back());
                if (previousAsteroidSize > currentAsteroidSize) {
                    currentAsteroidSize = -1;
                    break;
                } else if (previousAsteroidSize == currentAsteroidSize) {
                    currentAsteroidSize = -1;
                    retVal.pop_back();
                    break;
                } else if (previousAsteroidSize < currentAsteroidSize) {
                    retVal.pop_back();
                }
            }
            if (currentAsteroidSize != -1) {
                retVal.emplace_back(asteroid);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> asteroids;
    };
    vector<subject> testData{{{5, 10, -5}}, {{8, -8}}, {{10, 2, -5}}, {{-2, -1, 1, 2}}, {{1, -2, -2, -2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: asteroids = [5,10,-5]
     *  Output: [5,10]
     *
     *  Input: asteroids = [8,-8]
     *  Output: []
     *
     *  Input: asteroids = [10,2,-5]
     *  Output: [10]
     *
     *  Input: asteroids = [-2,-1,1,2]
     *  Output: [-2,-1,1,2]
     *
     *  Input: asteroids = [1,-2,-2,-2]
     *  Output: [-2,-2,-2]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: asteroids = [";
        for (long unsigned int j = 0; j < testData[i].asteroids.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].asteroids[j];
        }
        cout << "]\n";

        answer = cSolution.asteroidCollision(testData[i].asteroids);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

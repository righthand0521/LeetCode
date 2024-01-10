#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        bool retVal = true;

        sort(asteroids.begin(), asteroids.end());
        long long sum = mass;  // 1 <= asteroids.length <= 10^5, 1 <= asteroids[i] <= 10^5.
        for (auto asteroid : asteroids) {
            if (sum < asteroid) {
                retVal = false;
                break;
            }
            sum += asteroid;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int mass;
        vector<int> asteroids;
    };
    vector<subject> testData{{10, {3, 9, 19, 5, 21}}, {5, {4, 9, 23, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: mass = 10, asteroids = [3,9,19,5,21]
     *  Output: true
     *
     *  Input: mass = 5, asteroids = [4,9,23,4]
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: mass = " << testData[i].mass << ", asteroids = [";
        for (long unsigned int j = 0; j < testData[i].asteroids.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].asteroids[j];
        }
        cout << "]\n";

        answer = cSolution.asteroidsDestroyed(testData[i].mass, testData[i].asteroids);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

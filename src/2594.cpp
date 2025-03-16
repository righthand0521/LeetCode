#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long repairCars(vector<int>& ranks, int cars) {
        long long retVal = 0;

        // The minimum possible time is 1
        // The maximum possible time is when the slowest mechanic (highest rank) repairs all cars
        long long left = 1;
        long long right = 1LL * cars * cars * ranks[0];
        while (left < right) {
            long long middle = left + (right - left) / 2;

            // Calculate the number of cars that can be repaired in 'middle' time by all mechanics.
            long long carsRepaired = 0;
            for (auto rank : ranks) {
                carsRepaired += sqrt(1.0 * middle / rank);
            }

            // If the total cars repaired is less than required, increase the time. Otherwise, try a smaller time.
            if (carsRepaired < cars) {
                left = middle + 1;

            } else {
                right = middle;
            }
        }
        retVal = left;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> ranks;
        int cars;
    };
    vector<subject> testData{{{4, 2, 3, 1}, 10}, {{5, 1, 8}, 6}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: ranks = [4,2,3,1], cars = 10
     *  Output: 16
     *
     *  Input: ranks = [5,1,8], cars = 6
     *  Output: 16
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: ranks = [";
        for (long unsigned int j = 0; j < testData[i].ranks.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].ranks[j];
        }
        cout << "], cars = " << testData[i].cars << "\n";

        answer = cSolution.repairCars(testData[i].ranks, testData[i].cars);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

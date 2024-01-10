#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long minimumTime(vector<int>& time, int totalTrips) {
        long long retVal = 0;

        long long left = 1;
        long long right = (long long)totalTrips * (*min_element(time.begin(), time.end()));
        while (left < right) {
            long long middle = left + (right - left) / 2;

            long long tmpTrip = 0;
            for (auto iter : time) {
                tmpTrip += (middle / iter);
            }

            if (tmpTrip < totalTrips) {
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
        vector<int> time;
        int totalTrips;
    };
    vector<subject> testData{{{1, 2, 3}, 5}, {{2}, 1}, {{5, 10, 10}, 9}, {{1}, 4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: time = [1,2,3], totalTrips = 5
     *  Output: 3
     *
     *  Input: time = [2], totalTrips = 1
     *  Output: 2
     *
     *  Input: time = [5,10,10], totalTrips = 9
     *  Output: 25
     *
     *  Input: time = [1], totalTrips = 4
     *  Output: 4
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: time = [";
        for (long unsigned int j = 0; j < testData[i].time.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].time[j];
        }
        cout << "], totalTrips = " << testData[i].totalTrips << "\n";

        answer = cSolution.minimumTime(testData[i].time, testData[i].totalTrips);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

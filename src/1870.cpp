#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minSpeedOnTime(vector<int>& dist, double hour) {
        int retVal = -1;

        int distSize = dist.size();
        if ((double)(distSize - 1) >= hour) {
            return retVal;
        }

        // Tests are generated such that the answer will not exceed 10^7
        // and hour will have at most two digits after the decimal point.
        int left = 1;
        int right = 1e7;
        while (left < right) {
            int middle = left + (right - left) / 2;

            /* Example: dist = [1,3,2], hour = 2.7
             *  Speed   Time Required
             *    1     (1/1) + (3/1) + (2/1) = 6
             *    2     (1/2) + (3/2) + (2/2) = 1 + 2 + 1 = 4
             *    3     (1/3) + (3/3) + (2/3) = 1 + 1 + 0.67 = 2.67
             *
             *   10^7
             */
            double totalHour = 0;
            int i;
            for (i = 0; i < distSize - 1; ++i) {
                totalHour += ((dist[i] + middle - 1) / middle);
            }
            totalHour += (((double)dist[i]) / middle);

            if (totalHour > hour) {
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
        vector<int> dist;
        double hour;
    };
    vector<subject> testData{{{1, 3, 2}, 6}, {{1, 3, 2}, 2.7}, {{1, 3, 2}, 1.9}, {{1, 1, 100000}, 2.01}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: dist = [1,3,2], hour = 6
     *  Output: 1
     *
     *  Input: dist = [1,3,2], hour = 2.7
     *  Output: 3
     *
     *  Input: dist = [1,3,2], hour = 1.9
     *  Output: -1
     *
     *  Input: dist = [1,1,100000], hour = 2.01
     *  Output: 10000000
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: dist = [";
        for (long unsigned int j = 0; j < testData[i].dist.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].dist[j];
        }
        cout << "], hour = " << testData[i].hour << "\n";

        answer = cSolution.minSpeedOnTime(testData[i].dist, testData[i].hour);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

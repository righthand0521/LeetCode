#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        int retVal = -1;

        int bloomDaySize = bloomDay.size();
        long flowers = (long)m * (long)k;
        if (flowers > bloomDaySize) {
            return retVal;
        }

        int left = 0;
        int right = *max_element(bloomDay.begin(), bloomDay.end());
        while (left <= right) {
            int middle = (left + right) / 2;

            int bouquets = 0;
            int count = 0;
            for (int day : bloomDay) {
                if (day <= middle) {
                    count += 1;
                } else {
                    count = 0;
                }

                if (count == k) {
                    bouquets += 1;
                    count = 0;
                }
            }

            if (bouquets >= m) {
                retVal = middle;
                right = middle - 1;
            } else {
                left = middle + 1;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> bloomDay;
        int m;
        int k;
    };
    vector<subject> testData{{{1, 10, 3, 10, 2}, 3, 1}, {{1, 10, 3, 10, 2}, 3, 2}, {{7, 7, 7, 7, 12, 7, 7}, 2, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: bloomDay = [1,10,3,10,2], m = 3, k = 1
     *  Output: 3
     *
     *  Input: bloomDay = [1,10,3,10,2], m = 3, k = 2
     *  Output: -1
     *
     *  Input: bloomDay = [7,7,7,7,12,7,7], m = 2, k = 3
     *  Output: 12
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: bloomDay = [";
        for (long unsigned int j = 0; j < testData[i].bloomDay.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].bloomDay[j];
        }
        cout << "], m = " << testData[i].m << ", k = " << testData[i].k << "\n";

        answer = cSolution.minDays(testData[i].bloomDay, testData[i].m, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

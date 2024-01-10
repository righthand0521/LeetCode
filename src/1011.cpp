#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   public:
    int shipWithinDays(vector<int>& weights, int days) {
        int retVal = 0;

        int left = *max_element(weights.begin(), weights.end());
        int right = accumulate(weights.begin(), weights.end(), 0);
        while (left < right) {
            int middle = left + (right - left) / 2;

            int useDays = 1;
            int capacity = 0;
            for (auto weight : weights) {
                capacity += weight;
                if (capacity > middle) {
                    capacity = weight;
                    useDays += 1;
                }
            }
            if (useDays > days) {
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
        vector<int> weights;
        int days;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5}, {{3, 2, 2, 4, 1, 4}, 3}, {{1, 2, 3, 1, 1}, 4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
     *  Output: 15
     *
     *  Input: weights = [3,2,2,4,1,4], days = 3
     *  Output: 6
     *
     *  Input: weights = [1,2,3,1,1], days = 4
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: weights = [";
        for (long unsigned int j = 0; j < testData[i].weights.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].weights[j];
        }
        cout << "], days = " << testData[i].days << "\n";

        answer = cSolution.shipWithinDays(testData[i].weights, testData[i].days);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

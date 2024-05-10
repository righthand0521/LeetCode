#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        vector<int> retVal;

        int arrSize = arr.size();

        double left = 0;
        double right = 1.0;
        while (left < right) {
            double middle = (left + right) / 2;

            double maxFraction = 0.0;
            int totalSmallerFractions = 0;
            int numeratorIdx = 0;
            int denominatorIdx = 0;
            int j = 1;
            for (int i = 0; i < (arrSize - 1); ++i) {
                while ((j < arrSize) && (arr[i] >= middle * arr[j])) {
                    j += 1;
                }

                totalSmallerFractions += (arrSize - j);

                if (j == arrSize) {
                    break;
                }

                double fraction = static_cast<double>(arr[i]) / arr[j];
                if (fraction > maxFraction) {
                    numeratorIdx = i;
                    denominatorIdx = j;
                    maxFraction = fraction;
                }
            }

            if (totalSmallerFractions == k) {
                retVal.emplace_back(arr[numeratorIdx]);
                retVal.emplace_back(arr[denominatorIdx]);
                break;
            } else if (totalSmallerFractions > k) {
                right = middle;
            } else {
                left = middle;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
        int k;
    };
    vector<subject> testData{{{1, 2, 3, 5}, 3}, {{1, 7}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [1,2,3,5], k = 3
     *  Output: [2,5]
     *
     *  Input: arr = [1,7], k = 1
     *  Output: [1,7]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.kthSmallestPrimeFraction(testData[i].arr, testData[i].k);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

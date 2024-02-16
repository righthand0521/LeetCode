#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        int retVal = 0;

        unordered_map<int, int> occurrences;
        for (auto iterator : arr) {
            occurrences[iterator]++;
        }

        vector<pair<int, int>> occurrencesSort(occurrences.begin(), occurrences.end());
        sort(occurrencesSort.begin(), occurrencesSort.end(), [&](auto x1, auto x2) {
            // ascending order
            return x1.second < x2.second;
        });

        for (auto iterator : occurrencesSort) {
            k -= iterator.second;
            if (k < 0) {
                retVal++;
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
    vector<subject> testData{{{5, 5, 4}, 1}, {{4, 3, 1, 1, 3, 3, 2}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [5,5,4], k = 1
     *  Output: 1
     *
     *  Input: arr = [4,3,1,1,3,3,2], k = 3
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.findLeastNumOfUniqueInts(testData[i].arr, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

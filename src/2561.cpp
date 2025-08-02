#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
   public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        long long retVal = 0;

        unordered_map<int, int> frequency;
        int minValue = numeric_limits<int>::max();
        for (int b1 : basket1) {
            frequency[b1]++;
            minValue = min(minValue, b1);
        }
        for (int b2 : basket2) {
            frequency[b2]--;
            minValue = min(minValue, b2);
        }

        vector<int> merge;
        for (auto [key, value] : frequency) {
            if (value % 2 != 0) {
                retVal = -1;
                return retVal;
            }
            for (int i = 0; i < abs(value) / 2; ++i) {
                merge.emplace_back(key);
            }
        }

        if (merge.empty()) {
            return retVal;
        }
        sort(merge.begin(), merge.end());

        int mergeSize = merge.size();
        for (int i = 0; i < mergeSize / 2; i++) {
            retVal += min(merge[i], minValue * 2);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> basket1;
        vector<int> basket2;
    };
    vector<subject> testData{{{4, 2, 2, 2}, {1, 4, 1, 2}}, {{2, 3, 4, 1}, {3, 2, 5, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: basket1 = [4,2,2,2], basket2 = [1,4,1,2]
     *  Output: 1
     *
     *  Input: basket1 = [2,3,4,1], basket2 = [3,2,5,1]
     *  Output: -1
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: basket1 = [";
        for (long unsigned int j = 0; j < testData[i].basket1.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].basket1[j];
        }
        cout << "], basket2 = [";
        for (long unsigned int j = 0; j < testData[i].basket2.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].basket2[j];
        }
        cout << "]\n";

        answer = cSolution.minCost(testData[i].basket1, testData[i].basket2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

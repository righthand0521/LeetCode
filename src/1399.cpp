#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int countLargestGroup(int n) {
        int retVal = 0;

        int maxValue = 0;
        unordered_map<int, int> hashTable;
        for (int i = 1; i <= n; ++i) {
            int key = 0;
            int num = i;
            while (num) {
                key += num % 10;
                num /= 10;
            }
            ++hashTable[key];

            maxValue = max(maxValue, hashTable[key]);
        }

        for (auto& [_, value] : hashTable) {
            if (value == maxValue) {
                ++retVal;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{13}, {2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 13
     *  Output: 4
     *
     *  Input: n = 2
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.countLargestGroup(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

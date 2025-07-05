#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int findLucky(vector<int>& arr) {
        int retVal = -1;

        unordered_map<int, int> hashTable;
        for (int value : arr) {
            hashTable[value]++;
        }
        for (const auto& [key, count] : hashTable) {
            if (key == count) {
                retVal = max(retVal, key);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{2, 2, 3, 4}}, {{1, 2, 2, 3, 3, 3}}, {{2, 2, 2, 3, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [2,2,3,4]
     *  Output: 2
     *
     *  Input: arr = [1,2,2,3,3,3]
     *  Output: 3
     *
     *  Input: arr = [2,2,2,3,3]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.findLucky(testData[i].arr);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

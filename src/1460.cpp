#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canBeEqual(vector<int>& target, vector<int>& arr) {
        bool retVal = true;

        unordered_map<int, int> hashTable;
        for (int value : target) {
            hashTable[value] += 1;
        }
        for (int value : arr) {
            hashTable[value] -= 1;
        }

        for (auto& value : hashTable) {
            if (value.second != 0) {
                retVal = false;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> target;
        vector<int> arr;
    };
    vector<subject> testData{{{1, 2, 3, 4}, {2, 4, 1, 3}}, {{7}, {7}}, {{3, 7, 9}, {3, 7, 11}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: target = [1,2,3,4], arr = [2,4,1,3]
     *  Output: true
     *
     *  Input: target = [7], arr = [7]
     *  Output: true
     *
     *  Input: target = [3,7,9], arr = [3,7,11]
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: target = [";
        for (long unsigned int j = 0; j < testData[i].target.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].target[j];
        }
        cout << "], arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.canBeEqual(testData[i].target, testData[i].arr);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

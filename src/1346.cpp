#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool checkIfExist(vector<int>& arr) {
        bool retVal = false;

        unordered_map<int, int> hashTable;
        for (int value : arr) {
            hashTable[value]++;
        }

        for (int value : arr) {
            if ((value == 0) && (hashTable[value] > 1)) {
                retVal = true;
                break;
            } else if ((value != 0) && (hashTable.count(2 * value) != 0)) {
                retVal = true;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{
        {{10, 2, 5, 3}}, {{3, 1, 7, 11}}, {{-2, 0, 10, -19, 4, 6, -8}}, {{0, 0}}, {{-10, 12, -20, -8, 15}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [10,2,5,3]
     *  Output: true
     *
     *  Input: arr = [3,1,7,11]
     *  Output: false
     *
     *  Input: arr = [-2, 0, 10, -19, 4, 6, -8]
     *  Output: false
     *
     *  Input: arr = [0, 0]
     *  Output: true
     *
     *  Input: arr = [-10, 12, -20, -8, 15]
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.checkIfExist(testData[i].arr);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

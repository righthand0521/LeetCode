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
        for (auto i : arr) {
            if (hashTable.count(i * 2) != 0) {
                retVal = true;
                break;
            }

            if ((i % 2 == 0) && (hashTable.count(i / 2) != 0)) {
                retVal = true;
                break;
            }

            ++hashTable[i];
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{10, 2, 5, 3}},
                             {{3, 1, 7, 11}},
                             {{-2, 0, 10, -19, 4, 6, -8}},
                             {{0, 0}},
                             {{-10, 12, -20, -8, 15}},
                             {{7, 1, 14, 11}},
                             {{-778, -481, 842,  495, 44,  1000, -572, 977, 240, -116, 673,  997, -958, -539, -964,
                               -187, -701, -928, 472, 965, -672, -88,  443, 36,  388,  -127, 115, 704,  -549, 1000,
                               998,  291,  633,  423, 57,  -77,  -543, 72,  328, -938, -192, 382, 179}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [10,2,5,3]
     *  Output: true
     *
     *  Input: arr = [3,1,7,11]
     *  Output: false
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

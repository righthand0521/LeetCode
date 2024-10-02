#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> retVal;

        int arrSize = arr.size();
        if (arrSize == 0) {
            return retVal;
        }

        vector<int> sortedArr(arr);
        sort(sortedArr.begin(), sortedArr.end());

        int rank = 1;
        unordered_map<int, int> hashTable;
        hashTable[sortedArr[0]] = rank;
        for (int i = 1; i < arrSize; ++i) {
            if (sortedArr[i] > sortedArr[i - 1]) {
                rank++;
            }
            hashTable[sortedArr[i]] = rank;
        }

        for (int value : arr) {
            retVal.emplace_back(hashTable[value]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{40, 10, 20, 30}}, {{100, 100, 100}}, {{37, 12, 28, 9, 100, 56, 80, 5, 12}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [40,10,20,30]
     *  Output: [4,1,2,3]
     *
     *  Input: arr = [100,100,100]
     *  Output: [1,1,1]
     *
     *  Input: arr = [37,12,28,9,100,56,80,5,12]
     *  Output: [5,3,4,2,8,6,7,1,3]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.arrayRankTransform(testData[i].arr);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

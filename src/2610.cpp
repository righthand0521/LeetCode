#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> findMatrix(vector<int>& nums) {
        vector<vector<int>> retVal;

        unordered_map<int, int> hashTable;
        for (int num : nums) {
            hashTable[num] += 1;
        }

        while (hashTable.empty() == false) {
            vector<int> row;
            for (auto iterator : hashTable) {
                int key = iterator.first;
                row.emplace_back(key);
                hashTable[key] -= 1;
            }
            retVal.emplace_back(row);

            for (auto iterator : row) {
                if (hashTable[iterator] == 0) {
                    hashTable.erase(iterator);
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 3, 4, 1, 2, 3, 1}}, {{1, 2, 3, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,3,4,1,2,3,1]
     *  Output: [[1,3,4,2],[1,3],[1]]
     *
     *  Input: nums = [1,2,3,4]
     *  Output: [[4,3,2,1]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.findMatrix(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

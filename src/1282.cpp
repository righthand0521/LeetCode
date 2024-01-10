#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        vector<vector<int>> retVal;

        map<int, vector<int>> hashTable;

        int groupSizesSize = groupSizes.size();
        for (int i = 0; i < groupSizesSize; ++i) {
            hashTable[groupSizes[i]].emplace_back(i);
        }

        for (auto [key, value] : hashTable) {
            int groupSize = value.size() / key;
            for (int i = 0; i < groupSize; ++i) {
                vector<int> group(value.begin() + key * i, value.begin() + key * (i + 1));
                retVal.emplace_back(group);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> groupSizes;
    };
    vector<subject> testData{{{3, 3, 3, 3, 3, 1, 3}}, {{2, 1, 3, 3, 3, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: groupSizes = [3,3,3,3,3,1,3]
     *  Output: [[5],[0,1,2],[3,4,6]]
     *
     *  Input: groupSizes = [2,1,3,3,3,2]
     *  Output: [[1],[0,5],[2,3,4]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: groupSizes = [";
        for (long unsigned int j = 0; j < testData[i].groupSizes.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].groupSizes[j];
        }
        cout << "]\n";

        answer = cSolution.groupThePeople(testData[i].groupSizes);
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

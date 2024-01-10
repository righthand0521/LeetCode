#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
#define HASH_TABLE (1)
#define SORT (1)
   public:
    vector<vector<int>> mergeSimilarItems(vector<vector<int>>& items1, vector<vector<int>>& items2) {
        vector<vector<int>> retVal;

#if (HASH_TABLE)
        cout << "HASH_TABLE\n";

        map<int, int> hashTable;
        for (auto& item : items1) {
            hashTable[item[0]] += item[1];
        }
        for (auto& item : items2) {
            hashTable[item[0]] += item[1];
        }

        for (auto& [key, value] : hashTable) {
            retVal.push_back({key, value});
        }
#elif (SORT)
        cout << "SORT\n";

        sort(items1.begin(), items1.end(), [&](const vector<int>& x, const vector<int>& y) { return (x[0] < y[0]); });
        sort(items2.begin(), items2.end(), [&](const vector<int>& x, const vector<int>& y) { return (x[0] < y[0]); });

        int len1 = items1.size();
        int len2 = items2.size();
        int idx1 = 0;
        int idx2 = 0;
        while ((idx1 < len1) && (idx2 < len2)) {
            vector<int> iter(2);
            if (items1[idx1][0] == items2[idx2][0]) {
                iter[0] = items1[idx1][0];
                iter[1] = items1[idx1][1] + items2[idx2][1];
                ++idx1;
                ++idx2;
            } else if (items1[idx1][0] < items2[idx2][0]) {
                iter[0] = items1[idx1][0];
                iter[1] = items1[idx1][1];
                ++idx1;
            } else if (items1[idx1][0] > items2[idx2][0]) {
                iter[0] = items2[idx2][0];
                iter[1] = items2[idx2][1];
                ++idx2;
            }
            retVal.push_back(iter);
        }
        while (idx1 < len1) {
            vector<int> iter(2);
            iter[0] = items1[idx1][0];
            iter[1] = items1[idx1][1];
            retVal.push_back(iter);
            ++idx1;
        }
        while (idx2 < len2) {
            vector<int> iter(2);
            iter[0] = items2[idx2][0];
            iter[1] = items2[idx2][1];
            retVal.push_back(iter);
            ++idx2;
        }
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> items1;
        vector<vector<int>> items2;
    };
    vector<subject> testData{{{{1, 1}, {4, 5}, {3, 8}}, {{3, 1}, {1, 5}}},
                             {{{1, 1}, {3, 2}, {2, 3}}, {{2, 1}, {3, 2}, {1, 3}}},
                             {{{1, 1}, {2, 2}}, {{7, 1}, {2, 2}, {1, 4}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: items1 = [[1,1],[4,5],[3,8]], items2 = [[3,1],[1,5]]
     *  Output: [[1,6],[3,9],[4,5]]
     *
     *  Input: items1 = [[1,1],[3,2],[2,3]], items2 = [[2,1],[3,2],[1,3]]
     *  Output: [[1,4],[2,4],[3,4]]
     *
     *  Input: items1 = [[1,3],[2,2]], items2 = [[7,1],[2,2],[1,4]]
     *  Output: [[1,7],[2,4],[7,1]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: items1 = [";
        for (long unsigned int j = 0; j < testData[i].items1.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].items1[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].items1[j][k];
            }
            cout << "]";
        }
        cout << "], items2 = [";
        for (long unsigned int j = 0; j < testData[i].items2.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].items2[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].items2[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.mergeSimilarItems(testData[i].items1, testData[i].items2);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int binarySearch(vector<vector<int>>& items, int targetPrice) {
        int retVal = 0;

        int left = 0;
        int right = items.size() - 1;
        while (left <= right) {
            int middle = (left + right) / 2;
            if (items[middle][0] > targetPrice) {
                right = middle - 1;
            } else {
                retVal = max(retVal, items[middle][1]);
                left = middle + 1;
            }
        }

        return retVal;
    }
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
        vector<int> retVal;

        sort(items.begin(), items.end(), [](vector<int>& a, vector<int>& b) {
            // ascending order
            return a[0] < b[0];
        });

        int maxBeauty = items[0][1];
        for (auto& item : items) {
            maxBeauty = max(maxBeauty, item[1]);
            item[1] = maxBeauty;
        }

        for (int query : queries) {
            retVal.emplace_back(binarySearch(items, query));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> items;
        vector<int> queries;
    };
    vector<subject> testData{{{{1, 2}, {3, 2}, {2, 4}, {5, 6}, {3, 5}}, {1, 2, 3, 4, 5, 6}},
                             {{{1, 2}, {1, 2}, {1, 3}, {1, 4}}, {1}},
                             {{{10, 1000}}, {5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: items = [[1,2],[3,2],[2,4],[5,6],[3,5]], queries = [1,2,3,4,5,6]
     *  Output: [2,4,5,5,6,6]
     *
     *  Input: items = [[1,2],[1,2],[1,3],[1,4]], queries = [1]
     *  Output: [4]
     *
     *  Input: items = [[10,1000]], queries = [5]
     *  Output: [0]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: items = [";
        for (long unsigned int j = 0; j < testData[i].items.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].items[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].items[j][k];
            }
            cout << "]";
        }
        cout << "], queries = [";
        for (long unsigned int j = 0; j < testData[i].queries.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].queries[j];
        }
        cout << "]\n";

        answer = cSolution.maximumBeauty(testData[i].items, testData[i].queries);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

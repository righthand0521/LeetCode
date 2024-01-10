#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   public:
    int find(vector<int>& uf, int x) {
        int retVal = 0;

        if (uf[x] != x) {
            uf[x] = find(uf, uf[x]);
        }
        retVal = uf[x];

        return retVal;
    }
    void merge(vector<int>& uf, int x, int y) {
        x = find(uf, x);
        y = find(uf, y);
        uf[y] = x;
    }
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        vector<bool> retVal(queries.size(), false);

        sort(edgeList.begin(), edgeList.end(), [](vector<int>& e1, vector<int>& e2) {
            // ascending order
            return e1[2] < e2[2];
        });

        vector<int> index(queries.size());
        iota(index.begin(), index.end(), 0);
        sort(index.begin(), index.end(), [&](int i1, int i2) {
            // ascending order
            return queries[i1][2] < queries[i2][2];
        });

        vector<int> uf(n);
        iota(uf.begin(), uf.end(), 0);
        int k = 0;
        for (auto i : index) {
            while ((k < (int)edgeList.size()) && (edgeList[k][2] < queries[i][2])) {
                merge(uf, edgeList[k][0], edgeList[k][1]);
                k++;
            }

            if (find(uf, queries[i][0]) == find(uf, queries[i][1])) {
                retVal[i] = true;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> edgeList;
        vector<vector<int>> queries;
    };
    vector<subject> testData{{3, {{0, 1, 2}, {1, 2, 4}, {2, 0, 8}, {1, 0, 16}}, {{0, 1, 2}, {0, 2, 5}}},
                             {5, {{0, 1, 10}, {1, 2, 5}, {2, 3, 9}, {3, 4, 13}}, {{0, 4, 14}, {1, 4, 13}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3, edgeList = [[0,1,2],[1,2,4],[2,0,8],[1,0,16]], queries = [[0,1,2],[0,2,5]]
     *  Output: [false,true]
     *
     *  Input: n = 5, edgeList = [[0,1,10],[1,2,5],[2,3,9],[3,4,13]], queries = [[0,4,14],[1,4,13]]
     *  Output: [true,false]
     */

    Solution cSolution;
    vector<bool> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", edgeList = [";
        for (long unsigned int j = 0; j < testData[i].edgeList.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edgeList[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edgeList[j][k];
            }
            cout << "]";
        }
        cout << "], queries = [";
        for (long unsigned int j = 0; j < testData[i].queries.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].queries[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].queries[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.distanceLimitedPathsExist(testData[i].n, testData[i].edgeList, testData[i].queries);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << (answer[j] == true ? "true" : "false");
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

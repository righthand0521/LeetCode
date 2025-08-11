#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    static constexpr int MODULO = 1e9 + 7;  // Since the answer can be very large, return it modulo 10^9 + 7.

   public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        vector<int> retVal;

        vector<int> bins;
        int rep = 1;
        while (n > 0) {
            if (n % 2 == 1) {
                bins.emplace_back(rep);
            }
            n /= 2;
            rep *= 2;
        }

        for (const auto& query : queries) {
            int left = query[0];
            int right = query[1];
            int cur = 1;
            for (int i = left; i <= right; ++i) {
                cur = static_cast<long long>(cur) * bins[i] % MODULO;
            }
            retVal.emplace_back(cur);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> queries;
    };
    vector<subject> testData{{15, {{0, 1}, {2, 2}, {0, 3}}}, {2, {{0, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 15, queries = [[0,1],[2,2],[0,3]]
     *  Output: [2,4,64]
     *
     *  Input: n = 2, queries = [[0,0]]
     *  Output: [2]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", queries = [";
        for (long unsigned int j = 0; j < testData[i].queries.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].queries[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].queries[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.productQueries(testData[i].n, testData[i].queries);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

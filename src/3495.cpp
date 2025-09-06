#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    long long get(int num) {
        long long retVal = 0;

        int i = 1;
        int base = 1;
        while (base <= num) {
            retVal += (long long)((i + 1) / 2) * (min(base * 2 - 1, num) - base + 1);
            i++;
            base *= 2;
        }

        return retVal;
    }

   public:
    long long minOperations(vector<vector<int>>& queries) {
        long long retVal = 0;

        for (auto& query : queries) {
            retVal += (get(query[1]) - get(query[0] - 1) + 1) / 2;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> queries;
    };
    vector<subject> testData{{{{1, 2}, {2, 4}}}, {{{2, 6}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: queries = [[1,2],[2,4]]
     *  Output: 3
     *
     *  Input: queries = [[2,6]]
     *  Output: 4
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: queries = [";
        for (long unsigned int j = 0; j < testData[i].queries.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].queries[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].queries[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.minOperations(testData[i].queries);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

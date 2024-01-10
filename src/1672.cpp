#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximumWealth(vector<vector<int>>& accounts) {
        int retVal = 0;

        int sum;
        for (long unsigned int i = 0; i < accounts.size(); ++i) {
            sum = 0;
            for (long unsigned int j = 0; j < accounts[i].size(); ++j) {
                sum += accounts[i][j];
            }
            retVal = (retVal > sum ? retVal : sum);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> accounts;
    };
    vector<subject> testData{{{{1, 2, 3}, {3, 2, 1}}}, {{{1, 5}, {7, 3}, {3, 5}}}, {{{2, 8, 7}, {7, 1, 3}, {1, 9, 5}}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: accounts = [";
        for (long unsigned int j = 0; j < testData[i].accounts.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].accounts[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].accounts[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.maximumWealth(testData[i].accounts);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

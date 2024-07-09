#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    double averageWaitingTime(vector<vector<int>>& customers) {
        double retVal = 0;

        int customersSize = customers.size();

        int nextIdleTime = 0;
        double netWaitTime = 0;
        for (int i = 0; i < customersSize; ++i) {
            nextIdleTime = max(customers[i][0], nextIdleTime) + customers[i][1];
            netWaitTime += (nextIdleTime - customers[i][0]);
        }
        retVal = netWaitTime / customersSize;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> customers;
    };
    vector<subject> testData{{{{1, 2}, {2, 5}, {4, 3}}}, {{{5, 2}, {5, 4}, {10, 3}, {20, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: customers = [[1,2],[2,5],[4,3]]
     *  Output: 5.00000
     *
     *  Input: customers = [[5,2],[5,4],[10,3],[20,1]]
     *  Output: 3.25000
     */

    Solution cSolution;
    double answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: customers = [";
        for (long unsigned int j = 0; j < testData[i].customers.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].customers[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].customers[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.averageWaitingTime(testData[i].customers);
        cout.setf(ios::fixed);
        cout.precision(5);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

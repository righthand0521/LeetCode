#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int bestClosingTime(string customers) {
        int retVal = 0;

        /* At any index, the penalty is the sum of prefix count of 'N' and suffix count of 'Y'.
         *  Y Y N Y     N N N N N     Y Y Y Y
         *  3 2 1 1 0   0 0 0 0 0 0   4 3 2 1 0
         *  0 0 0 1 1   0 1 2 3 4 5   0 0 0 0 0
         */
        int penalty = count(customers.begin(), customers.end(), 'Y');
        int minPenalty = penalty;
        int customersSize = customers.size();
        for (int i = 0; i < customersSize; ++i) {
            if (customers[i] == 'Y') {
                --penalty;
            } else if (customers[i] == 'N') {
                ++penalty;
            }

            if (minPenalty > penalty) {
                minPenalty = penalty;
                retVal = i + 1;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string customers;
    };
    vector<subject> testData{{"YYNY"}, {"NNNNN"}, {"YYYY"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: customers = "YYNY"
     *  Output: 2
     *
     *  Input: customers = "NNNNN"
     *  Output: 0
     *
     *  Input: customers = "YYYY"
     *  Output: 4
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: customers = \"" << testData[i].customers << "\"\n";

        answer = cSolution.bestClosingTime(testData[i].customers);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

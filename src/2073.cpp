#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        int retVal = 0;

        int ticketsSize = tickets.size();
        for (int i = 0; i < ticketsSize; ++i) {
            if (i <= k) {
                retVal += min(tickets[i], tickets[k]);
            } else {
                retVal += min(tickets[i], (tickets[k] - 1));
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> tickets;
        int k;
    };
    vector<subject> testData{{{2, 3, 2}, 2}, {{5, 1, 1, 1}, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: tickets = [2,3,2], k = 2
     *  Output: 6
     *
     *  Input: tickets = [5,1,1,1], k = 0
     *  Output: 8
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: tickets = [";
        for (long unsigned int j = 0; j < testData[i].tickets.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].tickets[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.timeRequiredToBuy(testData[i].tickets, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

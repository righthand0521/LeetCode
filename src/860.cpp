#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool lemonadeChange(vector<int>& bills) {
        bool retVal = true;

        int five = 0;
        int ten = 0;
        for (int bill : bills) {
            if (bill == 5) {
                five += 1;
            } else if (bill == 10) {
                if (five == 0) {
                    retVal = false;
                    break;
                }
                five -= 1;
                ten += 1;
            } else if (bill == 20) {
                if ((ten >= 1) && (five >= 1)) {
                    ten -= 1;
                    five -= 1;
                } else if (five >= 3) {
                    five -= 3;
                } else {
                    retVal = false;
                    break;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> bills;
    };
    vector<subject> testData{{{5, 5, 5, 10, 20}}, {{5, 5, 10, 10, 20}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: bills = [5,5,5,10,20]
     *  Output: true
     *
     *  Input: bills = [5,5,10,10,20]
     *  Output: false
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: bills = [";
        for (long unsigned int j = 0; j < testData[i].bills.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].bills[j];
        }
        cout << "]\n";

        answer = cSolution.lemonadeChange(testData[i].bills);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

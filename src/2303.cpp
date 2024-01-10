#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    double calculateTax(vector<vector<int>>& brackets, int income) {
        double retVal = 0;

        int lower = 0;
        int upper;
        int percent;
        for (long unsigned int i = 0; i < brackets.size(); ++i) {
            upper = brackets[i][0];
            percent = brackets[i][1];
            retVal += ((double)((min(income, upper) - lower) * percent) / 100);
            lower = upper;

            if (income < upper) {
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> brackets;
        int income;
    };
    vector<subject> testData{{{{3, 50}, {7, 10}, {12, 25}}, 10}, {{{1, 0}, {4, 25}, {5, 50}}, 2}, {{{2, 50}}, 0}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    double answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: brackets = [";
        for (long unsigned int j = 0; j < testData[i].brackets.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].brackets[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].brackets[j][k];
            }
            cout << "]";
        }
        cout << "], income = " << testData[i].income << "\n";

        answer = cSolution.calculateTax(testData[i].brackets, testData[i].income);
        cout.setf(ios::fixed);
        cout.precision(5);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

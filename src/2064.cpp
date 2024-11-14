#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    bool canDistribute(int x, vector<int>& quantities, int n) {
        bool retVal = false;

        int quantitiesSize = quantities.size();
        int j = 0;
        int remaining = quantities[j];
        for (int i = 0; i < n; i++) {
            if (remaining > x) {
                remaining -= x;
                continue;
            }

            j++;
            if (j == quantitiesSize) {
                retVal = true;
                break;
            }
            remaining = quantities[j];
        }

        return retVal;
    }

   public:
    int minimizedMaximum(int n, vector<int>& quantities) {
        int retVal = 0;

        int left = 0;
        int right = *max_element(quantities.begin(), quantities.end());
        while (left < right) {
            int middle = (left + right) / 2;
            if (canDistribute(middle, quantities, n) == true) {
                right = middle;
            } else {
                left = middle + 1;
            }
        }
        retVal = left;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<int> quantities;
    };
    vector<subject> testData{{6, {11, 6}}, {7, {15, 10, 10}}, {1, {100000}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 6, quantities = [11,6]
     *  Output: 3
     *
     *  Input: n = 7, quantities = [15,10,10]
     *  Output: 5
     *
     *  Input: n = 1, quantities = [100000]
     *  Output: 100000
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", quantities = [";
        for (long unsigned int j = 0; j < testData[i].quantities.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].quantities[j];
        }
        cout << "]\n";

        answer = cSolution.minimizedMaximum(testData[i].n, testData[i].quantities);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

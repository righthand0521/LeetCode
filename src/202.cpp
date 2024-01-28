#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isHappy(int n) {
        bool retVal = false;

        unordered_set<int> hashTable;
        while (n != 1) {
            if (hashTable.find(n) != hashTable.end()) {
                break;
            }
            hashTable.insert(n);

            int square = 0;
            while (n > 0) {
                int digit = n % 10;
                square += (digit * digit);
                n /= 10;
            }
            n = square;
        }

        if (n == 1) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{19}, {2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 19
     *  Output: true
     *
     *  Input: n = 2
     *  Output: false
     */

    Solution cSolution;
    bool answer = false;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.isHappy(testData[i].n);
        cout << "Output: " << ((answer == true) ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

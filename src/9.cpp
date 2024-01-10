#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isPalindrome(int x) {
        bool retVal = false;

        if (x < 0) {
            return retVal;
        }

        // Constraints: -2 ^ 31 <= x <= 2 ^ 31 - 1
        long original = x;
        long palindrome = 0;
        while (x > 0) {
            palindrome *= 10;
            palindrome += (x % 10);
            x /= 10;
        }

        if (original == palindrome) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int x;
    };
    vector<subject> testData{{121}, {-121}, {10}, {1234567899}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: x = 121
     *  Output: true
     *
     *  Input: x = -121
     *  Output: false
     *
     *  Input: x = 10
     *  Output: false
     *
     *  Input: x = 1234567899
     *  Output: false
     */

    Solution cSolution;
    bool answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: x = " << testData[i].x << "\n";

        answer = cSolution.isPalindrome(testData[i].x);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

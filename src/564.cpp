#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   private:
    long halfToPalindrome(long left, bool even) {
        long retVal = left;

        if (even == false) {
            left = left / 10;
        }

        while (left > 0) {
            retVal = retVal * 10 + left % 10;
            left /= 10;
        }

        return retVal;
    }

   public:
    string nearestPalindromic(string n) {
        string retVal = "";

        int nSize = n.size();

        int i = (nSize % 2 == 0) ? (nSize / 2 - 1) : (nSize / 2);
        long firstHalf = stol(n.substr(0, i + 1));

        /* Generate possible palindromic candidates:
         *  1. Create a palindrome by mirroring the first half.
         *  2. Create a palindrome by mirroring the first half incremented by 1.
         *  3. Create a palindrome by mirroring the first half decremented by 1.
         *  4. Handle edge cases by considering palindromes of the
         *     form 999...and 100...001 (smallest and largest n-digit palindromes).
         */
        vector<long> candidates;
        candidates.push_back(halfToPalindrome(firstHalf, nSize % 2 == 0));
        candidates.push_back(halfToPalindrome(firstHalf + 1, nSize % 2 == 0));
        candidates.push_back(halfToPalindrome(firstHalf - 1, nSize % 2 == 0));
        candidates.push_back((long)pow(10, nSize - 1) - 1);
        candidates.push_back((long)pow(10, nSize) + 1);

        long diff = numeric_limits<long>::max();
        long res = 0;
        long nl = stol(n);
        for (auto candidate : candidates) {
            if (candidate == nl) {
                continue;
            }

            if (abs(candidate - nl) < diff) {
                diff = abs(candidate - nl);
                res = candidate;
            } else if (abs(candidate - nl) == diff) {
                res = min(res, candidate);
            }
        }
        retVal = to_string(res);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string n;
    };
    vector<subject> testData{{"123"}, {"1"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = "123"
     *  Output: "121"
     *
     *  Input: n = "1"
     *  Output: "0"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = \"" << testData[i].n << "\"\n";

        answer = cSolution.nearestPalindromic(testData[i].n);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

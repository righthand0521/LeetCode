#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    long long countGoodIntegers(int n, int k) {
        long long retVal = 0;

        // Enumerate the number of palindrome numbers of n digits
        int base = pow(10, (n - 1) / 2);
        int skip = n & 1;
        unordered_set<string> dict;
        for (int i = base; i < base * 10; i++) {
            string s = to_string(i);
            s += string(s.rbegin() + skip, s.rend());
            long long palindromicInteger = stoll(s);

            // If the current palindrome number is a k-palindromic integer
            if (palindromicInteger % k == 0) {
                sort(s.begin(), s.end());
                dict.emplace(s);
            }
        }

        vector<long long> factorial(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            factorial[i] = factorial[i - 1] * i;
        }
        for (const string& s : dict) {
            vector<int> cnt(10);
            for (char c : s) {
                cnt[c - '0']++;
            }

            // Calculate permutations and combinations
            long long tot = (n - cnt[0]) * factorial[n - 1];
            for (int x : cnt) {
                tot /= factorial[x];
            }
            retVal += tot;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int k;
    };
    vector<subject> testData{{3, 5}, {1, 4}, {5, 6}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3, k = 5
     *  Output: 27
     *
     *  Input: n = 1, k = 4
     *  Output: 2
     *
     *  Input: n = 5, k = 6
     *  Output: 2468
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", k = " << testData[i].k << "\n";

        answer = cSolution.countGoodIntegers(testData[i].n, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

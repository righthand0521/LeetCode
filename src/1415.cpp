#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    string getHappyString(int n, int k) {
        string retVal = "";

        // Calculate the total number of happy strings of length n
        int total = 3 * (1 << (n - 1));

        // If k is greater than the total number of happy strings, return an empty string
        if (k > total) {
            return retVal;
        }

        // Initialize result with 'a' characters
        retVal.resize(n, 'a');
        //  Define mappings for the next smallest and greatest valid characters
        unordered_map<char, char> nextSmallest = {{'a', 'b'}, {'b', 'a'}, {'c', 'a'}};
        unordered_map<char, char> nextGreatest = {{'a', 'c'}, {'b', 'c'}, {'c', 'b'}};
        // Calculate the starting indices for strings beginning with 'a', 'b', and 'c'
        int startA = 1;
        int startB = startA + (1 << (n - 1));
        int startC = startB + (1 << (n - 1));
        // Determine the first character based on the value of k
        if (k < startB) {
            retVal[0] = 'a';
            k -= startA;
        } else if (k < startC) {
            retVal[0] = 'b';
            k -= startB;
        } else {
            retVal[0] = 'c';
            k -= startC;
        }

        // Iterate through the remaining positions in the result string
        for (int charIndex = 1; charIndex < n; charIndex++) {
            // Calculate the midpoint of the group for the current character position
            int midpoint = (1 << (n - charIndex - 1));
            // Determine the next character based on the value of k
            if (k < midpoint) {
                retVal[charIndex] = nextSmallest[retVal[charIndex - 1]];
            } else {
                retVal[charIndex] = nextGreatest[retVal[charIndex - 1]];
                k -= midpoint;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int k;
    };
    vector<subject> testData{{1, 3}, {1, 4}, {3, 9}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 1, k = 3
     *  Output: "c"
     *
     *  Input: n = 1, k = 4
     *  Output: ""
     *
     *  Input: n = 3, k = 9
     *  Output: "cab"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", k = " << testData[i].k << "\n";

        answer = cSolution.getHappyString(testData[i].n, testData[i].k);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

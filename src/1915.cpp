#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    long long wonderfulSubstrings(string word) {
        long long retVal = 0;

        // Create the frequency map : Key = bitmask, Value = frequency of bitmask key
        unordered_map<int, int> frequency;
        frequency[0] = 1;

        int mask = 0;
        for (auto c : word) {
            // a string word that consists of the first ten lowercase English letters
            int bit = c - 'a';

            // Flip the parity of the c-th bit in the running prefix mask
            mask ^= (1 << bit);

            // Count smaller prefixes that create substrings with no odd occurring letters
            auto iterator = frequency.find(mask);
            if (iterator != frequency.end()) {
                retVal += frequency[mask];
                frequency[mask] += 1;
            } else {
                frequency[mask] = 1;
            }

            // Loop through every possible letter that can appear an odd number of times in a substring
            for (int odd = 0; odd < 10; ++odd) {
                int bitmask = mask ^ (1 << odd);
                auto iterator = frequency.find(bitmask);
                if (iterator != frequency.end()) {
                    retVal += frequency[bitmask];
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string word;
    };
    vector<subject> testData{{"aba"}, {"aabb"}, {"he"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: word = "aba"
     *  Output: 4
     *
     *  Input: word = "aabb"
     *  Output: 9
     *
     *  Input: word = "he"
     *  Output: 2
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: word = \"" << testData[i].word << "\"\n";

        answer = cSolution.wonderfulSubstrings(testData[i].word);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

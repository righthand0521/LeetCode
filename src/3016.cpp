#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int letters = 26;  // word consists of lowercase English letters.

   public:
    int minimumPushes(string word) {
        int retVal = 0;

        vector<int> frequency(letters, 0);
        for (char& c : word) {
            ++frequency[c - 'a'];
        }
        sort(frequency.rbegin(), frequency.rend());

        for (int i = 0; i < letters; ++i) {
            if (frequency[i] == 0) {
                break;
            }
            retVal += (i / 8 + 1) * frequency[i];
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string word;
    };
    vector<subject> testData{{"abcde"}, {"xyzxyzxyzxyz"}, {"aabbccddeeffgghhiiiiii"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: word = "abcde"
     *  Output: 5
     *
     *  Input: word = "xyzxyzxyzxyz"
     *  Output: 12
     *
     *  Input: word = "aabbccddeeffgghhiiiiii"
     *  Output: 24
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: word = \"" << testData[i].word << "\"\n";

        answer = cSolution.minimumPushes(testData[i].word);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

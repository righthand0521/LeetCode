#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    static constexpr int MODULO = (int)(1e9 + 7);

   public:
    int possibleStringCount(string word, int k) {
        int retVal = 0;

        int wordSize = word.size();
        int count = 1;
        vector<int> frequency;
        for (int i = 1; i < wordSize; ++i) {
            if (word[i] == word[i - 1]) {
                ++count;
            } else {
                frequency.emplace_back(count);
                count = 1;
            }
        }
        frequency.emplace_back(count);
        int frequencySize = frequency.size();

        long long longlongAnswer = 1;
        for (int value : frequency) {
            longlongAnswer = longlongAnswer * value % MODULO;
        }

        if (frequencySize >= k) {
            retVal = longlongAnswer;
            return retVal;
        }

        vector<int> g(k, 1);
        for (int i = 0; i < frequencySize; ++i) {
            vector<int> fNext(k, 0);
            for (int j = 1; j < k; ++j) {
                fNext[j] = g[j - 1];
                if (j - frequency[i] - 1 >= 0) {
                    fNext[j] = (fNext[j] - g[j - frequency[i] - 1] + MODULO) % MODULO;
                }
            }

            vector<int> gNext(k, 0);
            gNext[0] = fNext[0];
            for (int j = 1; j < k; ++j) {
                gNext[j] = (gNext[j - 1] + fNext[j]) % MODULO;
            }

            g = move(gNext);
        }

        retVal = (longlongAnswer - g[k - 1] + MODULO) % MODULO;

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string word;
        int k;
    };
    vector<subject> testData{{"aabbccdd", 7}, {"aabbccdd", 8}, {"aaabbb", 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: word = "aabbccdd", k = 7
     *  Output: 5
     *
     *  Input: word = "aabbccdd", k = 8
     *  Output: 1
     *
     *  Input: word = "aaabbb", k = 3
     *  Output: 8
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: word = \"" << testData[i].word << "\", k = " << testData[i].k << "\n";

        answer = cSolution.possibleStringCount(testData[i].word, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

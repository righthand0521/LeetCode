#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    string repeatLimitedString(string s, int repeatLimit) {
        string retVal;

        unordered_map<char, int> frequency;
        for (char ch : s) {
            frequency[ch]++;
        }

        priority_queue<char> maxHeap;
        for (auto& [ch, count] : frequency) {
            maxHeap.push(ch);
        }

        while (maxHeap.empty() == false) {
            char ch = maxHeap.top();
            maxHeap.pop();

            int count = frequency[ch];
            int use = min(count, repeatLimit);
            retVal.append(use, ch);
            frequency[ch] -= use;
            if ((frequency[ch] > 0) && (maxHeap.empty() == false)) {
                char nextCh = maxHeap.top();
                maxHeap.pop();

                retVal.push_back(nextCh);
                frequency[nextCh]--;
                if (frequency[nextCh] > 0) {
                    maxHeap.push(nextCh);
                }

                maxHeap.push(ch);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int repeatLimit;
    };
    vector<subject> testData{{"cczazcc", 3}, {"aababab", 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "cczazcc", repeatLimit = 3
     *  Output: "zzcccac"
     *
     *  Input: s = "aababab", repeatLimit = 2
     *  Output: "bbabaa"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: \"" << testData[i].s << "\", repeatLimit = " << testData[i].repeatLimit << "\n";

        answer = cSolution.repeatLimitedString(testData[i].s, testData[i].repeatLimit);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

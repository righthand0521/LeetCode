#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        bool retVal = false;

        int handSize = hand.size();
        if (handSize % groupSize != 0) {
            return retVal;
        }

        sort(hand.begin(), hand.end());

        unordered_map<int, int> count;
        for (auto& num : hand) {
            count[num]++;
        }

        for (auto& x : hand) {
            if (count.count(x) == 0) {
                continue;
            }

            for (int i = 0; i < groupSize; i++) {
                int num = x + i;
                if (count.count(num) == 0) {
                    return retVal;
                }

                count[num]--;
                if (count[num] == 0) {
                    count.erase(num);
                }
            }
        }
        retVal = true;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> hand;
        int groupSize;
    };
    vector<subject> testData{{{1, 2, 3, 6, 2, 3, 4, 7, 8}, 3}, {{1, 2, 3, 4, 5}, 4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
     *  Output: true
     *
     *  Input: hand = [1,2,3,4,5], groupSize = 4
     *  Output: false
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: hand = [";
        for (long unsigned int j = 0; j < testData[i].hand.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].hand[j];
        }
        cout << "], groupSize = " << testData[i].groupSize << "\n";

        answer = cSolution.isNStraightHand(testData[i].hand, testData[i].groupSize);
        cout << "Output: " << ((answer == true) ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

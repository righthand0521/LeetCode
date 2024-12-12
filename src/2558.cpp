#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    long long pickGifts(vector<int>& gifts, int k) {
        long long retVal = 0;

        priority_queue<int> giftsHeap(gifts.begin(), gifts.end());
        for (int i = 0; i < k; i++) {
            int maxElement = giftsHeap.top();
            giftsHeap.pop();
            giftsHeap.push(sqrt(maxElement));
        }

        while (giftsHeap.empty() == false) {
            retVal += giftsHeap.top();
            giftsHeap.pop();
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> gifts;
        int k;
    };
    vector<subject> testData{{{25, 64, 9, 4, 100}, 4}, {{1, 1, 1, 1}, 10}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: gifts = [25,64,9,4,100], k = 4
     *  Output: 29
     *
     *  Input: gifts = [1,1,1,1], k = 4
     *  Output: 4
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: gifts = [";
        for (long unsigned int j = 0; j < testData[i].gifts.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].gifts[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.pickGifts(testData[i].gifts, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

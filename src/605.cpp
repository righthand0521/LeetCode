#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        bool retVal = false;

        int flowerbedSize = flowerbed.size();
        for (int i = 0; i < flowerbedSize; ++i) {
            if (flowerbed[i] == 1) {
                continue;
            }

            if (i == 0) {
                if ((flowerbedSize == 1) || (flowerbed[i + 1] == 0)) {
                    --n;
                    flowerbed[i] = 1;
                }
            } else if (i == flowerbedSize - 1) {
                if (flowerbed[i - 1] == 0) {
                    --n;
                    flowerbed[i] = 1;
                }
            } else {
                if ((flowerbed[i - 1] == 0) && (flowerbed[i + 1] == 0)) {
                    --n;
                    flowerbed[i] = 1;
                }
            }
        }
        if (n <= 0) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> flowerbed;
        int n;
    };
    vector<subject> testData{{{1, 0, 0, 0, 1}, 1}, {{1, 0, 0, 0, 1}, 2}, {{0}, 0}, {{0}, 1}, {{1}, 0}, {{1}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: flowerbed = [1,0,0,0,1], n = 1
     *  Output: true
     *
     *  Input: flowerbed = [1,0,0,0,1], n = 2
     *  Output: false
     *
     *  Input: flowerbed = [0], n = 0
     *  Output: true
     *
     *  Input: flowerbed = [0], n = 1
     *  Output: true
     *
     *  Input: flowerbed = [1], n = 0
     *  Output: true
     *
     *  Input: flowerbed = [1], n = 1
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: flowerbed = [";
        for (long unsigned int j = 0; j < testData[i].flowerbed.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].flowerbed[j];
        }
        cout << "], n = " << testData[i].n << "\n";

        answer = cSolution.canPlaceFlowers(testData[i].flowerbed, testData[i].n);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

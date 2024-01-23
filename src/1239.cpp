#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void backtracking(vector<unsigned int>& masks, int start, int end, unsigned int mask, int* returnLength) {
        for (int i = start; i < end; ++i) {
            if ((mask & masks[i]) == 0) {
                backtracking(masks, i + 1, end, (mask | masks[i]), returnLength);
            }
        }

        int count = 0;
        while (mask) {
            count += (mask & 1);
            mask >>= 1;
        }
        (*returnLength) = max((*returnLength), count);
    }
    int maxLength(vector<string>& arr) {
        int retVal = 0;

        int arrSize = arr.size();
        vector<unsigned int> masks(arrSize, 0);
        for (int i = 0; i < arrSize; ++i) {
            for (char c : arr[i]) {
                unsigned int mask = 1 << (c - 'a');
                if ((mask & masks[i]) != 0) {
                    masks[i] = 0;
                    break;
                }
                masks[i] |= mask;
            }
        }
        backtracking(masks, 0, arrSize, 0, &retVal);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> arr;
    };
    vector<subject> testData{{{"un", "iq", "ue"}},
                             {{"cha", "r", "act", "ers"}},
                             {{"abcdefghijklmnopqrstuvwxyz"}},
                             {{"a", "abc", "d", "de", "def"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = ["un","iq","ue"]
     *  Output: 4
     *
     *  Input: arr = ["cha","r","act","ers"]
     *  Output: 6
     *
     *  Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
     *  Output: 26
     *
     *  Input: arr = ["a", "abc", "d", "de", "def"]
     *  Output: 6
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].arr[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.maxLength(testData[i].arr);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

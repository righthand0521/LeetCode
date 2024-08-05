#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    string kthDistinct(vector<string>& arr, int k) {
        string retVal = "";

        unordered_map<string, int> hashTable;
        for (string s : arr) {
            hashTable[s] += 1;
        }

        for (string s : arr) {
            if (hashTable[s] > 1) {
                continue;
            }

            k--;
            if (k == 0) {
                retVal = s;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> arr;
        int k;
    };
    vector<subject> testData{{{"d", "b", "c", "b", "c", "a"}, 2}, {{"aaa", "aa", "a"}, 1}, {{"a", "b", "a"}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = ["d","b","c","b","c","a"], k = 2
     *  Output: "a"
     *
     *  Input: arr = ["aaa","aa","a"], k = 1
     *  Output: "aaa"
     *
     *  Input: arr = ["a","b","a"], k = 3
     *  Output: ""
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].arr[j] << "\"";
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.kthDistinct(testData[i].arr, testData[i].k);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

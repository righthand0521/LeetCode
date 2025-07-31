#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    int subarrayBitwiseORs(vector<int>& arr) {
        int retVal = 0;

        unordered_set<int> result;
        unordered_set<int> current;
        current.insert(0);
        for (int x : arr) {
            unordered_set<int> current2;
            for (int y : current) {
                current2.insert(x | y);
            }
            current2.insert(x);
            current = current2;
            result.insert(current.begin(), current.end());
        }
        retVal = result.size();

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{0}}, {{1, 1, 2}}, {{1, 2, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [0]
     *  Output: 1
     *
     *  Input: arr = [1,1,2]
     *  Output: 3
     *
     *  Input: arr = [1,2,4]
     *  Output: 6
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.subarrayBitwiseORs(testData[i].arr);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

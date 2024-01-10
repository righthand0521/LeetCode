#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    bool uniqueOccurrences(vector<int>& arr) {
        bool retVal = false;

        unordered_map<int, int> occurrences;
        for (auto iterator : arr) {
            occurrences[iterator]++;
        }

        unordered_set<int> times;
        for (auto [key, value] : occurrences) {
            times.insert(value);
        }

        if (times.size() == occurrences.size()) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{1, 2, 2, 1, 1, 3}}, {{1, 2}}, {{-3, 0, 1, -3, 1, 1, 1, -3, 10, 0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [1,2,2,1,1,3]
     *  Output: true
     *
     *  Input: arr = [1,2]
     *  Output: false
     *
     *  Input: arr = [-3,0,1,-3,1,1,1,-3,10,0]
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.uniqueOccurrences(testData[i].arr);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

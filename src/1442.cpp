#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int countTriplets(vector<int>& arr) {
        int retVal = 0;

        int arrSize = arr.size();

        // Maps to store counts and totals of XOR values encountered
        unordered_map<int, int> countMap = {{0, 1}};
        unordered_map<int, int> totalMap;

        // Iterating through the array
        int prefix = 0;
        for (int i = 0; i < arrSize; ++i) {
            // Calculating XOR prefix
            prefix ^= arr[i];

            // Calculating contribution of current element to the result
            retVal += countMap[prefix] * i - totalMap[prefix];

            // Updating total count of current XOR value
            totalMap[prefix] += i + 1;
            countMap[prefix] += 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
    };
    vector<subject> testData{{{2, 3, 1, 6, 7}}, {{1, 1, 1, 1, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr = [2,3,1,6,7]
     *  Output: 4
     *
     *  Input: arr = [1,1,1,1,1]
     *  Output: 10
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].arr[j];
        }
        cout << "]\n";

        answer = cSolution.countTriplets(testData[i].arr);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

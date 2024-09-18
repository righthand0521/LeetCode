#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string largestNumber(vector<int> &nums) {
        string retVal;

        vector<string> numStrings;
        for (int num : nums) {
            numStrings.push_back(to_string(num));
        }
        sort(numStrings.begin(), numStrings.end(), [](string &a, string &b) {
            //
            return a + b > b + a;
        });

        if (numStrings[0] == "0") {
            retVal = "0";
        } else {
            retVal = "";
            for (string &numStr : numStrings) {
                retVal += numStr;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{10, 2}}, {{3, 30, 34, 5, 9}},       {{432, 43243}}, {{999999991, 9}},
                             {{0, 0}},  {{1000000000, 1000000000}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [10,2]
     *  Output: "210"
     *
     *  Input: nums = [3,30,34,5,9]
     *  Output: "9534330"
     *
     *  Input: nums = [432, 43243]
     *  Output: "43243432"
     *
     *  Input: nums = [999999991, 9]
     *  Output: "9999999991"
     *
     *  Input: nums = [0, 0]
     *  Output: "0"
     *
     *  Input: [1000000000, 1000000000]
     *  Output: "10000000001000000000"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.largestNumber(testData[i].nums);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

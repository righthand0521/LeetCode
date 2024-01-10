#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string largestNumber(vector<int>& nums) {
        string retVal;

        sort(nums.begin(), nums.end(), [](const int& n1, const int& n2) {
            /* Example
             *  43243 432
             *  43243: 43243000 +   432 = 43243432
             *    432: 43200000 + 43243 = 43243243
             *
             *  432 43200
             *    432: 43200000 + 43200 = 43243200
             *  43200: 43200000 +   432 = 43200432
             */
            long digits1 = 10;
            while (digits1 <= n1) {
                digits1 *= 10;
            }
            long digits2 = 10;
            while (digits2 <= n2) {
                digits2 *= 10;
            }
            long comp1 = n1 * digits2 + n2;
            long comp2 = n2 * digits1 + n1;

            return (comp1 > comp2);
        });

        // Input: nums = [0, 0], Output: "0".
        if (nums[0] == 0) {
            retVal = "0";
            return retVal;
        }

        for (auto num : nums) {
            retVal += to_string(num);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{10, 2}}, {{3, 30, 34, 5, 9}}, {{432, 43243}}, {{999999991, 9}}, {{0, 0}}};
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

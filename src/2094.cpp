#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findEvenNumbers(vector<int>& digits) {
        vector<int> retVal;

        unordered_set<int> nums;
        int digitsSize = digits.size();
        for (int i = 0; i < digitsSize; ++i) {
            for (int j = 0; j < digitsSize; ++j) {
                for (int k = 0; k < digitsSize; ++k) {
                    if (i == j || j == k || i == k) {
                        continue;
                    }
                    int num = digits[i] * 100 + digits[j] * 10 + digits[k];
                    if ((num >= 100) && (num % 2 == 0)) {
                        nums.insert(num);
                    }
                }
            }
        }

        for (const int num : nums) {
            retVal.emplace_back(num);
        }
        sort(retVal.begin(), retVal.end());

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> digits;
    };
    vector<subject> testData{{{2, 1, 3, 0}}, {{2, 2, 8, 8, 2}}, {{3, 7, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: digits = [2,1,3,0]
     *  Output: [102,120,130,132,210,230,302,310,312,320]
     *
     *  Input: digits = [2,2,8,8,2]
     *  Output: [222,228,282,288,822,828,882]
     *
     *  Input: digits = [3,7,5]
     *  Output: []
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: digits = [";
        for (long unsigned int j = 0; j < testData[i].digits.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].digits[j];
        }
        cout << "]\n";

        answer = cSolution.findEvenNumbers(testData[i].digits);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

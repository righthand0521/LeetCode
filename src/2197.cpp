#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        vector<int> retVal;

        for (int num : nums) {
            while (retVal.empty() == false) {
                int g = gcd(retVal.back(), num);
                if (g > 1) {
                    num = retVal.back() / g * num;
                    retVal.pop_back();
                } else {
                    break;
                }
            }
            retVal.push_back(num);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{6, 4, 3, 2, 7, 6, 2}}, {{2, 2, 1, 1, 3, 3, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [6,4,3,2,7,6,2]
     *  Output: [12,7,6]
     *
     *  Input: nums = [2,2,1,1,3,3,3]
     *  Output: [2,1,1,3]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.replaceNonCoprimes(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

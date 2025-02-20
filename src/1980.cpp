#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string findDifferentBinaryString(vector<string>& nums) {
        string retVal;

        vector<int> intNums;
        for (string num : nums) {
            intNums.emplace_back(stoi(num, 0, 2));
        }

        int numsSize = nums.size();
        int maxRange = 1 << numsSize;  // n == nums.length, 1 <= n <= 16.
        for (int i = 0; i < maxRange; ++i) {
            if (find(intNums.begin(), intNums.end(), i) == intNums.end()) {
                retVal = bitset<16>(i).to_string();
                retVal = retVal.substr(16 - numsSize);
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> nums;
    };
    vector<subject> testData{{{"01", "10"}}, {{"00", "01"}}, {{"111", "011", "001"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = ["01","10"]
     *  Output: "11"
     *
     *  Input: nums = ["00","01"]
     *  Output: "11"
     *
     *  Input: nums = ["111","011","001"]
     *  Output: "101"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].nums[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.findDifferentBinaryString(testData[i].nums);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

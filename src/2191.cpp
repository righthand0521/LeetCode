#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();
        vector<pair<int, int>> storePairs;
        for (int idx = 0; idx < numsSize; ++idx) {
            int num = nums[idx];
            if (num == 0) {
                storePairs.push_back({mapping[num], idx});
                continue;
            }

            int mappedValue = 0;
            int shift = 1;
            while (num > 0) {
                mappedValue += (mapping[num % 10] * shift);
                num /= 10;
                shift *= 10;
            }
            storePairs.push_back({mappedValue, idx});
        }

        sort(storePairs.begin(), storePairs.end());
        for (auto pair : storePairs) {
            retVal.emplace_back(nums[pair.second]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> mapping;
        vector<int> nums;
    };
    vector<subject> testData{{{8, 9, 4, 0, 2, 1, 3, 5, 7, 6}, {991, 338, 38}},
                             {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, {789, 456, 123}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: mapping = [8,9,4,0,2,1,3,5,7,6], nums = [991,338,38]
     *  Output: [338,38,991]
     *
     *  Input: mapping = [0,1,2,3,4,5,6,7,8,9], nums = [789,456,123]
     *  Output: [123,456,789]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: mapping = [";
        for (long unsigned int j = 0; j < testData[i].mapping.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].mapping[j];
        }
        cout << "], nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.sortJumbled(testData[i].mapping, testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

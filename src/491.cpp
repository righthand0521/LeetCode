#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        vector<vector<int>> retVal;

        int n = nums.size();
        set<vector<int>> result;
        for (int bitmask = 1; bitmask < (1 << n); ++bitmask) {
            vector<int> sequence;
            for (int i = 0; i < n; ++i) {
                if (((bitmask >> i) & 1) == 1) {
                    sequence.push_back(nums[i]);
                }
            }

            if (sequence.size() >= 2) {
                bool isIncreasing = true;
                for (long unsigned int i = 0; i < sequence.size() - 1; ++i) {
                    isIncreasing &= sequence[i] <= sequence[i + 1];
                }
                if (isIncreasing) {
                    result.insert(sequence);
                }
            }
        }
        retVal = vector(result.begin(), result.end());

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{4, 6, 7, 7}}, {{4, 4, 3, 2, 1}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.findSubsequences(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

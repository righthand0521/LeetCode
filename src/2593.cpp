#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    long long findScore(vector<int>& nums) {
        long long retVal = 0;

        int numsSize = nums.size();

        auto cmp = [](pair<int, int>& pair1, pair<int, int>& pair2) {
            if (pair1.first != pair2.first) {
                return pair1.first > pair2.first;
            }
            return pair1.second > pair2.second;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> heap(cmp);
        for (int i = 0; i < numsSize; ++i) {
            heap.push(make_pair(nums[i], i));
        }

        vector<bool> marked(numsSize);
        while (heap.empty() == false) {
            pair<int, int> element = heap.top();
            heap.pop();
            int num = element.first;
            int index = element.second;

            if (marked[index] == true) {
                continue;
            }

            retVal += num;

            marked[index] = true;
            // mark adjacent elements if they exist
            if (index - 1 >= 0) {
                marked[index - 1] = true;
            }
            if (index + 1 < numsSize) {
                marked[index + 1] = true;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 1, 3, 4, 5, 2}}, {{2, 3, 5, 1, 3, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,1,3,4,5,2]
     *  Output: 7
     *
     *  Input: nums = [2,3,5,1,3,2]
     *  Output: 5
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.findScore(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

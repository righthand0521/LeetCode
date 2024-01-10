#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void merge(vector<int>& nums, int left, int right) {
        int middle = (left + right) / 2;
        int len1 = middle - left + 1;
        int len2 = right - middle;

        vector<int> first(len1);
        vector<int> second(len2);
        int idx;

        // copy elements
        idx = left;
        for (int i = 0; i < len1; i++) {
            first[i] = nums[idx++];
        }
        for (int i = 0; i < len2; i++) {
            second[i] = nums[idx++];
        }

        // merge 2 sorted array
        int index1 = 0;
        int index2 = 0;
        idx = left;
        while ((index1 < len1) && (index2 < len2)) {
            if (first[index1] < second[index2]) {
                nums[idx++] = first[index1++];
            } else {
                nums[idx++] = second[index2++];
            }
        }
        while (index1 < len1) {
            nums[idx++] = first[index1++];
        }
        while (index2 < len2) {
            nums[idx++] = second[index2++];
        }
    }
    void mergeSort(vector<int>& nums, int left, int right) {
        if (left >= right) {
            return;
        }
        int middle = (left + right) / 2;
        mergeSort(nums, left, middle);
        mergeSort(nums, middle + 1, right);
        merge(nums, left, right);
    }
    vector<int> sortArray(vector<int>& nums) {
        vector<int> retVal;

        retVal.assign(nums.begin(), nums.end());
        mergeSort(retVal, 0, retVal.size() - 1);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{5, 2, 3, 1}}, {{5, 1, 1, 2, 0, 0}}};
    int numberOfTestCase = testData.size();
    /* Example 1:
     *  Input: nums = [5,2,3,1]
     *  Output: [1,2,3,5]
     *
     *  Input: nums = [5,1,1,2,0,0]
     *  Output: [0,0,1,1,2,5]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.sortArray(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

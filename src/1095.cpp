#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class MountainArray {
   private:
    vector<int> arr;

   public:
    MountainArray(vector<int>& arr) {
        //
        this->arr = arr;
    }
    int get(int index) {
        int retVal = this->arr[index];

        return retVal;
    }
    int length() {
        int retVal = this->arr.size();

        return retVal;
    }
};
/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */
class Solution {
   public:
    int findInMountainArray(int target, MountainArray& mountainArr) {
        int retVal = -1;

        int arrSize = mountainArr.length();
        int left, right, middle, peak, value;

        // Find the index of the peak element
        left = 0;
        right = arrSize - 1;
        while (left < right) {
            middle = left + (right - left) / 2;
            if (mountainArr.get(middle) < mountainArr.get(middle + 1)) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        peak = left;

        // Search in the strictly increasing part of the array. If found, will be returned in the loop itself.
        left = 0;
        right = peak;
        while (left <= right) {
            middle = left + (right - left) / 2;
            value = mountainArr.get(middle);
            if (value == target) {
                retVal = middle;
                return retVal;
            } else if (value < target) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        // Search in the strictly decreasing part of the array. If found, will be returned in the loop itself.
        left = peak + 1;
        right = arrSize - 1;
        while (left <= right) {
            middle = left + (right - left) / 2;
            value = mountainArr.get(middle);
            if (value == target) {
                retVal = middle;
                return retVal;
            } else if (value > target) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr;
        int target;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5, 3, 1}, 3}, {{0, 1, 2, 4, 2, 1}, 3}, {{0, 5, 3, 1}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: array = [1,2,3,4,5,3,1], target = 3
     *  Output: 2
     *
     *  Input: array = [0,1,2,4,2,1], target = 3
     *  Output: -1
     *
     *  Input: array = [0,5,3,1], target = 1
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr = [";
        for (long unsigned int j = 0; j < testData[i].arr.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].arr[j];
        }
        cout << "], target = " << testData[i].target << "\n";

        MountainArray obj = MountainArray(testData[i].arr);

        answer = cSolution.findInMountainArray(testData[i].target, obj);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

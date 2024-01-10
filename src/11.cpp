#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxArea(vector<int>& height) {
        int retVal = 0;

        int heightSize = height.size();

        int left = 0;
        int right = heightSize - 1;
        while (left < right) {
            int leftValue = height[left];
            int rightValue = height[right];
            int minValue = min(leftValue, rightValue);
            retVal = max(retVal, minValue * (right - left));

            if (leftValue > rightValue) {
                right--;
            } else {
                left++;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> height;
    };
    vector<subject> testData{{{1, 8, 6, 2, 5, 4, 8, 3, 7}}, {{1, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: height = [1,8,6,2,5,4,8,3,7]
     *  Output: 49
     *
     *  Input: height = [1,1]
     *  utput: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: height = [";
        for (long unsigned int j = 0; j < testData[i].height.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].height[j];
        }
        cout << "]\n";

        answer = cSolution.maxArea(testData[i].height);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

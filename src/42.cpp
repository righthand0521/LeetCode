#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int trap(vector<int>& height) {
        int retVal = 0;

        int heightSize = height.size();
        if (heightSize == 0) {
            return retVal;
        }

        vector<int> leftMax(heightSize, 0);
        leftMax[0] = height[0];
        for (int i = 1; i < heightSize; ++i) {
            leftMax[i] = max(leftMax[i - 1], height[i]);
        }

        vector<int> rightMax(heightSize, 0);
        rightMax[heightSize - 1] = height[heightSize - 1];
        for (int i = heightSize - 2; i >= 0; --i) {
            rightMax[i] = max(rightMax[i + 1], height[i]);
        }

        for (int i = 0; i < heightSize; ++i) {
            retVal += (min(leftMax[i], rightMax[i]) - height[i]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> height;
    };
    vector<subject> testData{{{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}}, {{4, 2, 0, 3, 2, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
     *  Output: 6
     *
     *  Input: height = [4,2,0,3,2,5]
     *  Output: 9
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: height = [";
        for (long unsigned int j = 0; j < testData[i].height.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].height[j];
        }
        cout << "]\n";

        answer = cSolution.trap(testData[i].height);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

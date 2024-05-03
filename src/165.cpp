#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    /* Return the following:
     *  If version1 < version2, return -1.
     *  If version1 > version2, return 1.
     *  Otherwise, return 0.
     */
    int small = -1;
    int large = 1;
    int equal = 0;

   public:
    int compareVersion(string version1, string version2) {
        int retVal = equal;

        int version1Size = version1.size();
        int version2Size = version2.size();

        int idx1 = 0;
        int idx2 = 0;
        while ((idx1 < version1Size) || (idx2 < version2Size)) {
            int sum1 = 0;
            while ((idx1 < version1Size) && (version1[idx1] != '.')) {
                sum1 = 10 * sum1 + (version1[idx1] - '0');
                idx1++;
            }
            idx1++;

            int sum2 = 0;
            while ((idx2 < version2Size) && (version2[idx2] != '.')) {
                sum2 = 10 * sum2 + (version2[idx2] - '0');
                idx2++;
            }
            idx2++;

            if (sum1 > sum2) {
                retVal = large;
                break;
            } else if (sum1 < sum2) {
                retVal = small;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string version1;
        string version2;
    };
    vector<subject> testData{{"1.01", "1.001"}, {"1.0", "1.0.0"}, {"0.1", "1.1"}, {"1.1", "1.10"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: version1 = "1.01", version2 = "1.001"
     *  Output: 0
     *
     *  Input: version1 = "1.0", version2 = "1.0.0"
     *  Output: 0
     *
     *  Input: version1 = "0.1", version2 = "1.1"
     *  Output: -1
     *
     *  Input: version1 = "1.1", version2 = "1.10"
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: version1 = \"" << testData[i].version1 << "\"";
        cout << ", version2 = \"" << testData[i].version2 << "\"\n";

        answer = cSolution.compareVersion(testData[i].version1, testData[i].version2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

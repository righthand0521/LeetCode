#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
/* Return the following:
 *  If version1 < version2, return -1.
 *  If version1 > version2, return 1.
 *  Otherwise, return 0.
 */
#define COMPARE_SMALL (-1)
#define COMPARE_LARGE (1)
#define COMPARE_EQUAL (0)
   public:
    int compareVersion(string version1, string version2) {
        int retVal = COMPARE_EQUAL;

        int len1 = version1.size();
        int len2 = version2.size();
        int idx1 = 0;
        int idx2 = 0;
        while ((idx1 < len1) || (idx2 < len2)) {
            //
            vector<char> l1;
            while ((idx1 < len1) && (version1[idx1] != '.')) {
                l1.push_back(version1[idx1]);
                ++idx1;
            }
            ++idx1;

            vector<char> l2;
            while ((idx2 < len2) && (version2[idx2] != '.')) {
                l2.push_back(version2[idx2]);
                ++idx2;
            }
            ++idx2;

            //
            int count1 = l1.size();
            int count2 = l2.size();
            int count = max(count1, count2);
            for (int i = 0; i < count - count1; ++i) {
                l1.insert(l1.begin(), '0');
            }
            for (int i = 0; i < count - count2; ++i) {
                l2.insert(l2.begin(), '0');
            }

            //
            for (int i = 0; i < count; ++i) {
                if (l1[i] < l2[i]) {
                    retVal = COMPARE_SMALL;
                    return retVal;
                } else if (l1[i] > l2[i]) {
                    retVal = COMPARE_LARGE;
                    return retVal;
                }
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

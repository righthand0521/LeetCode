#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

struct Mat {
    static constexpr int MODULO = 1e9 + 7;
    static constexpr int letterSize = 26;  // s consists only of lowercase English letters.
    int a[letterSize][letterSize];

    Mat() {
        //
        memset(a, 0, sizeof(a));
    }
    Mat(const Mat& that) {
        for (int i = 0; i < letterSize; ++i) {
            for (int j = 0; j < letterSize; ++j) {
                a[i][j] = that.a[i][j];
            }
        }
    }
    Mat& operator=(const Mat& that) {
        if (this != &that) {
            for (int i = 0; i < letterSize; ++i) {
                for (int j = 0; j < letterSize; ++j) {
                    a[i][j] = that.a[i][j];
                }
            }
        }
        return *this;
    }
};
Mat operator*(const Mat& u, const Mat& v) {
    Mat retVal;

    for (int i = 0; i < Mat::letterSize; ++i) {
        for (int j = 0; j < Mat::letterSize; ++j) {
            for (int k = 0; k < Mat::letterSize; ++k) {
                retVal.a[i][j] = (retVal.a[i][j] + (long long)u.a[i][k] * v.a[k][j]) % Mat::MODULO;
            }
        }
    }

    return retVal;
}
class Solution {
   private:
    static constexpr int MODULO = 1e9 + 7;
    static constexpr int letterSize = 26;  // s consists only of lowercase English letters.

    // matrix exponentiation by squaring
    Mat quickmul(const Mat& x, int y) {
        Mat retVal;

        // identity matrix
        for (int i = 0; i < letterSize; ++i) {
            retVal.a[i][i] = 1;
        }

        Mat cur = x;
        while (y) {
            if (y & 1) {
                retVal = retVal * cur;
            }
            cur = cur * cur;
            y >>= 1;
        }

        return retVal;
    }

   public:
    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        int retVal = 0;

        Mat T;
        for (int i = 0; i < letterSize; ++i) {
            for (int j = 1; j <= nums[i]; ++j) {
                T.a[(i + j) % letterSize][i] = 1;
            }
        }

        Mat res = quickmul(T, t);

        vector<int> f(letterSize);
        for (char ch : s) {
            ++f[ch - 'a'];
        }

        for (int i = 0; i < letterSize; ++i) {
            for (int j = 0; j < letterSize; ++j) {
                retVal = (retVal + (long long)res.a[i][j] * f[j]) % MODULO;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int t;
        vector<int> nums;
    };
    vector<subject> testData{
        {"abcyy", 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2}},
        {"azbk", 1, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abcyy", t = 2, nums = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2]
     *  Output: 7
     *
     *  Input: s = "azbk", t = 1, nums = [2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2]
     *  Output: 8
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", t = " << testData[i].t << ", nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.lengthAfterTransformations(testData[i].s, testData[i].t, testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

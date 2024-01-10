#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <climits>

using namespace std;

class Solution {
public:
    bool isHappy(int n) {
        bool retVal = true;

        unordered_set<int> recordSet;
        int sum;
        int num = n;
        while (num != 1) {
            if (recordSet.find(num) != recordSet.end()) {
                break;
            }
            recordSet.insert(num);

            sum = 0;
            while (num > 0) {
                sum += ((num%10) * (num%10));
                num = (num - num%10) / 10;
            }
            num = sum;
        }
        retVal = (num == 1)?true:false;

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        int n;
    };
    vector<subject> testData {
        {19}
        , {2}
        , {INT_MAX}
        , {7}
        , {4}
        , {37}
    };
    int numberOfTestCase = testData.size();

    Solution cSolution;
    bool answer = false;
    for (int i=0; i<numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.isHappy(testData[i].n);
        cout << "Output: "<< ((answer==true)?"true":"false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

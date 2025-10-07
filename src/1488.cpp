#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> avoidFlood(vector<int>& rains) {
        vector<int> retVal;

        int rainsSize = rains.size();
        retVal.resize(rainsSize, 1);

        set<int> st;
        unordered_map<int, int> mp;
        for (int i = 0; i < rainsSize; ++i) {
            if (rains[i] == 0) {
                st.insert(i);
                continue;
            }

            retVal[i] = -1;
            if (mp.count(rains[i])) {
                auto it = st.lower_bound(mp[rains[i]]);
                if (it == st.end()) {
                    retVal = {};
                    break;
                }
                retVal[*it] = rains[i];
                st.erase(it);
            }
            mp[rains[i]] = i;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> rains;
    };
    vector<subject> testData{{{1, 2, 3, 4}}, {{1, 2, 0, 0, 2, 1}}, {{1, 2, 0, 1, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: rains = [1,2,3,4]
     *  Output: [-1,-1,-1,-1]
     *
     *  Input: rains = [1,2,0,0,2,1]
     *  Output: [-1,-1,2,1,-1,-1]
     *
     *  Input: rains = [1,2,0,1,2]
     *  Output: []
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: rains = [";
        for (long unsigned int j = 0; j < testData[i].rains.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].rains[j];
        }
        cout << "]\n";

        answer = cSolution.avoidFlood(testData[i].rains);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

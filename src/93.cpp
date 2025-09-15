#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    void dfs(const string& s, int step, int index, vector<string>& path, vector<string>& result) {
        int sSize = s.size();
        if (step == 4) {
            if (index == sSize) {
                string ip = path[0] + "." + path[1] + "." + path[2] + "." + path[3];
                result.emplace_back(ip);
            }
            return;
        }

        int remaining = sSize - index;
        if ((remaining < (4 - step)) || (remaining > (4 - step) * 3)) {
            return;
        }

        for (int length = 1; length <= 3; ++length) {
            if (index + length > sSize) {
                break;
            }

            string segment = s.substr(index, length);
            if (((segment[0] == '0') && (segment.size() > 1)) || (stoi(segment) > 255)) {
                continue;
            }

            path.push_back(segment);
            dfs(s, step + 1, index + length, path, result);
            path.pop_back();
        }
    }

   public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> retVal;

        int sSize = s.size();
        if ((sSize >= 4) && (sSize <= 12)) {
            vector<string> path;
            dfs(s, 0, 0, path, retVal);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"25525511135"}, {"0000"}, {"101023"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "25525511135"
     *  Output: ["255.255.11.135","255.255.111.35"]
     *
     *  Input: s = "0000"
     *  Output: ["0.0.0.0"]
     *
     *  Input: s = "101023"
     *  Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.restoreIpAddresses(testData[i].s);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

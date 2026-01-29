#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/minimum-cost-to-convert-string-ii/solutions/2577877/zi-dian-shu-floyddp-by-endlesscheng-oi2r/
class Solution {
   private:
    struct Node {
        Node* son[26]{};
        int sid = -1;
    };

    Node* root;
    int sid;

    int put(string& s) {
        int retVal = 0;

        Node* o = root;
        for (char b : s) {
            int i = b - 'a';
            if (o->son[i] == nullptr) {
                o->son[i] = new Node();
            }
            o = o->son[i];
        }
        if (o->sid < 0) {
            o->sid = sid++;
        }
        retVal = o->sid;

        return retVal;
    }
    void freeNode(Node* node) {
        if (node == nullptr) {
            return;
        }

        for (int i = 0; i < 26; i++) {
            if (node->son[i] != nullptr) {
                freeNode(node->son[i]);
                node->son[i] = nullptr;
            }
        }

        delete node;
        node = nullptr;
    }

   public:
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed,
                          vector<int>& cost) {
        long long retVal = -1;

        root = new Node();
        sid = 0;

        int costSize = cost.size();

        vector<vector<int>> dis(costSize * 2, vector<int>(costSize * 2, numeric_limits<int>::max() / 2));
        for (int i = 0; i < costSize * 2; i++) {
            dis[i][i] = 0;
        }
        for (int i = 0; i < costSize; i++) {
            int x = put(original[i]);
            int y = put(changed[i]);
            dis[x][y] = min(dis[x][y], cost[i]);
        }

        for (int k = 0; k < sid; k++) {
            for (int i = 0; i < sid; i++) {
                if (dis[i][k] == numeric_limits<int>::max() / 2) {
                    continue;
                }

                for (int j = 0; j < sid; j++) {
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                }
            }
        }

        int sourceSize = source.size();
        vector<long long> dp(sourceSize + 1);
        for (int i = sourceSize - 1; i >= 0; i--) {
            dp[i] = numeric_limits<long long>::max() / 2;
            if (source[i] == target[i]) {
                dp[i] = dp[i + 1];
            }

            Node* p = root;
            Node* q = root;
            for (int j = i; j < sourceSize; j++) {
                p = p->son[source[j] - 'a'];
                q = q->son[target[j] - 'a'];
                if ((p == nullptr) || (q == nullptr)) {
                    break;
                }

                if ((p->sid < 0) || (q->sid < 0)) {
                    continue;
                }

                int d = dis[p->sid][q->sid];
                if (d < numeric_limits<int>::max() / 2) {
                    dp[i] = min(dp[i], dis[p->sid][q->sid] + dp[j + 1]);
                }
            }
        }
        if (dp[0] < numeric_limits<long long>::max() / 2) {
            retVal = dp[0];
        }

        //
        freeNode(root);
        root = nullptr;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string source;
        string target;
        vector<string> original;
        vector<string> changed;
        vector<int> cost;
    };
    vector<subject> testData{
        {"abcd", "acbe", {"a", "b", "c", "c", "e", "d"}, {"b", "c", "b", "e", "b", "e"}, {2, 5, 5, 1, 2, 20}},
        {"abcdefgh", "acdeeghh", {"bcd", "fgh", "thh"}, {"cde", "thh", "ghh"}, {1, 3, 5}},
        {"abcdefgh", "addddddd", {"bcd", "defgh"}, {"ddd", "ddddd"}, {100, 1578}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input:
     *  source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"],
     *  changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
     *  Output: 28
     *
     *  Input:
     *  source = "abcdefgh", target = "acdeeghh", original = ["bcd","fgh","thh"],
     *  changed = ["cde","thh","ghh"], cost = [1,3,5]
     *  Output: 9
     *
     *  Input:
     *  source = "abcdefgh", target = "addddddd", original = ["bcd","defgh"],
     *  changed = ["ddd","ddddd"], cost = [100,1578]
     *  Output: -1
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: source = \"" << testData[i].source << "\", target = \"" << testData[i].target << "\"";
        cout << ", original = [";
        for (long unsigned int j = 0; j < testData[i].original.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].original[j] << "\"";
        }
        cout << "], changed = [";
        for (long unsigned int j = 0; j < testData[i].changed.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].changed[j] << "\"";
        }
        cout << "], cost = [";
        for (long unsigned int j = 0; j < testData[i].cost.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].cost[j];
        }
        cout << "]\n";

        answer = cSolution.minimumCost(testData[i].source, testData[i].target, testData[i].original,
                                       testData[i].changed, testData[i].cost);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

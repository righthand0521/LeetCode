#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/implement-trie-prefix-tree/solutions/721110/gong-shui-san-xie-yi-ti-shuang-jie-er-we-esm9/
#define MAX_CHAR (26)  // word and prefix consist only of lowercase English letters.
class Trie {
   private:
    Trie* child[MAX_CHAR];
    bool isEnd;

   public:
    Trie() {
        for (int i = 0; i < MAX_CHAR; ++i) {
            child[i] = nullptr;
        }
        isEnd = false;
    }
    ~Trie() {
        for (int i = 0; i < MAX_CHAR; ++i) {
            if (child[i] != nullptr) {
                delete child[i];
            }
        }
    }
    void insert(string word) {
        Trie* root = this;
        for (char x : word) {
            int cur = x - 'a';
            if (root->child[cur] == nullptr) {
                root->child[cur] = new Trie();
            }
            root = root->child[cur];
        }
        root->isEnd = true;
    }
    bool search(string word) {
        bool retVal = false;

        Trie* root = this;
        for (char x : word) {
            int cur = x - 'a';
            if (root->child[cur] == nullptr) {
                return retVal;
            }
            root = root->child[cur];
        }
        retVal = root->isEnd;

        return retVal;
    }
    bool startsWith(string prefix) {
        bool retVal = false;

        Trie* root = this;
        for (char x : prefix) {
            int cur = x - 'a';
            if (root->child[cur] == nullptr) {
                return retVal;
            }
            root = root->child[cur];
        }
        retVal = true;

        return retVal;
    }
};
/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

int main(int argc, char** argv) {
    struct subject {
        vector<string> methods;
        vector<string> value;
    };
    vector<subject> testData{{{"Trie", "insert", "search", "search", "startsWith", "insert", "search"},
                              {"", "apple", "apple", "app", "app", "app", "app"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
     *  [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
     *  Output
     *  [null, null, true, false, true, null, true]
     */

    Trie cSolution;
    bool retBool;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input\n[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << ((j == 0) ? "" : ", ") << "\"" << testData[i].methods[j] << "\"";
        }
        cout << "]\n[";
        for (long unsigned int j = 0; j < testData[i].value.size(); ++j) {
            cout << ((j == 0) ? "" : ", ") << "[\"" << testData[i].value[j] << "\"]";
        }
        cout << "]\n";

        cout << "Output: \n[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("Trie") == 0) {
                // cSolution.Trie();
                cout << ((j == 0) ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("insert") == 0) {
                cSolution.insert(testData[i].value[j]);
                cout << ((j == 0) ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("search") == 0) {
                retBool = cSolution.search(testData[i].value[j]);
                cout << ((j == 0) ? "" : ", ") << ((retBool == true) ? "true" : "false");
            } else if (testData[i].methods[j].compare("startsWith") == 0) {
                retBool = cSolution.startsWith(testData[i].value[j]);
                cout << ((j == 0) ? "" : ", ") << ((retBool == true) ? "true" : "false");
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/design-add-and-search-words-data-structure/solutions/1054681/fu-xue-ming-zhu-qian-zhui-shu-xiang-xi-r-rty2/
#define MAX_CHAR (26)  // word in addWord consists of lowercase English letters.
class TrieNode {
   public:
    vector<TrieNode*> child;
    bool isWord;
    TrieNode() : child(MAX_CHAR, nullptr), isWord(false){};
    ~TrieNode() {
        for (auto c : child) {
            delete c;
        }
    }
};
class WordDictionary {
   private:
    TrieNode* root;

   public:
    WordDictionary() {
        //
        root = new TrieNode();
    }
    ~WordDictionary() {
        //
        delete root;
    }
    void addWord(string word) {
        TrieNode* p = root;
        for (char c : word) {
            int i = c - 'a';
            if (!p->child[i]) p->child[i] = new TrieNode();
            p = p->child[i];
        }
        p->isWord = true;
    }
    bool search(string word) {
        bool retVal = match(word, root, 0);

        return retVal;
    }
    bool match(string& word, TrieNode* pRoot, int start) {
        bool retVal = false;

        if (pRoot == nullptr) {
            return retVal;
        }

        if (start == (int)word.size()) {
            retVal = pRoot->isWord;
            return retVal;
        }

        char c = word[start];
        if (c != '.') {
            retVal = match(word, pRoot->child[c - 'a'], start + 1);
            return retVal;
        }
        for (const auto& child : pRoot->child) {
            if (match(word, child, start + 1) == true) {
                retVal = true;
                break;
            }
        }

        return retVal;
    }
};
/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */

int main(int argc, char** argv) {
    struct subject {
        vector<string> methods;
        vector<string> value;
    };
    vector<subject> testData{
        {{"WordDictionary", "addWord", "addWord", "addWord", "search", "search", "search", "search"},
         {"", "bad", "dad", "mad", "pad", "bad", ".ad", "b.."}}};
    int numberOfTestCase = testData.size();
    /* Example:
     *  Input
     *  ["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
     *  [[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
     *  Output
     *  [null,null,null,null,false,true,true,true]
     */

    WordDictionary cSolution;
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
            if (testData[i].methods[j].compare("WordDictionary") == 0) {
                // cSolution.WordDictionary();
                cout << ((j == 0) ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("addWord") == 0) {
                cSolution.addWord(testData[i].value[j]);
                cout << ((j == 0) ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("search") == 0) {
                retBool = cSolution.search(testData[i].value[j]);
                cout << ((j == 0) ? "" : ", ") << ((retBool == true) ? "true" : "false");
            }
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

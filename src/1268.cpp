#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

struct Trie {
    unordered_map<char, Trie*> child;
    priority_queue<string> words;
};
class Solution {
   private:
    void addWord(Trie* root, const string& product) {
        Trie* pCurrent = root;
        for (const char& c : product) {
            if (pCurrent->child.count(c) == 0) {
                pCurrent->child[c] = new Trie();
            }
            pCurrent = pCurrent->child[c];
            pCurrent->words.push(product);
            if (pCurrent->words.size() > 3) {
                pCurrent->words.pop();
            }
        }
    }
    void freeAll(Trie* pFree) {
        if (pFree == nullptr) {
            return;
        }

        for (int i = 0; i <= 26; i++) {
            freeAll(pFree->child['a' + i]);
        }

        delete pFree;
        pFree = nullptr;
    }

   public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        vector<vector<string>> retVal;

        //
        Trie* pRoot = new Trie();
        for (const string& product : products) {
            addWord(pRoot, product);
        }

        //
        Trie* pCurrent = pRoot;
        bool flag = false;
        for (const char& c : searchWord) {
            if ((flag == true) || (pCurrent->child.count(c) == 0)) {
                retVal.emplace_back();
                flag = true;
            } else {
                pCurrent = pCurrent->child[c];
                vector<string> selects;
                while (pCurrent->words.empty() == false) {
                    selects.push_back(pCurrent->words.top());
                    pCurrent->words.pop();
                }
                reverse(selects.begin(), selects.end());
                retVal.push_back(move(selects));
            }
        }

        //
        freeAll(pRoot);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> products;
        string searchWord;
    };
    vector<subject> testData{{{"mobile", "mouse", "moneypot", "monitor", "mousepad"}, "mouse"}, {{"havana"}, "havana"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
     *  Output: [["mobile","moneypot","monitor"],["mobile","moneypot","monitor"],["mouse","mousepad"],
     *  ["mouse","mousepad"],["mouse","mousepad"]]
     *
     *  Input: products = ["havana"], searchWord = "havana"
     *  Output: [["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
     */

    Solution cSolution;
    vector<vector<string>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: products = [";
        for (long unsigned int j = 0; j < testData[i].products.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "\"" << testData[i].products[j] << "\"";
        }
        cout << "], searchWord = \"" << testData[i].searchWord << "\"\n";

        answer = cSolution.suggestedProducts(testData[i].products, testData[i].searchWord);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << "\"" << answer[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

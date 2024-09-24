#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class TrieNode {
   public:
    TrieNode* children[10];  // Each node has up to 10 possible children (digits 0-9)

    TrieNode() {
        for (int i = 0; i < 10; ++i) {
            children[i] = nullptr;
        }
    }
    ~TrieNode() {
        for (int i = 0; i < 10; ++i) {
            delete children[i];
        }
    }
};
class Trie {
   public:
    TrieNode* root;

    Trie() {
        //
        root = new TrieNode();
    }
    ~Trie() {
        //
        delete root;
    }

    void insert(int num) {
        TrieNode* node = root;

        string numStr = to_string(num);
        for (char digit : numStr) {
            int idx = digit - '0';
            if (node->children[idx] == nullptr) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
        }
    }
    int findLongestPrefix(int num) {
        int retVal = 0;

        TrieNode* node = root;
        string numStr = to_string(num);
        for (char digit : numStr) {
            int idx = digit - '0';
            if (node->children[idx]) {
                // Increase length if the current digit matches
                retVal++;
                node = node->children[idx];
            } else {
                // Stop if no match for the current digit
                break;
            }
        }

        return retVal;
    }
};
class Solution {
   public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        int retVal = 0;

        Trie trie;

        // Step 1: Insert all numbers from arr1 into the Trie
        for (int num : arr1) {
            trie.insert(num);
        }

        // Step 2: Find the longest prefix match for each number in arr2
        for (int num : arr2) {
            int len = trie.findLongestPrefix(num);
            retVal = max(retVal, len);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> arr1;
        vector<int> arr2;
    };
    vector<subject> testData{{{1, 10, 100}, {1000}}, {{1, 2, 3}, {4, 4, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: arr1 = [1,10,100], arr2 = [1000]
     *  Output: 3
     *
     *  Input: arr1 = [1,2,3], arr2 = [4,4,4]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: arr1 = [";
        for (long unsigned int j = 0; j < testData[i].arr1.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].arr1[j];
        }
        cout << "], arr2 = [";
        for (long unsigned int j = 0; j < testData[i].arr2.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].arr2[j];
        }
        cout << "]\n";

        answer = cSolution.longestCommonPrefix(testData[i].arr1, testData[i].arr2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

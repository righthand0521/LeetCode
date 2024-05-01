#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    struct TrieNode {
        string word;
        unordered_map<char, TrieNode*> children;
        TrieNode() { this->word = ""; }
    };
    void insertTrie(TrieNode* root, const string& word) {
        TrieNode* node = root;
        for (auto c : word) {
            if (node->children.count(c) == 0) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->word = word;
    }

   public:
    bool dfs(vector<vector<char>>& board, int row, int col, TrieNode* root, set<string>& answer) {
        bool retVal = false;

        char ch = board[row][col];
        if (root->children.count(ch) == 0) {
            return retVal;
        }

        root = root->children[ch];
        if (root->word.size() > 0) {
            answer.insert(root->word);
        }

        board[row][col] = '#';
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int boardSize = board.size();
        int boardColSize = board[0].size();
        for (int i = 0; i < 4; ++i) {
            int x = row + dirs[i][0];
            int y = col + dirs[i][1];
            if ((x >= 0) && (x < boardSize) && (y >= 0) && (y < boardColSize)) {
                if (board[x][y] != '#') {
                    dfs(board, x, y, root, answer);
                }
            }
        }
        board[row][col] = ch;
        retVal = true;

        return retVal;
    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> retVal;

        TrieNode* root = new TrieNode();
        for (auto& word : words) {
            insertTrie(root, word);
        }

        set<string> answer;
        int boardSize = board.size();
        int boardColSize = board[0].size();
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardColSize; ++col) {
                dfs(board, row, col, root, answer);
            }
        }
        for (auto& word : answer) {
            retVal.emplace_back(word);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<char>> board;
        vector<string> words;
    };
    vector<subject> testData{{{{'o', 'a', 'a', 'n'}, {'e', 't', 'a', 'e'}, {'i', 'h', 'k', 'r'}, {'i', 'f', 'l', 'v'}},
                              {"oath", "pea", "eat", "rain"}},
                             {{{'a', 'b'}, {'c', 'd'}}, {"abcb"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]],
     *          words = ["oath","pea","eat","rain"]
     *  Output: ["eat","oath"]
     *
     *  Input: board = [["a","b"],["c","d"]], words = ["abcb"]
     *  Output: []
     */

    Solution cSolution;
    vector<string> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: board = [";
        for (long unsigned int j = 0; j < testData[i].board.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].board[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << "\"" << testData[i].board[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "], words = [";
        for (long unsigned int j = 0; j < testData[i].words.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].words[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.findWords(testData[i].board, testData[i].words);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << answer[j] << "\"";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

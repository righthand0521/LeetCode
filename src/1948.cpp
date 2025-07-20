#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct Trie {
    string serial;                          // current node structure's serialized representation
    unordered_map<string, Trie*> children;  // current node's child nodes
};
class Solution {
   private:
    // post-order traversal based on depth-first search, calculate the serialized representation of each node structure
    void construct(Trie* node, unordered_map<string, int>& frequency) {
        // if it is a leaf node, then the serialization is represented as an empty string, and no operation is required.
        if (node->children.empty()) {
            return;
        }

        // if it is not a leaf node,
        // the serialization representation of the child node structure needs to be calculated first.
        vector<string> v;
        for (const auto& [folder, child] : node->children) {
            construct(child, frequency);
            v.push_back(folder + "(" + child->serial + ")");
        }

        // to prevent issues with order, sorting is needed
        sort(v.begin(), v.end());
        for (string& s : v) {
            node->serial += move(s);
        }

        // add to hash table
        ++frequency[node->serial];
    };
    void operate(Trie* node, unordered_map<string, int>& frequency, vector<string>& path,
                 vector<vector<string>>& retVal) {
        // if the serialization appears more than once in the hash table, it needs to be deleted.
        if (frequency[node->serial] > 1) {
            return;
        }

        // otherwise add the path to the answer
        if (path.empty() == false) {
            retVal.push_back(path);
        }

        for (const auto& [folder, child] : node->children) {
            path.push_back(folder);
            operate(child, frequency, path, retVal);
            path.pop_back();
        }
    };

   public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        vector<vector<string>> retVal;

        // root node
        Trie* root = new Trie();
        for (const vector<string>& path : paths) {
            Trie* current = root;
            for (const string& node : path) {
                if (!current->children.count(node)) {
                    current->children[node] = new Trie();
                }
                current = current->children[node];
            }
        }

        // hash table records the occurrence times of each serialized representation
        unordered_map<string, int> frequency;
        construct(root, frequency);

        // record the path from the root node to the current node.
        vector<string> path;
        operate(root, frequency, path, retVal);

        // free memory
        for (const auto& [folder, child] : root->children) {
            delete child;
        }
        delete root;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<string>> paths;
    };
    vector<subject> testData{
        {{{"a"}, {"c"}, {"d"}, {"a", "b"}, {"c", "b"}, {"d", "a"}}},
        {{{"a"}, {"c"}, {"a", "b"}, {"c", "b"}, {"a", "b", "x"}, {"a", "b", "x", "y"}, {"w"}, {"w", "y"}}},
        {{{"a", "b"}, {"c", "d"}, {"c"}, {"a"}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: paths = [["a"],["c"],["d"],["a","b"],["c","b"],["d","a"]]
     *  Output: [["d"],["d","a"]]
     *
     *  Input: paths = [["a"],["c"],["a","b"],["c","b"],["a","b","x"],["a","b","x","y"],["w"],["w","y"]]
     *  Output: [["c"],["c","b"],["a"],["a","b"]]
     *
     *  Input: paths = [["a","b"],["c","d"],["c"],["a"]]
     *  Output: [["c"],["c","d"],["a"],["a","b"]]
     */

    Solution cSolution;
    vector<vector<string>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: paths = [";
        for (long unsigned int j = 0; j < testData[i].paths.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].paths[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << "\"" << testData[i].paths[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.deleteDuplicateFolder(testData[i].paths);
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

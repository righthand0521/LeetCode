#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

#include "tree.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
   public:
    // Encodes a tree to a single string.
    void rserialize(TreeNode *root, string &retVal) {
        if (root == nullptr) {
            retVal += "None,";
            return;
        }
        retVal += to_string(root->val) + ",";
        rserialize(root->left, retVal);
        rserialize(root->right, retVal);
    }
    string serialize(TreeNode *root) {
        string retVal;

        rserialize(root, retVal);

        return retVal;
    }

    // Decodes your encoded data to tree.
    TreeNode *rdeserialize(list<string> &dataArray) {
        TreeNode *pRoot = nullptr;

        if (dataArray.front() == "None") {
            dataArray.erase(dataArray.begin());
            return pRoot;
        }
        pRoot = new TreeNode(stoi(dataArray.front()));
        dataArray.erase(dataArray.begin());
        pRoot->left = rdeserialize(dataArray);
        pRoot->right = rdeserialize(dataArray);

        return pRoot;
    }
    TreeNode *deserialize(string data) {
        TreeNode *pRetVal = nullptr;

        list<string> dataArray;
        string str;
        for (auto &ch : data) {
            if (ch == ',') {
                dataArray.push_back(str);
                str.clear();
            } else {
                str.push_back(ch);
            }
        }
        if (str.empty() == false) {
            dataArray.push_back(str);
            str.clear();
        }
        pRetVal = rdeserialize(dataArray);

        return pRetVal;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

int main(int argc, char **argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,2,3,null,null,4,5]
     *  Output: [1,2,3,null,null,4,5]
     *
     *  Input: root = []
     *  Output: []
     */

    // Solution cSolution;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "\n";
    }

    return EXIT_SUCCESS;
}

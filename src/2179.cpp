#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class FenwickTree {
   private:
    vector<int> tree;

   public:
    FenwickTree(int size) : tree(size + 1, 0) {}
    void update(int index, int delta) {
        index++;
        int treeSize = tree.size();
        while (index < treeSize) {
            tree[index] += delta;
            index += (index & -index);
        }
    }
    int query(int index) {
        int retVal = 0;

        index++;
        while (index > 0) {
            retVal += tree[index];
            index -= (index & -index);
        }

        return retVal;
    }
};

class Solution {
   public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        long long retVal = 0;

        int nums1Size = nums1.size();

        vector<int> pos2(nums1Size);
        for (int i = 0; i < nums1Size; i++) {
            pos2[nums2[i]] = i;
        }

        vector<int> reversedIndexMapping(nums1Size);
        for (int i = 0; i < nums1Size; i++) {
            reversedIndexMapping[pos2[nums1[i]]] = i;
        }

        FenwickTree tree(nums1Size);

        for (int value = 0; value < nums1Size; value++) {
            int pos = reversedIndexMapping[value];
            int left = tree.query(pos);
            tree.update(pos, 1);

            int right = (nums1Size - 1 - pos) - (value - left);
            retVal += ((long long)left * right);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums1;
        vector<int> nums2;
    };
    vector<subject> testData{{{2, 0, 1, 3}, {0, 1, 2, 3}}, {{4, 0, 1, 3, 2}, {4, 1, 0, 2, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums1 = [2,0,1,3], nums2 = [0,1,2,3]
     *  Output: 1
     *
     *  Input: nums1 = [4,0,1,3,2], nums2 = [4,1,0,2,3]
     *  Output: 4
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums1 = [";
        for (long unsigned int j = 0; j < testData[i].nums1.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums1[j];
        }
        cout << "], nums2 = [";
        for (long unsigned int j = 0; j < testData[i].nums2.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums2[j];
        }
        cout << "]\n";

        answer = cSolution.goodTriplets(testData[i].nums1, testData[i].nums2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}

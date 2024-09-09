#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#include "list.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
   public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        vector<vector<int>> retVal(m, vector<int>(n, -1));

        vector<vector<int>> movement = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int movementIndex = 0;
        int x = 0;
        int y = 0;
        ListNode* pCurrent = head;
        while (pCurrent != nullptr) {
            retVal[x][y] = pCurrent->val;

            x += movement[movementIndex][0];
            y += movement[movementIndex][1];
            // 0 <= Node.val <= 1000
            if ((x < 0) || (y < 0) || (x >= m) || (y >= n) || (retVal[x][y] != -1)) {
                x -= movement[movementIndex][0];
                y -= movement[movementIndex][1];
                movementIndex = (movementIndex + 1) % 4;
                x += movement[movementIndex][0];
                y += movement[movementIndex][1];
            }

            pCurrent = pCurrent->next;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int m;
        int n;
        vector<int> head;
    };
    vector<subject> testData{{3, 5, {3, 0, 2, 6, 8, 1, 7, 9, 4, 2, 5, 5, 0}}, {1, 4, {0, 1, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: m = 3, n = 5, head = [3,0,2,6,8,1,7,9,4,2,5,5,0]
     *  Output: [[3,0,2,6,8],[5,0,-1,-1,1],[5,2,4,9,7]]
     *
     *  Input: m = 1, n = 4, head = [0,1,2]
     *  Output: [[0,1,2,-1]]
     */

    Solution cSolution;
    ListNode* pHead = nullptr;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].head);
        cout << "Input: m = " << testData[i].m << ", n = " << testData[i].n << ", head = [";
        printList(pHead);
        cout << "]\n";

        answer = cSolution.spiralMatrix(testData[i].m, testData[i].n, pHead);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}

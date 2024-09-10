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
   private:
    int gcd(int a, int b) {
        int retVal = 1;

        while (b != 0) {
            int tmp = a;
            a = b;
            b = tmp % b;
        }
        retVal = a;

        return retVal;
    }

   public:
    ListNode *insertGreatestCommonDivisors(ListNode *head) {
        ListNode *pRetVal = head;

        if ((pRetVal == nullptr) || (pRetVal->next == nullptr)) {
            return pRetVal;
        }

        ListNode *pNode1 = pRetVal;
        ListNode *pNode2 = pRetVal->next;
        while (pNode2 != nullptr) {
            int gcdValue = gcd(pNode1->val, pNode2->val);

            ListNode *gcdNode = new ListNode(gcdValue);
            pNode1->next = gcdNode;
            gcdNode->next = pNode2;

            pNode1 = pNode2;
            pNode2 = pNode2->next;
        }

        return pRetVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        vector<int> node;
    };
    vector<subject> testData{{{18, 6, 10, 3}}, {{7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [18,6,10,3]
     *  Output: [18,6,6,2,10,1,3]
     *
     *  Input: head = [7]
     *  Output: [7]
     */

    Solution cSolution;
    ListNode *pHead = nullptr;
    ListNode *pAnswer = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        pAnswer = cSolution.insertGreatestCommonDivisors(pHead);
        cout << "Output: [";
        printList(pAnswer);
        cout << "]\n";

        cout << "\n";

        freeListNode(pAnswer);
        pAnswer = nullptr;
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}

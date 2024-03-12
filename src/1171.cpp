#include <algorithm>
#include <iostream>
#include <unordered_map>
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
    ListNode* removeZeroSumSublists(ListNode* head) {
        ListNode* pRetVal = nullptr;

        pRetVal = new ListNode(0);
        pRetVal->next = head;

        unordered_map<int, ListNode*> hashTable;
        hashTable[0] = pRetVal;

        ListNode* pCurrent = nullptr;
        int prefixSum = 0;
        for (pCurrent = pRetVal; pCurrent; pCurrent = pCurrent->next) {
            prefixSum += pCurrent->val;
            hashTable[prefixSum] = pCurrent;
        }

        prefixSum = 0;
        for (pCurrent = pRetVal; pCurrent; pCurrent = pCurrent->next) {
            prefixSum += pCurrent->val;
            /* valgrind -s --tool=memcheck --leak-check=full --max-stackframe=5000000 1171.cpp
                ==19012== HEAP SUMMARY:
                ==19012==     in use at exit: 96 bytes in 6 blocks
                ==19012==   total heap usage: 43 allocs, 37 frees, 74,832 bytes allocated
                ==19012==
                ==19012== 96 (32 direct, 64 indirect) bytes in 2 blocks are definitely lost in loss record 2 of 2
                ==19012==    at 0x4849013: operator new(unsigned long) (in
               /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
                ==19012==    by 0x109630: main (in /root/WorkingSpace/1171-cpp)
                ==19012==
                ==19012== LEAK SUMMARY:
                ==19012==    definitely lost: 32 bytes in 2 blocks
                ==19012==    indirectly lost: 64 bytes in 4 blocks
                ==19012==      possibly lost: 0 bytes in 0 blocks
                ==19012==    still reachable: 0 bytes in 0 blocks
                ==19012==         suppressed: 0 bytes in 0 blocks
                ==19012==
                ==19012== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
            */
            pCurrent->next = hashTable[prefixSum]->next;
        }

        pCurrent = pRetVal;
        pRetVal = pRetVal->next;
        delete pCurrent;

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> node;
    };
    vector<subject> testData{{{1, 2, -3, 3, 1}}, {{1, 2, 3, -3, 4}}, {{1, 2, 3, -3, -2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,2,-3,3,1]
     *  Output: [3,1]
     *
     *  Input: head = [1,2,3,-3,4]
     *  Output: [1,2,4]
     *
     *  Input: head = [1,2,3,-3,-2]
     *  Output: [1]
     */

    Solution cSolution;
    ListNode* pAnswer = nullptr;
    ListNode* pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        pAnswer = cSolution.removeZeroSumSublists(pHead);
        cout << "Output: [";
        printList(pAnswer);
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
        freeListNode(pAnswer);
        pAnswer = nullptr;
    }

    return EXIT_SUCCESS;
}

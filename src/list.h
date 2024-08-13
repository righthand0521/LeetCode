#ifndef LIST_H
#define LIST_H

#if (CPP)
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(NULL) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* buildList(vector<int>& nums) {
    ListNode* pHead = nullptr;

    int numsSize = nums.size();
    if (numsSize == 0) {
        return pHead;
    }
    pHead = new ListNode(nums[0]);

    ListNode* pCurrent = pHead;
    for (int i = 1; i < numsSize; ++i) {
        ListNode* node = new ListNode(nums[i]);
        pCurrent->next = node;
        pCurrent = pCurrent->next;
    }

    return pHead;
}
void freeListNode(ListNode* pHead) {
    ListNode* pCurrent = pHead;
    ListNode* pFree = nullptr;
    while (pCurrent != nullptr) {
        pFree = pCurrent;
        pCurrent = pCurrent->next;
        delete pFree;
    }
}
void printList(ListNode* pHead) {
    ListNode* pCurrent = pHead;
    while (pCurrent != nullptr) {
        cout << pCurrent->val << (pCurrent->next == nullptr ? "" : ",");
        pCurrent = pCurrent->next;
    }
}

ListNode* addValueToEndListNode(ListNode* pHead, int value) {
    ListNode* pNew = new ListNode(value);
    if (pNew == nullptr) {
        return pHead;
    }

    if (pHead == nullptr) {
        pHead = pNew;
        return pHead;
    }

    ListNode* pCurrent = pHead;
    while (pCurrent->next != nullptr) {
        pCurrent = pCurrent->next;
    }
    pCurrent->next = pNew;

    return pHead;
}
ListNode* mergeListNode(ListNode* pList1, ListNode* pList2) {
    ListNode* pRetVal = pList1;

    ListNode* pCurrent = pList1;
    while (pCurrent->next != nullptr) {
        pCurrent = pCurrent->next;
    }
    pCurrent->next = pList2;

    return pRetVal;
}
#else
struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* buildList(int* nums, int numsSize) {
    struct ListNode* pHead = NULL;

    if (numsSize == 0) {
        return pHead;
    }
    pHead = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pHead == NULL) {
        perror("malloc");
        return pHead;
    }
    pHead->val = nums[0];
    pHead->next = NULL;

    struct ListNode* pCurrent = pHead;
    struct ListNode* pNew;
    int i;
    for (i = 1; i < numsSize; ++i) {
        pNew = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (pNew == NULL) {
            perror("malloc");
            return pHead;
        }
        pNew->val = nums[i];
        pNew->next = NULL;
        pCurrent->next = pNew;
        pCurrent = pCurrent->next;
    }

    return pHead;
}
void freeListNode(struct ListNode* pHead) {
    struct ListNode* pCurrent = pHead;
    struct ListNode* pFree = NULL;
    while (pCurrent != NULL) {
        pFree = pCurrent;
        pCurrent = pCurrent->next;
        free(pFree);
        pFree = NULL;
    }
}
void printList(struct ListNode* pHead) {
    struct ListNode* pCurrent = pHead;
    while (pCurrent != NULL) {
        printf("%d%s", pCurrent->val, (pCurrent->next == NULL) ? "" : ",");
        pCurrent = pCurrent->next;
    }
}

struct ListNode* createListNode(int value) {
    struct ListNode* pNew = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pNew == NULL) {
        perror("malloc");
        return pNew;
    }
    pNew->val = value;
    pNew->next = NULL;

    return pNew;
}
struct ListNode* addValueToEndListNode(struct ListNode* pHead, int value) {
    struct ListNode* pNew = createListNode(value);
    if (pNew == NULL) {
        return pHead;
    }

    if (pHead == NULL) {
        pHead = pNew;
        return pHead;
    }

    struct ListNode* pCurrent = pHead;
    while (pCurrent->next != NULL) {
        pCurrent = pCurrent->next;
    }
    pCurrent->next = pNew;

    return pHead;
}
struct ListNode* mergeListNode(struct ListNode* pList1, struct ListNode* pList2) {
    struct ListNode* pRetVal = pList1;

    struct ListNode* pCurrent = pList1;
    while (pCurrent->next != NULL) {
        pCurrent = pCurrent->next;
    }
    pCurrent->next = pList2;

    return pRetVal;
}
#endif

#define LIST_VALID_CYCLE_INDEX (-1)
#if (CPP)
ListNode* addListNodeCycle(ListNode* pHead, int pos) {
    ListNode* pRetVal = pHead;

    if (pos == LIST_VALID_CYCLE_INDEX) {
        return pRetVal;
    }

    ListNode* pCurrent = pHead;
    ListNode* pPos = NULL;
    int steps = 0;
    while (pCurrent->next != NULL) {
        if (steps == pos) {
            pPos = pCurrent;
        }
        pCurrent = pCurrent->next;
        steps++;
    }
    pCurrent->next = pPos;

    return pRetVal;
}
ListNode* removeListNodeCycle(ListNode* pHead, int pos) {
    ListNode* pRetVal = pHead;

    if (pos == LIST_VALID_CYCLE_INDEX) {
        return pRetVal;
    }

    ListNode* pCurrent = pHead;
    ListNode* pPos = NULL;
    int steps = 0;
    while (pCurrent->next != pPos) {
        if (steps == pos) {
            pPos = pCurrent;
        }
        pCurrent = pCurrent->next;
        steps++;
    }
    pCurrent->next = NULL;

    return pRetVal;
}
#else
struct ListNode* addListNodeCycle(struct ListNode* pHead, int pos) {
    struct ListNode* pRetVal = pHead;

    if (pos == LIST_VALID_CYCLE_INDEX) {
        return pRetVal;
    }

    struct ListNode* pCurrent = pHead;
    struct ListNode* pPos = NULL;
    int steps = 0;
    while (pCurrent->next != NULL) {
        if (steps == pos) {
            pPos = pCurrent;
        }
        pCurrent = pCurrent->next;
        steps++;
    }
    pCurrent->next = pPos;

    return pRetVal;
}
struct ListNode* removeListNodeCycle(struct ListNode* pHead, int pos) {
    struct ListNode* pRetVal = pHead;

    if (pos == LIST_VALID_CYCLE_INDEX) {
        return pRetVal;
    }

    struct ListNode* pCurrent = pHead;
    struct ListNode* pPos = NULL;
    int steps = 0;
    while (pCurrent->next != pPos) {
        if (steps == pos) {
            pPos = pCurrent;
        }
        pCurrent = pCurrent->next;
        steps++;
    }
    pCurrent->next = NULL;

    return pRetVal;
}
#endif

#endif  // LIST_H

#ifndef NODE_H
#define NODE_H

struct Node {
    int val;
    struct Node* next;
    struct Node* random;
};

#endif  // NODE_H

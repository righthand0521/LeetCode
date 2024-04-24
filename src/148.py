import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop

from list import ListNode, ListNodeCommon


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def merge(self, head: Optional[ListNode], tail: Optional[ListNode]) -> Optional[ListNode]:
        retVal = None

        dummyHead = ListNode(0)

        pNext = dummyHead
        pHead = head
        pTail = tail
        while pHead and pTail:
            if pHead.val <= pTail.val:
                pNext.next = pHead
                pHead = pHead.next
            else:
                pNext.next = pTail
                pTail = pTail.next
            pNext = pNext.next
        if pHead:
            pNext.next = pHead
        elif pTail:
            pNext.next = pTail

        retVal = dummyHead.next

        return retVal

    def sortFunc(self, head: Optional[ListNode], tail: Optional[ListNode]) -> Optional[ListNode]:
        retVal = head

        if head is None:
            return retVal
        elif head.next == tail:
            head.next = None
            return retVal

        slow = head
        fast = head
        while fast != tail:
            slow = slow.next
            fast = fast.next
            if fast != tail:
                fast = fast.next
        mid = slow
        retVal = self.merge(self.sortFunc(head, mid), self.sortFunc(mid, tail))

        return retVal

    def sortList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        retVal = None

        retVal = self.sortFunc(head, None)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head in [[4, 2, 1, 3], [-1, 5, 3, 4, 0], []]:
            # /* Example
            #  *  Input: head = [4,2,1,3]
            #  *  Output: [1,2,3,4]
            #  *
            #  *  Input: head = [-1,5,3,4,0]
            #  *  Output: [-1,0,3,4,5]
            #  *
            #  *  Input: head = []
            #  *  Output: []
            #  */
            logging.info("Input: head = %s", head)
            pHead = ListNode.buildList(head)

            retVal = pSolution.sortList(pHead)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)

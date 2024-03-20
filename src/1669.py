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
    def mergeInBetween(self, list1: ListNode, a: int, b: int, list2: ListNode) -> ListNode:
        retVal = list1

        pPrevious = None
        pNext1 = list1
        for _ in range(a):
            pPrevious = pNext1
            pNext1 = pNext1.next
        pNext2 = pPrevious

        for _ in range(a, b+1):
            pPrevious.next = pNext1.next
            pNext1 = pPrevious.next

        pNext2.next = list2
        while pNext2 != None:
            pPrevious = pNext2
            pNext2 = pNext2.next
        pPrevious.next = pNext1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for l1, a, b, l2 in zip([[0, 1, 2, 3, 4, 5], [0, 1, 2, 3, 4, 5, 6]],
                                [3, 2],
                                [4, 5],
                                [[1000000, 1000001, 1000002], [1000000, 1000001, 1000002, 1000003, 1000004]]):
            # /* Example
            #  *  Input: list1 = [0,1,2,3,4,5], a = 3, b = 4, list2 = [1000000,1000001,1000002]
            #  *  Output: [0,1,2,1000000,1000001,1000002,5]
            #  *
            #  *  Input: list1 = [0,1,2,3,4,5,6], a = 2, b = 5, list2 = [1000000,1000001,1000002,1000003,1000004]
            #  *  Output: [0,1,1000000,1000001,1000002,1000003,1000004,6]
            #  */
            logging.info(
                "Input: l1 = %s, a = %s, b = %s, l2 = %s", l1, a, b, l2)

            pHead1 = ListNode.buildList(l1)
            pHead2 = ListNode.buildList(l2)
            retVal = pSolution.mergeInBetween(pHead1, a, b, pHead2)
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

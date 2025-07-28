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
    def reverseBetween(self, head: Optional[ListNode], left: int, right: int) -> Optional[ListNode]:
        retVal = head

        pTmp = ListNode(-1)
        pTmp.next = head

        pPrevious = pTmp
        for _ in range(left-1):
            pPrevious = pPrevious.next

        pCurrent = pPrevious.next

        for _ in range(right - left):
            pNext = pCurrent.next
            pCurrent.next = pNext.next
            pNext.next = pPrevious.next
            pPrevious.next = pNext

        retVal = pTmp.next

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head, left, right in zip([[1, 2, 3, 4, 5], [5]], [2, 1], [4, 1]):
            # /* Example
            #  *  Input: head = [1,2,3,4,5], left = 2, right = 4
            #  *  Output: [1,4,3,2,5]
            #  *
            #  *  Input: head = [5], left = 1, right = 1
            #  *  Output: [5]
            #  */
            logging.info("Input: head = %s, left = %s, right = %s", head, left, right)

            pHead = ListNode.buildList(head)
            pHead = pSolution.reverseBetween(pHead, left, right)
            logging.info("Output: %s", pHead)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

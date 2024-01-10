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
    def removeElements(self, head: Optional[ListNode], val: int) -> Optional[ListNode]:
        retVal = ListNode(0)

        retVal.next = head

        if head == None:
            retVal = retVal.next
            return retVal

        pPrevious = retVal
        pFree = head
        while pFree != None:
            if pFree.val != val:
                pPrevious = pFree
                pFree = pFree.next
                continue

            pPrevious.next = pFree.next
            pFree.next = None
            pFree = pPrevious.next

        retVal = retVal.next

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head, val in zip([[1, 2, 6, 3, 4, 5, 6], [], [7, 7, 7, 7]], [6, 1, 7]):
            # /* Example
            #  *  Input: head = [1,2,6,3,4,5,6], val = 6
            #  *  Output: [1,2,3,4,5]
            #  *
            #  *  Input: head = [], val = 1
            #  *  Output: []
            #  *
            #  *  Input: head = [7,7,7,7], val = 7
            #  *  Output: []
            #  */
            logging.info("Input: head = %s, val = %s", head, val)

            pHead = ListNode.buildList(head)
            retVal = pSolution.removeElements(pHead, val)
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

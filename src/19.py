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
    def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
        retVal = head

        pRemove = head
        pCurrent = head
        for i in range(n):
            if pCurrent == None:
                break
            pCurrent = pCurrent.next
        if pCurrent == None:
            retVal = pRemove.next
            return retVal

        while pCurrent.next != None:
            pRemove = pRemove.next
            pCurrent = pCurrent.next
        pCurrent = pRemove
        pRemove = pRemove.next
        pCurrent.next = pRemove.next

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head, n in zip([[1, 2, 3, 4, 5], [1], [1, 2]], [2, 1, 1]):
            # /* Example
            #  *  Input: head = [1,2,3,4,5], n = 2
            #  *  Output: [1,2,3,5]
            #  *
            #  *  Input: head = [1], n = 1
            #  *  Output: []
            #  *
            #  *  Input: head = [1,2], n = 1
            #  *  Output: [1]
            #  */
            logging.info("Input: head = %s, n = %s", head, n)

            pHead = ListNode.buildList(head)
            retVal = pSolution.removeNthFromEnd(pHead, n)
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

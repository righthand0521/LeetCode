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
    def rotateRight(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        retVal = head

        if (retVal is None) or (retVal.next is None):
            return retVal

        pCurrent = head
        headSize = 0
        while pCurrent.next != None:
            headSize += 1
            pCurrent = pCurrent.next
        k = headSize - (k % (headSize + 1))

        pCurrent.next = head
        while (k > 0):
            head = head.next
            k -= 1
        pCurrent = head
        head = head.next
        pCurrent.next = None
        retVal = head

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head, k in zip([[1, 2, 3, 4, 5], [0, 1, 2]], [2, 4]):
            # /* Example
            #  *  Input: head = [1,2,3,4,5], k = 2
            #  *  Output: [4,5,1,2,3]
            #  *
            #  *  Input: head = [0,1,2], k = 4
            #  *  Output: [2,0,1]
            #  */
            logging.info("Input: head = %s, k = %s", head, k)

            pHead = ListNode.buildList(head)
            retVal = pSolution.rotateRight(pHead, k)
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

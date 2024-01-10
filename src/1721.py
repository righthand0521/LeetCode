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
    def swapNodes(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        retVal = head

        pCurrent = head
        idx = 0
        while pCurrent != None:
            idx += 1
            if idx >= k:
                break
            pCurrent = pCurrent.next
        pSwapHead = pCurrent

        pCurrent = pCurrent.next
        pSwapTail = head
        while pCurrent != None:
            pCurrent = pCurrent.next
            pSwapTail = pSwapTail.next

        tmp = pSwapHead.val
        pSwapHead.val = pSwapTail.val
        pSwapTail.val = tmp

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head, k in zip([[1, 2, 3, 4, 5], [7, 9, 6, 6, 7, 8, 3, 0, 9, 5]], [2, 5]):
            # /* Example
            #  *  Input: head = [1,2,3,4,5], k = 2
            #  *  Output: [1,4,3,2,5]
            #  *
            #  *  Input: head = [7,9,6,6,7,8,3,0,9,5], k = 5
            #  *  Output: [7,9,6,6,8,7,3,0,9,5]
            #  */
            logging.info("Input: head = %s, k = %s", head, k)

            pHead = ListNode.buildList(head)
            retVal = pSolution.swapNodes(pHead, k)
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

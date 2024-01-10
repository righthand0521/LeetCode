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
    def swapPairs(self, head: Optional[ListNode]) -> Optional[ListNode]:
        retVal = head

        if retVal == None or retVal.next == None:
            return retVal

        retVal = head.next
        p1 = head
        p2 = head.next
        pPrevious = None
        while p2 != None:
            if pPrevious != None:
                pPrevious.next = p2
            p1.next = p2.next
            p2.next = p1

            pPrevious = p1
            p1 = p1.next
            if p1 == None:
                break

            p2 = p1.next

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head in [[1, 2, 3, 4], [], [1], [1, 2, 3, 4, 5]]:
            # /* Example
            #  *  Input: head = [1,2,3,4]
            #  *  Output: [2,1,4,3]
            #  *
            #  *  Input: head = []
            #  *  Output: []
            #  *
            #  *  Input: head = [1]
            #  *  Output: [1]
            #  */
            logging.info("Input: head = %s", head)

            pHead = ListNode.buildList(head)
            retVal = pSolution.swapPairs(pHead)
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

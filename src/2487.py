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
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        retVal = None

        previous = None
        current = head
        next = None
        while current != None:
            next = current.next
            current.next = previous
            previous = current
            current = next
        retVal = previous

        return retVal

    def removeNodes(self, head: Optional[ListNode]) -> Optional[ListNode]:
        retVal = head

        head = self.reverseList(head)

        maximum = 0
        previous = None
        current = head
        while current != None:
            maximum = max(maximum, current.val)
            if current.val >= maximum:
                previous = current
                current = current.next
                continue

            if previous != None:
                previous.next = current.next
            else:
                head = current.next
            deleted = current
            current = current.next
            deleted.next = None

        retVal = self.reverseList(head)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head in [[5, 2, 13, 3, 8], [1, 1, 1, 1]]:
            # /* Example
            #  *  Input: head = [5,2,13,3,8]
            #  *  Output: [13,8]
            #  *
            #  *  Input: head = [1,1,1,1]
            #  *  Output: [1,1,1,1]
            #  */
            logging.info("Input: head = %s", head)

            head = ListNode.buildList(head)
            retVal = pSolution.removeNodes(head)
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

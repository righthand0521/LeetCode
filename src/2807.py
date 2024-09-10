import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional

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
    def gcd(self, a: int, b: int) -> int:
        retVal = 1

        while b != 0:
            a, b = b, a % b
        retVal = a

        return retVal

    def insertGreatestCommonDivisors(self, head: Optional[ListNode]) -> Optional[ListNode]:
        retVal = head

        if (retVal is None) or (retVal.next is None):
            return retVal

        node1 = retVal
        node2 = retVal.next
        while node2 is not None:
            gcdValue = self.gcd(node1.val, node2.val)

            gcdNode = ListNode(gcdValue)
            node1.next = gcdNode
            gcdNode.next = node2

            node1 = node2
            node2 = node2.next

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head in [[18, 6, 10, 3], [7]]:
            # /* Example
            #  *  Input: head = [18,6,10,3]
            #  *  Output: [18,6,6,2,10,1,3]
            #  *
            #  *  Input: head = [7]
            #  *  Output: [7]
            #  */
            logging.info("Input: head = %s", head)
            pHead = ListNode.buildList(head)

            retVal = pSolution.insertGreatestCommonDivisors(pHead)
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

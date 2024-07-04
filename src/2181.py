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
    def mergeNodes(self, head: Optional[ListNode]) -> Optional[ListNode]:
        retVal = head

        modify = head.next
        nextSum = modify
        while nextSum:
            sum = 0

            # Find the sum of all nodes until you encounter a 0.
            while nextSum.val != 0:
                sum += nextSum.val
                nextSum = nextSum.next

            # Assign the sum to the current node's value.
            modify.val = sum

            # Move nextSum to the first non-zero value of the next block.
            nextSum = nextSum.next

            # Move modify also to this node.
            modify.next = nextSum
            modify = modify.next

        retVal = head.next

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head in [[0, 3, 1, 0, 4, 5, 2, 0], [0, 1, 0, 3, 0, 2, 2, 0]]:
            # /* Example
            #  *  Input: head = [0,3,1,0,4,5,2,0]
            #  *  Output: [4,11]
            #  *
            #  *  Input: head = [0,1,0,3,0,2,2,0]
            #  *  Output: [1,3,4]
            #  */
            logging.info("Input: head = %s", head)

            pHead = ListNode.buildList(head)
            retVal = pSolution.mergeNodes(pHead)
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

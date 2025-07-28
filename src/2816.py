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
    def doubleIt(self, head: Optional[ListNode]) -> Optional[ListNode]:
        retVal = head

        previous = None
        current = head
        while current != None:
            doubleValue = current.val * 2
            if doubleValue < 10:
                current.val = doubleValue
            elif previous != None:
                current.val = doubleValue % 10
                previous.val += 1
            else:
                head = ListNode(1, current)
                current.val = doubleValue % 10
            previous = current
            current = current.next
        retVal = head

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head in [[1, 8, 9], [9, 9, 9]]:
            # /* Example
            #  *  Input: head = [1,8,9]
            #  *  Output: [3,7,8]
            #  *
            #  *  Input: head = [9,9,9]
            #  *  Output: [1,9,9,8]
            #  */
            logging.info("Input: head = %s", head)

            head = ListNode.buildList(head)
            retVal = pSolution.doubleIt(head)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

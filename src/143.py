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
    def reorderList(self, head: Optional[ListNode]) -> None:
        """
        Do not return anything, modify head in-place instead.
        """
        if head == None:
            return

        address = []
        pNext = head
        while pNext != None:
            address.append(pNext)
            pNext = pNext.next

        left = 0
        right = len(address) - 1
        while left < right:
            address[left].next = address[right]
            left += 1
            if left == right:
                break
            address[right].next = address[left]
            right -= 1
        address[left].next = None


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head in [[1, 2, 3, 4], [1, 2, 3, 4, 5]]:
            # /* Example
            #  *  Input: head = [1,2,3,4]
            #  *  Output: [1,4,2,3]
            #  *
            #  *  Input: head = [1,2,3,4,5]
            #  *  Output: [1,5,2,4,3]
            #  */
            logging.info("Input: head = %s", head)

            pHead = ListNode.buildList(head)
            pSolution.reorderList(pHead)
            logging.info("Output: %s", pHead)

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

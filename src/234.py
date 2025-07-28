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
    def isPalindrome(self, head: Optional[ListNode]) -> bool:
        retVal = False

        value = []
        pCurrent = head
        while pCurrent != None:
            value.append(pCurrent.val)
            pCurrent = pCurrent.next

        left = 0
        right = len(value) - 1
        while left <= right:
            if value[left] != value[right]:
                return retVal
            left += 1
            right -= 1
        retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head in [[1, 2, 2, 1], [1, 2], [1, 2, 1], [1, 2, 3], [1]]:
            # /* Example
            #  *  Input: head = [1,2,2,1]
            #  *  Output: true
            #  *
            #  *  Input: head = [1,2]
            #  *  Output: false
            #  */
            logging.info("Input: head = %s", head)

            pHead = ListNode.buildList(head)
            retVal = pSolution.isPalindrome(pHead)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

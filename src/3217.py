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
    def modifiedList(self, nums: List[int], head: Optional[ListNode]) -> Optional[ListNode]:
        retVal = head

        valuesToRemove = set(nums)

        while (retVal) and (retVal.val in valuesToRemove):
            retVal = retVal.next
        if not retVal:
            return retVal

        current = retVal
        while current.next:
            if current.next.val in valuesToRemove:
                current.next = current.next.next
            else:
                current = current.next

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, head in zip([[1, 2, 3], [1], [5]], [[1, 2, 3, 4, 5], [1, 2, 1, 2, 1, 2], [1, 2, 3, 4]]):
            # /* Example
            #  *  Input: nums = [1,2,3], head = [1,2,3,4,5]
            #  *  Output: [4,5]
            #  *
            #  *  Input: nums = [1], head = [1,2,1,2,1,2]
            #  *  Output: [2,2,2]
            #  *
            #  *  Input: nums = [5], head = [1,2,3,4]
            #  *  Output: [1,2,3,4]
            #  */
            logging.info("Input: nums = %s, head = %s", nums, head)

            pHead = ListNode.buildList(head)
            retVal = pSolution.modifiedList(nums, pHead)
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

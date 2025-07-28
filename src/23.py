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
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        retVal = ListNode(0)

        nums = []
        heapify(nums)
        for l in lists:
            while l is not None:
                heappush(nums, l.val)
                l = l.next

        node = retVal
        while len(nums) > 0:
            node.next = ListNode(nums[0])
            node = node.next
            heappop(nums)

        retVal = retVal.next

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for lists in [[[1, 4, 5], [1, 3, 4], [2, 6]], [], [[]]]:
            # /* Example
            #  *  Input: lists = [[1,4,5],[1,3,4],[2,6]]
            #  *  Output: [1,1,2,3,4,4,5,6]
            #  *
            #  *  Input: lists = []
            #  *  Output: []
            #  *
            #  *  Input: lists = [[]]
            #  *  Output: []
            #  */
            logging.info("Input: lists = %s", lists)

            pList = []
            for l in lists:
                pHead = ListNode.buildList(l)
                pList.append(pHead)

            retVal = pSolution.mergeKLists(pList)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

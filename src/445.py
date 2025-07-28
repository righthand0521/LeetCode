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
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        retVal = ListNode()

        list1 = []
        while l1 != None:
            list1.append(l1.val)
            l1 = l1.next

        list2 = []
        while l2 != None:
            list2.append(l2.val)
            l2 = l2.next

        carry = 0
        while list1 or list2:
            sum = carry
            if list1:
                sum += list1.pop()
            if list2:
                sum += list2.pop()
            retVal.val = sum % 10

            carry = sum // 10
            node = ListNode(carry)
            node.next = retVal
            retVal = node

        if carry == 0:
            retVal = retVal.next

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for l1, l2 in zip([[7, 2, 4, 3], [2, 4, 3], [0]], [[5, 6, 4], [5, 6, 4], [0]]):
            # /* Example
            #  *  Input: l1 = [7,2,4,3], l2 = [5,6,4]
            #  *  Output: [7,8,0,7]
            #  *
            #  *  Input: l1 = [2,4,3], l2 = [5,6,4]
            #  *  Output: [8,0,7]
            #  *
            #  *  Input: l1 = [0], l2 = [0]
            #  *  Output: [0]
            #  */
            logging.info("Input: l1 = %s, l2 = %s", l1, l2)

            pHead1 = ListNode.buildList(l1)
            pHead2 = ListNode.buildList(l2)
            retVal = pSolution.addTwoNumbers(pHead1, pHead2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

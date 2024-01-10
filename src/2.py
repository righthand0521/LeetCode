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
        retVal = ListNode(0)

        node = retVal
        carry = 0
        while ((l1 != None) or (l2 != None)):
            sum = 0

            if l1 != None:
                sum += l1.val
                l1 = l1.next

            if l2 != None:
                sum += l2.val
                l2 = l2.next

            sum += carry
            carry = 0
            if sum >= 10:
                sum = sum % 10
                carry = 1

            node.next = ListNode(sum)
            node = node.next

        if carry == 1:
            node.next = ListNode(carry)
            node = node.next
            carry = 0

        retVal = retVal.next

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for l1, l2 in zip([[2, 4, 3], [0], [9, 9, 9, 9, 9, 9, 9], [7, 1, 6], [9, 7, 8]],
                          [[5, 6, 4], [0], [9, 9, 9, 9], [5, 9, 2], [6, 8, 5]]):
            # /* Example
            #  *  Input: l1 = [2,4,3], l2 = [5,6,4]
            #  *  Output: [7,0,8]
            #  *
            #  *  Input: l1 = [0], l2 = [0]
            #  *  Output: [0]
            #  *
            #  *  Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
            #  *  Output: [8,9,9,9,0,0,0,1]
            #  *
            #  *  Input: l1 = [7,1,6], l2 = [5,9,2]
            #  *  Output: [2,1,9]
            #  *
            #  *  Input: l1 = [9,7,8], l2 = [6,8,5]
            #  *  Output: [5,6,4,1]
            #  */
            logging.info("Input: l1 = %s, l2 = %s", l1, l2)

            pHead1 = ListNode.buildList(l1)
            pHead2 = ListNode.buildList(l2)
            retVal = pSolution.addTwoNumbers(pHead1, pHead2)
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

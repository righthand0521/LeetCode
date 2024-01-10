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
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        retVal = ListNode(0)

        node = retVal
        while ((list1 != None) or (list2 != None)):
            if list1 == None:
                node.next = ListNode(list2.val)
                list2 = list2.next
            elif list2 == None:
                node.next = ListNode(list1.val)
                list1 = list1.next
            elif list1.val <= list2.val:
                node.next = ListNode(list1.val)
                list1 = list1.next
            elif list1.val > list2.val:
                node.next = ListNode(list2.val)
                list2 = list2.next
            node = node.next

        retVal = retVal.next

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for l1, l2 in zip([[1, 2, 4], [], []], [[1, 3, 4], [], [0]]):
            # /* Example
            #  *  Input: list1 = [1,2,4], list2 = [1,3,4]
            #  *  Output: [1,1,2,3,4,4]
            #  *
            #  *  Input: list1 = [], list2 = []
            #  *  Output: []
            #  *
            #  *  Input: list1 = [], list2 = [0]
            #  *  Output: [0]
            #  */
            logging.info("Input: l1 = %s, l2 = %s", l1, l2)

            pHead1 = ListNode.buildList(l1)
            pHead2 = ListNode.buildList(l2)
            retVal = pSolution.mergeTwoLists(pHead1, pHead2)
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

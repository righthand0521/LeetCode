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
    def partition(self, head: Optional[ListNode], x: int) -> Optional[ListNode]:
        retVal = head

        if head == None:
            return retVal

        pLessHead = ListNode()
        pLess = pLessHead
        pGreatHead = ListNode()
        pGreat = pGreatHead
        while retVal != None:
            if retVal.val < x:
                pLess.next = retVal
                pLess = pLess.next
            else:
                pGreat.next = retVal
                pGreat = pGreat.next
            retVal = retVal.next
        pLess.next = pGreatHead.next
        pGreat.next = None
        retVal = pLessHead.next

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head, x in zip([[1, 4, 3, 2, 5, 2], [2, 1], [], [1], [1, 1], [1, 1], [3, 5, 8, 5, 10, 2, 1]],
                           [3, 2, 0, 2, 2, 0, 5]):
            # /* Example
            #  *  Input: head = [1,4,3,2,5,2], x = 3
            #  *  Output: [1,2,2,4,3,5]
            #  *
            #  *  Input: head = [2,1], x = 2
            #  *  Output: [1,2]
            #  *
            #  *  Input: head = [], x = 0
            #  *  Output: []
            #  *
            #  *  Input: head = [1], x = 2
            #  *  Output: [1]
            #  *
            #  *  Input: head = [1,1], x = 2
            #  *  Output: [1,1]
            #  *
            #  *  Input: head = [1,1], x = 0
            #  *  Output: [1,1]
            #  *
            #  *  Input: head = [3,5,8,5,10,2,1], x = 5
            #  *  Output: [3,2,1,5,8,5,10]
            #  */
            logging.info("Input: head = %s, x = %s", head, x)

            pHead = ListNode.buildList(head)
            retVal = pSolution.partition(pHead, x)
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

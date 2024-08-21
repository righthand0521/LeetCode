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
    def reverse(self, head: ListNode, tail: ListNode):
        pPrevious = tail.next
        pCurent = head
        while pPrevious != tail:
            pNext = pCurent.next
            pCurent.next = pPrevious
            pPrevious = pCurent
            pCurent = pNext

        return tail, head

    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        retVal = head

        pHair = ListNode(0)
        pHair.next = head

        pPrevious = pHair
        while head != None:
            pTail = pPrevious

            for _ in range(k):
                pTail = pTail.next
                if pTail == None:
                    retVal = pHair.next
                    return retVal

            pNext = pTail.next
            head, pTail = self.reverse(head, pTail)

            pPrevious.next = head
            pTail.next = pNext
            pPrevious = pTail
            head = pTail.next

        retVal = pHair.next

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head, k in zip([[1, 2, 3, 4, 5], [1, 2, 3, 4, 5]], [2, 3]):
            # /* Example
            #  *  Input: head = [1,2,3,4,5], k = 2
            #  *  Output: [2,1,4,3,5]
            #  *
            #  *  Input: head = [1,2,3,4,5], k = 3
            #  *  Output: [3,2,1,4,5]
            #  */
            logging.info("Input: head = %s, k = %s", head, k)

            pHead = ListNode.buildList(head)
            retVal = pSolution.reverseKGroup(pHead, k)
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

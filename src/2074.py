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
    def reverseEvenLengthGroups(self, head: Optional[ListNode]) -> Optional[ListNode]:
        retVal = head

        count = 0
        pPrevious = None
        pCurrent = head
        while pCurrent != None:
            count += 1
            length = 0
            pNext = pCurrent
            while (length < count) and (pNext != None):
                length += 1
                pNext = pNext.next

            if length % 2 == 0:
                for _ in range(length-1):
                    pTmp = pCurrent.next
                    pCurrent.next = pCurrent.next.next
                    pTmp.next = pPrevious.next
                    pPrevious.next = pTmp
            else:
                for _ in range(length-1):
                    pPrevious = pCurrent
                    pCurrent = pCurrent.next

            pPrevious = pCurrent
            pCurrent = pCurrent.next

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head in [[5, 2, 6, 3, 9, 1, 7, 3, 8, 4], [1, 1, 0, 6], [1, 1, 0, 6, 5]]:
            # /* Example
            #  *  Input: head = [5,2,6,3,9,1,7,3,8,4]
            #  *  Output: [5,6,2,3,9,1,4,8,3,7]
            #  *
            #  *  Input: head = [1,1,0,6]
            #  *  Output: [1,0,1,6]
            #  *
            #  *  Input: head = [1,1,0,6,5]
            #  *  Output: [1,0,1,5,6]
            #  */
            logging.info("Input: head = %s", head)

            pHead = ListNode.buildList(head)
            pHead = pSolution.reverseEvenLengthGroups(pHead)
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

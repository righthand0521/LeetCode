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
#     def __init__(self, x):
#         self.val = x
#         self.next = None
class Solution:
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> Optional[ListNode]:
        retVal = None

        lenA = 0
        pCurrentA = headA
        while pCurrentA.next != None:
            lenA += 1
            pCurrentA = pCurrentA.next

        lenB = 0
        pCurrentB = headB
        while pCurrentB.next != None:
            lenB += 1
            pCurrentB = pCurrentB.next

        if pCurrentA != pCurrentB:
            return retVal

        diff = abs(lenA - lenB)
        retVal = headA if lenA > lenB else headB
        for i in range(diff):
            retVal = retVal.next

        pCurrentA = retVal if lenA > lenB else headA
        pCurrentB = retVal if lenB > lenA else headB
        while retVal != None:
            if pCurrentA == pCurrentB:
                return retVal
            retVal = retVal.next
            pCurrentA = pCurrentA.next
            pCurrentB = pCurrentB.next

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for intersectVal, listA, listB, skipA, skipB in zip(
            [8, 2, 0],
            [[4, 1, 8, 4, 5], [1, 9, 1, 2, 4], [2, 6, 4]],
            [[5, 6, 1, 8, 4, 5], [3, 2, 4], [1, 5]],
            [2, 3, 3],
            [3, 1, 2]
        ):
            # /* Example
            #  *  Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
            #  *  Output: Intersected at '8'
            #  *
            #  *  Input: intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
            #  *  Output: Intersected at '2'
            #  *
            #  *  Input: intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
            #  *  Output: No intersection
            #  */
            logging.info("Input: intersectVal = %s, listA = %s, listB = %s, skipA = %s, skipB = %s",
                         intersectVal, listA, listB, skipA, skipB)

            intersect = None
            for i in range(skipA, len(listA)):
                intersect = ListNodeCommon().addValueToEndListNode(intersect, listA[i])
            headA = None
            for i in range(skipA):
                headA = ListNodeCommon().addValueToEndListNode(headA, listA[i])
            headA = ListNodeCommon().mergeListNode(headA, intersect)
            headB = None
            for i in range(skipB):
                headB = ListNodeCommon().addValueToEndListNode(headB, listB[i])
            headB = ListNodeCommon().mergeListNode(headB, intersect)

            retVal = pSolution.getIntersectionNode(headA, headB)
            if retVal is None:
                logging.info("Output: No intersection")
            else:
                logging.info("Output: Intersected at '%s'", intersectVal)

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

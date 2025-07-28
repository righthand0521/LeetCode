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
    def nodesBetweenCriticalPoints(self, head: Optional[ListNode]) -> List[int]:
        retVal = [-1, -1]

        # The number of nodes in the list is in the range [2, 10^5].
        currentIndex = 1
        current = head.next
        previous = head

        firstCriticalIndex = 0
        previousCriticalIndex = 0
        minDistance = float("inf")
        while current.next is not None:
            if (((current.val < previous.val) and (current.val < current.next.val)) or
                    ((current.val > previous.val) and (current.val > current.next.val))):
                if previousCriticalIndex == 0:
                    previousCriticalIndex = currentIndex
                    firstCriticalIndex = currentIndex
                else:
                    minDistance = min(minDistance, currentIndex - previousCriticalIndex)
                    previousCriticalIndex = currentIndex

            currentIndex += 1
            previous = current
            current = current.next

        if minDistance != float("inf"):
            maxDistance = previousCriticalIndex - firstCriticalIndex
            retVal = [minDistance, maxDistance]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head in [[3, 1], [5, 3, 1, 2, 5, 1, 2], [1, 3, 2, 2, 3, 2, 2, 2, 7]]:
            # /* Example
            #  *  Input: head = [3,1]
            #  *  Output: [-1,-1]
            #  *
            #  *  Input: head = [5,3,1,2,5,1,2]
            #  *  Output: [1,3]
            #  *
            #  *  Input: head = [1,3,2,2,3,2,2,2,7]
            #  *  Output: [3,3]
            #  */
            logging.info("Input: head = %s", head)

            pHead = ListNode.buildList(head)
            retVal = pSolution.nodesBetweenCriticalPoints(pHead)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

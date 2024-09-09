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
    def spiralMatrix(self, m: int, n: int, head: Optional[ListNode]) -> List[List[int]]:
        retVal = [[-1] * n for _ in range(m)]

        movement = [[0, 1], [1, 0], [0, -1], [-1, 0]]
        movementIndex = 0
        x = 0
        y = 0
        pCurrent = head
        while pCurrent != None:
            retVal[x][y] = pCurrent.val

            x += movement[movementIndex][0]
            y += movement[movementIndex][1]
            # 0 <= Node.val <= 1000
            if (x < 0) or (y < 0) or (x >= m) or (y >= n) or (retVal[x][y] != -1):
                x -= movement[movementIndex][0]
                y -= movement[movementIndex][1]
                movementIndex = (movementIndex + 1) % 4
                x += movement[movementIndex][0]
                y += movement[movementIndex][1]

            pCurrent = pCurrent.next

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for m, n, head in zip([3, 1], [5, 4], [[3, 0, 2, 6, 8, 1, 7, 9, 4, 2, 5, 5, 0], [0, 1, 2]]):
            # /* Example
            #  *  Input: m = 3, n = 5, head = [3,0,2,6,8,1,7,9,4,2,5,5,0]
            #  *  Output: [[3,0,2,6,8],[5,0,-1,-1,1],[5,2,4,9,7]]
            #  *
            #  *  Input: m = 1, n = 4, head = [0,1,2]
            #  *  Output: [[0,1,2,-1]]
            #  */
            logging.info("Input: m = %s, n = %s, head = %s", m, n, head)

            retVal = pSolution.spiralMatrix(m, n, ListNode.buildList(head))
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

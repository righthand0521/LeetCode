import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


class Solution:
    def step(self, fruits: List[List[int]], startPos: int, left: int, right: int) -> int:
        retVal = 0

        if fruits[right][0] <= startPos:
            retVal = startPos - fruits[left][0]
        elif fruits[left][0] >= startPos:
            retVal = fruits[right][0] - startPos
        else:
            retVal = min(abs(startPos - fruits[right][0]), abs(startPos - fruits[left][0]))
            retVal += fruits[right][0]
            retVal -= fruits[left][0]

        return retVal

    def maxTotalFruits(self, fruits: List[List[int]], startPos: int, k: int) -> int:
        retVal = 0

        fruitsSize = len(fruits)

        sum = 0
        left = 0
        right = 0
        while right < fruitsSize:
            sum += fruits[right][1]

            while (left <= right) and (self.step(fruits, startPos, left, right) > k):
                sum -= fruits[left][1]
                left += 1
            retVal = max(retVal, sum)

            right += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for fruits, startPos, k in [
            [[[2, 8], [6, 3], [8, 6]], 5, 4],
            [[[0, 9], [4, 1], [5, 7], [6, 2], [7, 4], [10, 9]], 5, 4],
            [[[0, 3], [6, 4], [8, 5]], 3, 2]
        ]:
            # /* Example
            #  *  Input: fruits = [[2,8],[6,3],[8,6]], startPos = 5, k = 4
            #  *  Output: 9
            #  *
            #  *  Input: fruits = [[0,9],[4,1],[5,7],[6,2],[7,4],[10,9]], startPos = 5, k = 4
            #  *  Output: 14
            #  *
            #  *  Input: fruits = [[0,3],[6,4],[8,5]], startPos = 3, k = 2
            #  *  Output: 0
            #  */
            logging.info("Input: fruits = %s, startPos = %s, k = %s", fruits, startPos, k)

            retVal = pSolution.maxTotalFruits(fruits, startPos, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

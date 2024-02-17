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
    def furthestBuilding(self, heights: List[int], bricks: int, ladders: int) -> int:
        retVal = 0

        heightsSize = len(heights)

        bricksSum = 0
        laddersHeap = []
        for i in range(1, heightsSize):
            diff = heights[i] - heights[i-1]
            if diff <= 0:
                continue

            heappush(laddersHeap, diff)
            if len(laddersHeap) > ladders:
                bricksSum += heappop(laddersHeap)

            if bricksSum > bricks:
                retVal = i - 1
                return retVal

        retVal = heightsSize - 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for heights, bricks, ladders in zip([[4, 2, 7, 6, 9, 14, 12], [4, 12, 2, 7, 3, 18, 20, 3, 19], [14, 3, 19, 3]],
                                            [5, 10, 17],
                                            [1, 2, 0]):
            # /* Example
            #  *  Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
            #  *  Output: 4
            #  *
            #  *  Input: heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
            #  *  Output: 7
            #  *
            #  *  Input: heights = [14,3,19,3], bricks = 17, ladders = 0
            #  *  Output: 3
            #  */
            logging.info(
                "Input: heights = %s, bricks = %s, ladders = %s", heights, bricks, ladders)

            retVal = pSolution.furthestBuilding(heights, bricks, ladders)
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

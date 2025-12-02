import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop

from math import atan2


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
    def countTrapezoids(self, points: List[List[int]]) -> int:
        retVal = 0

        pointsSize = len(points)
        inf = 10**9 + 7

        slopeToIntercept = defaultdict(list)
        middleToSlope = defaultdict(list)
        for i in range(pointsSize):
            x1, y1 = points[i]
            for j in range(i + 1, pointsSize):
                x2, y2 = points[j]
                dx = x1 - x2
                dy = y1 - y2

                if x2 == x1:
                    k = inf
                    b = x1
                else:
                    k = (y2 - y1) / (x2 - x1)
                    b = (y1 * dx - x1 * dy) / dx

                middle = (x1 + x2) * 10000 + (y1 + y2)
                slopeToIntercept[k].append(b)
                middleToSlope[middle].append(k)

        for sti in slopeToIntercept.values():
            stiSize = len(sti)
            if stiSize == 1:
                continue

            cnt = defaultdict(int)
            for b_val in sti:
                cnt[b_val] += 1

            totalSum = 0
            for count in cnt.values():
                retVal += (totalSum * count)
                totalSum += count

        for mts in middleToSlope.values():
            mtsSize = len(mts)
            if mtsSize == 1:
                continue

            cnt = defaultdict(int)
            for k_val in mts:
                cnt[k_val] += 1

            totalSum = 0
            for count in cnt.values():
                retVal -= (totalSum * count)
                totalSum += count

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for points in [[[-3, 2], [3, 0], [2, 3], [3, 2], [2, -3]], [[0, 0], [1, 0], [0, 1], [2, 1]]]:
            # /* Example
            #  *  Input: points = [[-3,2],[3,0],[2,3],[3,2],[2,-3]]
            #  *  Output: 2
            #  *
            #  *  Input: points = [[0,0],[1,0],[0,1],[2,1]]
            #  *  Output: 1
            #  */
            logging.info("Input: points = %s", points)

            retVal = pSolution.countTrapezoids(points)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

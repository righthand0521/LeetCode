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
    def maxPoints(self, points: List[List[int]]) -> int:
        retVal = 1

        pointsSize = len(points)
        if pointsSize == 1:
            return retVal

        retVal = 2
        for i in range(pointsSize):
            hashTable = defaultdict(lambda: 0)
            for j in range(pointsSize):
                if i == j:
                    continue
                x = points[j][0] - points[i][0]
                y = points[j][1] - points[i][1]
                hashTable[atan2(y, x)] += 1

            for arctangent in hashTable:
                retVal = max(retVal, hashTable[arctangent] + 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for points in [[[1, 1], [2, 2], [3, 3]], [[1, 1], [3, 2], [5, 3], [4, 1], [2, 3], [1, 4]]]:
            # /* Example
            #  *  Input: points = [[1,1],[2,2],[3,3]]
            #  *  Output: 3
            #  *
            #  *  Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
            #  *  Output: 4
            #  */
            logging.info("Input: points = %s", points)

            retVal = pSolution.maxPoints(points)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

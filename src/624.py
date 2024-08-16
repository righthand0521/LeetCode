import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional


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
    def maxDistance(self, arrays: List[List[int]]) -> int:
        retVal = 0

        arraysSize = len(arrays)

        minValue = arrays[0][0]
        maxValue = arrays[0][-1]
        for i in range(1, arraysSize):
            diff1 = abs(arrays[i][-1] - minValue)
            diff2 = abs(maxValue - arrays[i][0])
            retVal = max(retVal, diff1, diff2)

            minValue = min(minValue, arrays[i][0])
            maxValue = max(maxValue, arrays[i][-1])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arrays in [[[1, 2, 3], [4, 5], [1, 2, 3]], [[1], [1]]]:
            # /* Example
            #  *  Input: arrays = [[1,2,3],[4,5],[1,2,3]]
            #  *  Output: 4
            #  *
            #  *  Input: arrays = [[1],[1]]
            #  *  Output: 0
            #  */
            logging.info("Input: arrays = %s", arrays)

            retVal = pSolution.maxDistance(arrays)
            logging.info("Output: %d", retVal)

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

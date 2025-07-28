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
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        retVal = []

        intervals.sort(key=lambda intervals: intervals[0])

        intervalsSize = len(intervals)
        retVal.append(intervals[0])
        for i in range(1, intervalsSize):
            if retVal[-1][1] >= intervals[i][0]:
                retVal[-1][1] = max(retVal[-1][1], intervals[i][1])
            else:
                retVal.append(intervals[i])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for intervals in [[[1, 3], [2, 6], [8, 10], [15, 18]], [[1, 4], [4, 5]], [[1, 4], [2, 3]]]:
            # /* Example
            #  *  Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
            #  *  Output: [[1,6],[8,10],[15,18]]
            #  *
            #  *  Input: intervals = [[1,4],[4,5]]
            #  *  Output: [[1,5]]
            #  *
            #  *  Input: intervals = [[1,4],[2,3]]
            #  *  Output: [[1,4]]
            #  */
            logging.info("Input: intervals = %s", intervals)

            retVal = pSolution.merge(intervals)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

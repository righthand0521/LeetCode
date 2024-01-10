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
    def eraseOverlapIntervals(self, intervals: List[List[int]]) -> int:
        retVal = 0

        overlapping = float('-inf')
        intervals.sort(key=lambda intervals: (intervals[1], intervals[0]))
        for start, end in intervals:
            if start < overlapping:
                retVal += 1
            else:
                overlapping = end

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for intervals in [[[1, 2], [2, 3], [3, 4], [1, 3]], [[1, 2], [1, 2], [1, 2]], [[1, 2], [2, 3]]]:
            # /* Example
            #  *  Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
            #  *  Output: 1
            #  *
            #  *  Input: intervals = [[1,2],[1,2],[1,2]]
            #  *  Output: 2
            #  *
            #  *  Input: intervals = [[1,2],[2,3]]
            #  *  Output: 0
            #  */
            logging.info("Input: intervals = %s", intervals)

            retVal = pSolution.eraseOverlapIntervals(intervals)
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

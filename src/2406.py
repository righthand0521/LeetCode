import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from copy import deepcopy
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
    def minGroups(self, intervals: List[List[int]]) -> int:
        retVal = 0

        # Convert the intervals to two events start as (start, 1) and end as (end + 1, -1)
        events = []
        for interval in intervals:
            events.append((interval[0], 1))
            events.append((interval[1] + 1, -1))
        # Sort the events first by time, and then by type (1 for start, -1 for end).
        events.sort(key=lambda x: (x[0], x[1]))

        concurrentIntervals = 0
        maxConcurrentIntervals = 0
        for event in events:
            concurrentIntervals += event[1]
            maxConcurrentIntervals = max(maxConcurrentIntervals, concurrentIntervals)
        retVal = maxConcurrentIntervals

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for intervals in [[[5, 10], [6, 8], [1, 5], [2, 3], [1, 10]], [[1, 3], [5, 6], [8, 10], [11, 13]]]:
            # /* Example
            #  *  Input: intervals = [[5,10],[6,8],[1,5],[2,3],[1,10]]
            #  *  Output: 3
            #  *
            #  *  Input: intervals = [[1,3],[5,6],[8,10],[11,13]]
            #  *  Output: 1
            #  */
            logging.info("Input: intervals = %s", intervals)

            retVal = pSolution.minGroups(intervals)
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

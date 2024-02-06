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
    def insert(self, intervals: List[List[int]], newInterval: List[int]) -> List[List[int]]:
        retVal = []

        left = newInterval[0]
        right = newInterval[1]
        place = False

        for interval in intervals:
            if interval[0] > right:
                if place == False:
                    retVal.append([left, right])
                    place = True
                retVal.append(interval)
            elif interval[1] < left:
                retVal.append(interval)
            else:
                left = min(left, interval[0])
                right = max(right, interval[1])

        if place == False:
            retVal.append([left, right])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for intervals, newInterval in zip([[[1, 3], [6, 9]], [[1, 2], [3, 5], [6, 7], [8, 10], [12, 16]]],
                                          [[2, 5], [4, 8]]):
            # /* Example
            #  *  Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
            #  *  Output: [[1,5],[6,9]]
            #  *
            #  *  Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
            #  *  Output: [[1,2],[3,10],[12,16]]
            #  */
            logging.info("Input: intervals = %s, newInterval = %s", intervals, newInterval)

            retVal = pSolution.insert(intervals, newInterval)
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

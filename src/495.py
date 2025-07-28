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
    def findPoisonedDuration(self, timeSeries: List[int], duration: int) -> int:
        retVal = 0

        expired = 0
        for timeSerie in timeSeries:
            if timeSerie >= expired:
                retVal += duration
            else:
                retVal += (timeSerie + duration - expired)
            expired = timeSerie + duration

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for timeSeries, duration in zip([[1, 4], [1, 2]], [2, 2]):
            # /* Example
            #  *  Input: timeSeries = [1,4], duration = 2
            #  *  Output: 4
            #  *
            #  *  Input: timeSeries = [1,2], duration = 2
            #  *  Output: 3
            #  */
            logging.info("Input: timeSeries = %s, duration = %s", timeSeries, duration)

            retVal = pSolution.findPoisonedDuration(timeSeries, duration)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

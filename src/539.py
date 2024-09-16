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
    def findMinDifference(self, timePoints: List[str]) -> int:
        retVal = 0

        minutes = []
        for timePoint in timePoints:
            minutes.append(int(timePoint[:2]) * 60 + int(timePoint[3:]))
        minutes.sort()

        retVal = 24 * 60 - minutes[-1] + minutes[0]
        minutesSize = len(minutes)
        for i in range(minutesSize - 1):
            retVal = min(retVal, minutes[i + 1] - minutes[i])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for timePoints in [["23:59", "00:00"], ["00:00", "23:59", "00:00"], ["01:01", "02:01"]]:
            # /* Example
            #  *  Input: timePoints = ["23:59","00:00"]
            #  *  Output: 1
            #  *
            #  *  Input: timePoints = ["00:00","23:59","00:00"]
            #  *  Output: 0
            #  *
            #  *  Input: timePoints = ["01:01","02:01"]
            #  *  Output: 60
            #  */
            logging.info("Input: timePoints = %s", timePoints)

            retVal = pSolution.findMinDifference(timePoints)
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

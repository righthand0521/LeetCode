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
    def maxFreeTime(self, eventTime: int, k: int, startTime: List[int], endTime: List[int]) -> int:
        retVal = 0

        startTimeSize = len(startTime)
        t = 0
        for i in range(startTimeSize):
            t += (endTime[i] - startTime[i])
            left = 0 if i <= k - 1 else endTime[i - k]
            right = eventTime if i == startTimeSize - 1 else startTime[i + 1]
            retVal = max(retVal, right - left - t)
            if i >= k - 1:
                t -= (endTime[i - k + 1] - startTime[i - k + 1])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for eventTime, k, startTime, endTime in [
            [5, 1, [1, 3], [2, 5]],
            [10, 1, [0, 2, 9], [1, 4, 10]],
            [5, 2, [0, 1, 2, 3, 4], [1, 2, 3, 4, 5]]
        ]:
            # /* Example
            #  *  Input: eventTime = 5, k = 1, startTime = [1,3], endTime = [2,5]
            #  *  Output: 2
            #  *
            #  *  Input: eventTime = 10, k = 1, startTime = [0,2,9], endTime = [1,4,10]
            #  *  Output: 6
            #  *
            #  *  Input: eventTime = 5, k = 2, startTime = [0,1,2,3,4], endTime = [1,2,3,4,5]
            #  *  Output: 0
            #  */
            logging.info("Input: eventTime = %s, k = %s, startTime = %s, endTime = %s",
                         eventTime, k, startTime, endTime)

            retVal = pSolution.maxFreeTime(eventTime, k, startTime, endTime)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

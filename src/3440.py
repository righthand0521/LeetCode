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
    def maxFreeTime(self, eventTime: int, startTime: List[int], endTime: List[int]) -> int:
        retVal = 0

        startTimeSize = len(startTime)
        q = [False] * startTimeSize
        t1 = 0
        t2 = 0
        for i in range(startTimeSize):
            if endTime[i] - startTime[i] <= t1:
                q[i] = True
            t1 = max(t1, startTime[i] - (0 if i == 0 else endTime[i - 1]))

            if endTime[startTimeSize - i - 1] - startTime[startTimeSize - i - 1] <= t2:
                q[startTimeSize - i - 1] = True
            t2 = max(t2, (eventTime if i == 0 else startTime[startTimeSize - i]) - endTime[startTimeSize - i - 1])

        for i in range(startTimeSize):
            left = 0 if i == 0 else endTime[i - 1]
            right = eventTime if i == startTimeSize - 1 else startTime[i + 1]
            if q[i] == True:
                retVal = max(retVal, right - left)
            else:
                retVal = max(retVal, right - left - (endTime[i] - startTime[i]))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for eventTime, startTime, endTime in [
            [5,  [1, 3], [2, 5]],
            [10,  [0, 7, 9], [1, 8, 10]],
            [10,  [0, 3, 7, 9], [1, 4, 8, 10]],
            [5,  [0, 1, 2, 3, 4], [1, 2, 3, 4, 5]]
        ]:
            # /* Example
            #  *  Input: eventTime = 5, startTime = [1,3], endTime = [2,5]
            #  *  Output: 2
            #  *
            #  *  Input: eventTime = 10, startTime = [0,7,9], endTime = [1,8,10]
            #  *  Output: 7
            #  *
            #  *  Input: eventTime = 10, startTime = [0,3,7,9], endTime = [1,4,8,10]
            #  *  Output: 6
            #  *
            #  *  Input: eventTime = 5, startTime = [0, 1, 2, 3, 4], endTime = [1, 2, 3, 4, 5]
            #  *  Output: 0
            #  */
            logging.info("Input: eventTime = %s,  startTime = %s, endTime = %s", eventTime,  startTime, endTime)

            retVal = pSolution.maxFreeTime(eventTime,  startTime, endTime)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

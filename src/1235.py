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
    def jobScheduling(self, startTime: List[int], endTime: List[int], profit: List[int]) -> int:
        retVal = 0

        startTimeSize = len(startTime)

        jobs = sorted(zip(startTime, endTime, profit), key=lambda p: p[1])

        dp = [0] * (startTimeSize + 1)
        for i in range(1, startTimeSize + 1):
            k = bisect_right(jobs, jobs[i - 1][0], hi=i, key=lambda p: p[1])
            dp[i] = max(dp[i - 1], dp[k] + jobs[i - 1][2])
        retVal = dp[startTimeSize]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for startTime, endTime, profit in zip(
            [[1, 2, 3, 3], [1, 2, 3, 4, 6], [1, 1, 1]],
            [[3, 4, 5, 6], [3, 5, 10, 6, 9], [2, 3, 4]],
            [[50, 10, 40, 70], [20, 20, 100, 70, 60], [5, 6, 4]]):
            # /* Example
            #  *  Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
            #  *  Output: 120
            #  *
            #  *  Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
            #  *  Output: 150
            #  *
            #  *  Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
            #  *  Output: 6
            #  */
            logging.info("Input: startTime = %s, endTime = %s, profit = %s", startTime, endTime, profit)

            retVal = pSolution.jobScheduling(startTime, endTime, profit)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

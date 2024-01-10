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
    def makesquare(self, matchsticks: List[int]) -> bool:
        retVal = False

        sumOfMatchsticks = sum(matchsticks)
        if sumOfMatchsticks % 4:
            return retVal
        squareSide = sumOfMatchsticks // 4

        matchsticksSize = len(matchsticks)
        dpSize = (1 << matchsticksSize)
        dp = [-1] * dpSize
        dp[0] = 0
        for i in range(1, dpSize):
            for key, value in enumerate(matchsticks):
                if i & (1 << key) == 0:
                    continue
                j = i & ~(1 << key)

                if (dp[j] >= 0) and (dp[j] + value <= squareSide):
                    dp[i] = (dp[j] + value) % squareSide
                    break
        retVal = (dp[-1] == 0)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for matchsticks in [[1, 1, 2, 2, 2], [3, 3, 3, 3, 4]]:
            # /* Example
            #  *  Input: matchsticks = [1,1,2,2,2]
            #  *  Output: true
            #  *
            #  *  Input: matchsticks = [3,3,3,3,4]
            #  *  Output: false
            #  */
            logging.info("Input: matchsticks = %s", matchsticks)

            retVal = pSolution.makesquare(matchsticks)
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

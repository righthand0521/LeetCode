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
    def canCross(self, stones: List[int]) -> bool:
        retVal = False

        stonesSize = len(stones)

        dp = [[False for _ in range(stonesSize)] for _ in range(stonesSize)]
        dp[0][0] = True

        for i in range(1, stonesSize):
            if stones[i] - stones[i - 1] > i:
                return retVal

        for i in range(1, stonesSize):
            for j in range(i-1, -1, -1):
                k = stones[i] - stones[j]
                if k > j+1:
                    break

                dp[i][k] = dp[j][k - 1] or dp[j][k] or dp[j][k + 1]
                if (i == stonesSize - 1) and (dp[i][k] != False):
                    retVal = True
                    return retVal

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for stones in [[0, 1, 3, 5, 6, 8, 12, 17], [0, 1, 2, 3, 4, 8, 9, 11]]:
            # /* Example
            #  *  Input: stones = [0,1,3,5,6,8,12,17]
            #  *  Output: true
            #  *
            #  *  Input: stones = [0,1,2,3,4,8,9,11]
            #  *  Output: false
            #  */
            logging.info("Input: stones = %s", stones)

            retVal = pSolution.canCross(stones)
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

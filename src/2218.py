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
    def maxValueOfCoins(self, piles: List[List[int]], k: int) -> int:
        retVal = 0

        prefixSum = [[0] + list(accumulate(pile)) for pile in piles]
        dp = [0] * (k+1)
        for i in range(len(piles)):
            for j in range(k, -1, -1):
                for select in range(len(piles[i]) + 1):
                    sum_ = prefixSum[i][select]
                    if j - select >= 0:
                        dp[j] = max(dp[j], dp[j - select] + sum_)
        retVal = dp[-1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for piles, k in zip([[[1, 100, 3], [7, 8, 9]],
                             [[100], [100], [100], [100], [100], [100], [1, 1, 1, 1, 1, 1, 700]]],
                            [2, 7]):
            # /* Example
            #  *  Input: piles = [[1,100,3],[7,8,9]], k = 2
            #  *  Output: 101
            #  *
            #  *  Input: piles = [[100],[100],[100],[100],[100],[100],[1,1,1,1,1,1,700]], k = 7
            #  *  Output: 706
            #  */
            logging.info("Input: piles = %s, k = %s", piles, k)

            retVal = pSolution.maxValueOfCoins(piles, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

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
    # https://leetcode.cn/problems/stone-game-ii/solutions/284065/java-dong-tai-gui-hua-qing-xi-yi-dong-17xing-by-lg/
    def stoneGameII(self, piles: List[int]) -> int:
        retVal = 0

        pilesSize = len(piles)
        dp = [[0 for _ in range(pilesSize + 1)] for _ in range(pilesSize)]
        sum = 0
        for i in range(pilesSize - 1, -1, -1):
            sum += piles[i]
            for M in range(1, pilesSize + 1):
                if i + 2 * M >= pilesSize:
                    dp[i][M] = sum
                else:
                    for x in range(1, 2 * M + 1):
                        dp[i][M] = max(dp[i][M], sum - dp[i + x][max(M, x)])
        retVal = dp[0][1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for piles in [[2, 7, 9, 4, 4], [1, 2, 3, 4, 5, 100]]:
            # /* Example
            #  *  Input: piles = [2,7,9,4,4]
            #  *  Output: 10
            #  *
            #  *  Input: piles = [1,2,3,4,5,100]
            #  *  Output: 104
            #  */
            logging.info("Input: piles = %s", piles)

            retVal = pSolution.stoneGameII(piles)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

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
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def numMusicPlaylists(self, n: int, goal: int, k: int) -> int:
        retVal = 0

        # the number of possible playlists of length goal containing exactly n unique songs
        dp = [[0 for _ in range(n + 1)] for _ in range(goal + 1)]
        dp[0][0] = 1

        for i in range(1, goal + 1):
            for j in range(1, min(i, n) + 1):
                # The i-th song is a new song
                dp[i][j] = dp[i - 1][j - 1] * (n - j + 1) % self.MODULO
                # The i-th song is a song we have played before
                if j > k:
                    dp[i][j] = (dp[i][j] + dp[i - 1][j]
                                * (j - k)) % self.MODULO

        retVal = dp[goal][n]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, goal, k in zip([3, 2, 2], [3, 3, 3],  [1, 0, 1]):
            # /* Example
            #  *  Input: n = 3, goal = 3, k = 1
            #  *  Output: 6
            #  *
            #  *  Input: n = 2, goal = 3, k = 0
            #  *  Output: 6
            #  *
            #  *  Input: n = 2, goal = 3, k = 1
            #  *  Output: 2
            #  */
            logging.info("Input: n = %s, goal = %s, k = %s", n, goal, k)

            retVal = pSolution.numMusicPlaylists(n, goal, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

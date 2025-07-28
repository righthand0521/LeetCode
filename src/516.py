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
    def longestPalindromeSubseq(self, s: str) -> int:
        retVal = 0

        # /* dp[i][j]: the longest palindromic subsequence's length of substring(i, j)
        #  *  +-----------------------+   +-------------------+
        #  *  |   | b | b | b | a | b |   |   | c | b | b | d |
        #  *  |---+---+---+---+---+---|   |---+---+---+---+---|
        #  *  | b | 1 | 2 | 3 | 3 |[4]|   | c | 1 | 1 | 2 |[2]|
        #  *  |---+---+---+---+---+---|   |---+---+---+---+---|
        #  *  | b | 0 | 1 | 2 | 2 | 3 |   | b | 0 | 1 | 2 | 2 |
        #  *  |---+---+---+---+---+---|   |---+---+---+---+---|
        #  *  | b | 0 | 0 | 1 | 1 | 3 |   | b | 0 | 0 | 1 | 1 |
        #  *  |---+---+---+---+---+---|   |---+---+---+---+---|
        #  *  | a | 0 | 0 | 0 | 1 | 1 |   | d | 0 | 0 | 0 | 1 |
        #  *  |---+---+---+---+---+---|   +-------------------+
        #  *  | b | 0 | 0 | 0 | 0 | 1 |
        #  *  +-----------------------+
        #  */
        sSize = len(s)
        dp = [[0] * sSize for _ in range(sSize)]
        for i in range(sSize-1, -1, -1):
            dp[i][i] = 1
            for j in range(i+1, sSize):
                if s[i] == s[j]:
                    dp[i][j] = dp[i+1][j-1] + 2
                else:
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1])
        retVal = dp[0][sSize-1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["bbbab", "cbbd"]:
            # /* Example
            #  *  Input: s = "bbbab"
            #  *  Output: 4
            #  *
            #  *  Input: s = "cbbd"
            #  *  Output: 2
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.longestPalindromeSubseq(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

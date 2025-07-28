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
    def minimumDeleteSum(self, s1: str, s2: str) -> int:
        retVal = 0

        # // 1143. Longest Common Subsequence: https://leetcode.com/problems/longest-common-subsequence/
        s1Size = len(s1)
        s2Size = len(s2)

        sum = 0
        for c in s1:
            sum += ord(c)
        for c in s2:
            sum += ord(c)

        dp = [[0 for i in range(s2Size+1)] for _ in range(s1Size+1)]
        for idx1 in range(1, s1Size+1):
            for idx2 in range(1, s2Size+1):
                if s1[idx1 - 1] == s2[idx2 - 1]:
                    dp[idx1][idx2] = dp[idx1 - 1][idx2 - 1] + ord(s1[idx1 - 1])
                else:
                    dp[idx1][idx2] = max(
                        dp[idx1 - 1][idx2], dp[idx1][idx2 - 1])
        retVal = sum - (2 * dp[s1Size][s2Size])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s1, s2 in zip(["sea", "delete"], ["eat", "leet"]):
            # /* Example
            #  *  Input: s1 = "sea", s2 = "eat"
            #  *  Output: 231
            #  *
            #  *  Input: s1 = "delete", s2 = "leet"
            #  *  Output: 403
            #  */
            logging.info("Input: s1 = \"%s\", s2 = \"%s\"", s1, s2)

            retVal = pSolution.minimumDeleteSum(s1, s2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

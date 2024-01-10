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
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        retVal = 0

        # // 712. Minimum ASCII Delete Sum for Two Strings:
        # // https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/
        s1Size = len(text1)
        s2Size = len(text2)

        # // https://pic.leetcode-cn.com/1617411822-KhEKGw-image.png
        dp = [[0 for i in range(s2Size+1)] for _ in range(s1Size+1)]
        for idx1 in range(1, s1Size+1):
            for idx2 in range(1, s2Size+1):
                if text1[idx1 - 1] == text2[idx2 - 1]:
                    dp[idx1][idx2] = dp[idx1 - 1][idx2 - 1] + 1
                else:
                    dp[idx1][idx2] = max(
                        dp[idx1 - 1][idx2], dp[idx1][idx2 - 1])
        retVal = dp[s1Size][s2Size]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for text1, text2 in zip(["abcde", "abc", "abc"], ["ace", "abc", "def"]):
            # /* Example
            #  *  Input: text1 = "abcde", text2 = "ace"
            #  *  Output: 3
            #  *
            #  *  Input: text1 = "abc", text2 = "abc"
            #  *  Output: 3
            #  *
            #  *  Input: text1 = "abc", text2 = "def"
            #  *  Output: 0
            #  */
            logging.info("Input: text1 = \"%s\", text2 = \"%s\"", text1, text2)

            retVal = pSolution.longestCommonSubsequence(text1, text2)
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

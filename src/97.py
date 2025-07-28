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
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
        retVal = False

        s1Size = len(s1)
        s2Size = len(s2)
        s3Size = len(s3)
        if s1Size + s2Size != s3Size:
            return retVal

        # /* dp[i,j]: s1[0:i] + s2[0:j] = s3[0:(i+j)]
        #  * dp[i,j] = (dp[i-1,j] and s1[0:i-1] = s3[0:i+j-1]) or (dp[i,j-1] and s2[0:j-1] = s3[0:i+j-1]), dp[0,0] = true.
        #  */
        dp = [[False for _ in range(s2Size + 1)] for _ in range(s1Size + 1)]
        dp[0][0] = True
        for s1Idx in range(s1Size + 1):
            for s2Idx in range(s2Size + 1):
                s3Idx = s1Idx + s2Idx - 1
                if s1Idx > 0:
                    dp[s1Idx][s2Idx] |= (
                        dp[s1Idx - 1][s2Idx] and s1[s1Idx - 1] == s3[s3Idx])
                if s2Idx > 0:
                    dp[s1Idx][s2Idx] |= (
                        dp[s1Idx][s2Idx - 1] and s2[s2Idx - 1] == s3[s3Idx])
        retVal = dp[s1Size][s2Size]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s1, s2, s3 in zip(["aabcc", "aabcc", ""], ["dbbca", "dbbca", ""], ["aadbbcbcac", "aadbbbaccc", ""]):
            # /* Example
            #  *  Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
            #  *  Output: true
            #  *
            #  *  Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
            #  *  Output: false
            #  *
            #  *  Input: s1 = "", s2 = "", s3 = ""
            #  *  Output: true
            #  */
            logging.info(
                "Input: s1 = \"%s\", s2 = \"%s\", s3 = \"%s\"", s1, s2, s3)

            retVal = pSolution.isInterleave(s1, s2, s3)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

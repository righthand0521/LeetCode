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
    def longestPalindrome(self, s: str) -> str:
        retVal = ""

        # /* Example: Input: s = "babad"
        #  *      0 1 2 3 4 |     0 1 2 3 4 |     0 1 2 3 4
        #  *      b a b a d |     b a b a d |     b a b a d
        #  *  0 b T         | 0 b T F       | 0 b T F T F F
        #  *  1 a   T       | 1 a   T F     | 1 a   T F T F
        #  *  2 b     T     | 2 b     T F   | 2 b     T F F
        #  *  3 a       T   | 3 a       T F | 3 a       T F
        #  *  4 d         T | 4 d         T | 4 d         T
        #  *
        #  * Example: Input: s = "cbbd"
        #  *      0 1 2 3 |     0 1 2 3 |     0 1 2 3
        #  *      c b b d |     c b b d |     c b b d
        #  *  0 c T       | 0 c T F     | 0 c T F F F
        #  *  1 b   T     | 1 b   T T   | 1 b   T T F
        #  *  2 b     T   | 2 b     T F | 2 b     T F
        #  *  3 d       T | 3 d       T | 3 d       T
        #  */
        sSize = len(s)
        dp = [[False] * sSize for _ in range(sSize)]
        #
        for i in range(sSize):
            dp[i][i] = True
            retVal = s[i:i+1]
        #
        for i in range(sSize - 1):
            if s[i] == s[i + 1]:
                dp[i][i + 1] = True
                retVal = s[i:(i+1)+1]
        #
        for diff in range(2, sSize):
            for i in range(sSize - diff):
                j = i + diff
                if s[i] == s[j] and dp[i + 1][j - 1]:
                    dp[i][j] = True
                    retVal = s[i:j+1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["babad", "cbbd"]:
            # /* Example
            #  *  Input: s = "babad"
            #  *  Output: "bab"
            #  *
            #  *  Input: s = "cbbd"
            #  *  Output: "bb"
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.longestPalindrome(s)
            logging.info("Output: \"%s\"", retVal)

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

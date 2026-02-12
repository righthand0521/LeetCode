import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional


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
    def helper(self, s: str, x: str, y: str) -> int:
        retVal = 0

        sSize = len(s)

        i = 0
        while i < sSize:
            if s[i] != x and s[i] != y:
                i += 1
                continue

            h = {0: i-1}
            diff = 0
            while (i < sSize) and ((s[i] == x) or (s[i] == y)):
                if s[i] == x:
                    diff += 1
                else:
                    diff -= 1

                if diff in h:
                    retVal = max(retVal, i - h[diff])
                else:
                    h[diff] = i

                i += 1

            i += 1

        return retVal

    def longestBalanced(self, s: str) -> int:
        retVal = 0

        sSize = len(s)

        # Case 1: single character
        last = 0
        for i in range(sSize):
            if (i > 0) and (s[i] == s[i-1]):
                last += 1
            else:
                last = 1

            retVal = max(retVal, last)

        # Case 2: two distinct characters
        retVal = max(retVal, self.helper(s, 'a', 'b'), self.helper(s, 'b', 'c'), self.helper(s, 'a', 'c'))

        # Case 3: all three characters
        pre = [0, 0, 0]
        h = {(0, 0): -1}
        for i, ch in enumerate(s):
            pre[ord(ch) - 97] += 1
            key = (pre[0] - pre[1], pre[1] - pre[2])
            if key in h:
                retVal = max(retVal, i - h[key])
            else:
                h[key] = i

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["abbac", "aabcc", "aba"]:
            # /* Example
            #  *  Input: s = "abbac"
            #  *  Output: 4
            #  *
            #  *  Input: s = "aabcc"
            #  *  Output: 3
            #  *
            #  *  Input: s = "aba"
            #  *  Output: 2
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.longestBalanced(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

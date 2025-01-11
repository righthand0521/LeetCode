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
    def canConstruct(self, s: str, k: int) -> bool:
        retVal = False

        sSize = len(s)
        if sSize < k:
            return retVal
        elif sSize == k:
            retVal = True
            return retVal

        frequency = [0] * 26  # s consists of lowercase English letters.
        for c in s:
            frequency[ord(c) - ord("a")] += 1

        oddCount = 0
        for count in frequency:
            if count % 2 == 1:
                oddCount += 1

        if oddCount <= k:
            retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, k in zip(["annabelle", "leetcode", "true"], [2, 3, 4]):
            # /* Example
            #  *  Input: s = "annabelle", k = 2
            #  *  Output: true
            #  *
            #  *  Input: s = "leetcode", k = 3
            #  *  Output: false
            #  *
            #  *  Input: s = "true", k = 4
            #  *  Output: true
            #  */
            logging.info("Input: s = \"%s\", k = %s", s, k)

            retVal = pSolution.canConstruct(s, k)
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

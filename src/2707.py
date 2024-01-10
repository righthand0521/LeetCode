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
    def minExtraChar(self, s: str, dictionary: List[str]) -> int:
        retVal = 0

        dictionary_set = set(dictionary)

        sSize = len(s)
        dp = [0] * (sSize + 1)
        for start in range(sSize - 1, -1, -1):
            dp[start] = 1 + dp[start + 1]
            for end in range(start, sSize):
                curr = s[start: end + 1]
                if curr in dictionary_set:
                    dp[start] = min(dp[start], dp[end + 1])
        retVal = dp[0]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, dictionary in zip(["leetscode", "sayhelloworld"], [["leet", "code", "leetcode"], ["hello", "world"]]):
            # /* Example
            #  *  Input: s = "leetscode", dictionary = ["leet","code","leetcode"]
            #  *  Output: 1
            #  *
            #  *  Input: s = "sayhelloworld", dictionary = ["hello","world"]
            #  *  Output: 3
            #  */
            logging.info("Input: s = \"%s\", dictionary = %s", s, dictionary)

            retVal = pSolution.minExtraChar(s, dictionary)
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

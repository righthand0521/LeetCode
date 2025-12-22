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
    def minDeletionSize(self, strs: List[str]) -> int:
        retVal = 0

        strSize = len(strs[0])

        dp = [1] * strSize
        for i in range(strSize - 2, -1, -1):
            for j in range(i + 1, strSize):
                needUpdate = True
                for s in strs:
                    if s[i] > s[j]:
                        needUpdate = False
                        break
                if needUpdate == True:
                    dp[i] = max(dp[i], 1 + dp[j])

        retVal = strSize - max(dp)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for strs in [["babca", "bbazb"], ["edcba"], ["ghi", "def", "abc"]]:
            # /* Example
            #  *  Input: strs = ["babca","bbazb"]
            #  *  Output: 3
            #  *
            #  *  Input: strs = ["edcba"]
            #  *  Output: 4
            #  *
            #  *  Input: strs = ["ghi","def","abc"]
            #  *  Output: 0
            #  */
            logging.info("Input: strs = %s", strs)

            retVal = pSolution.minDeletionSize(strs)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

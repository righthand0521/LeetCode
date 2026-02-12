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
    def longestBalanced(self, s: str) -> int:
        retVal = 0

        sSize = len(s)
        for i in range(sSize):
            hashTable = defaultdict(int)
            for j in range(i, sSize):
                hashTable[s[j]] += 1
                hashTableSize = len(set(hashTable.values()))
                if hashTableSize == 1:
                    retVal = max(retVal, j - i + 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["abbac", "zzabccy", "aba"]:
            # /* Example
            #  *  Input: s = "abbac"
            #  *  Output: 4
            #  *
            #  *  Input: s = "zzabccy"
            #  *  Output: 4
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

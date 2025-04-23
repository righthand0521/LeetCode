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
    def countLargestGroup(self, n: int) -> int:
        retVal = 0

        hashTable = Counter()
        for i in range(1, n + 1):
            key = sum([int(x) for x in str(i)])
            hashTable[key] += 1
        maxValue = max(hashTable.values())

        for value in hashTable.values():
            if value == maxValue:
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [13, 2]:
            # /* Example
            #  *  Input: n = 13
            #  *  Output: 4
            #  *
            #  *  Input: n = 2
            #  *  Output: 2
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.countLargestGroup(n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)

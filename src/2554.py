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
    def maxCount(self, banned: List[int], n: int, maxSum: int) -> int:
        retVal = 0

        # Store banned numbers in a set for quick lookup
        bannedSet = set(banned)

        for num in range(1, n + 1):
            # Skip banned numbers
            if num in bannedSet:
                continue

            # Return if adding the current number exceeds maxSum
            if maxSum - num < 0:
                break

            # Include current number
            maxSum -= num
            retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for banned, n, maxSum in zip([[1, 6, 5], [1, 2, 3, 4, 5, 6, 7], [11]], [5, 8, 7], [6, 1, 50]):
            # /* Example
            #  *  Input: banned = [1,6,5], n = 5, maxSum = 6
            #  *  Output: 2
            #  *
            #  *  Input: banned = [1,2,3,4,5,6,7], n = 8, maxSum = 1
            #  *  Output: 0
            #  *
            #  *  Input: banned = [11], n = 7, maxSum = 50
            #  *  Output: 7
            #  */
            logging.info("Input: banned = %s, n = %s, maxSum = %s",
                         banned, n, maxSum)

            retVal = pSolution.maxCount(banned, n, maxSum)
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
